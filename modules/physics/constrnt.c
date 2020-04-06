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

#include "physics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 		0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

constraint_forces
	*constraint_force_list_head = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_constraint_forces (int index)
{

	double_vec3d
		force,
		torque;

	rigid_body_dynamics
		*rb = nullptr;

	rb = rigid_body_list_head;
	
	while (rb)
	{

		calculate_constraint_force_and_torque (rb, &force, &torque, index);

		rb->linear_force [index].x += force.x;
		rb->linear_force [index].y += force.y;
		rb->linear_force [index].z += force.z;

		rb->torque [index].x += torque.x;
		rb->torque [index].y += torque.y;
		rb->torque [index].z += torque.z;

		#if DEBUG_MODULE
	
		debug_log ("BODY: Applying to %s constraint force [%f, %f, %f] torque [%f, %f, %f]",
						rb->name,
						force.x, force.y, force.z,
						torque.x, torque.y, torque.z);

		#endif

		rb = rb->next;
	}

	// destroy forces... combine with calculate fn ?

	destroy_constraint_forces ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_constraint_force (rigid_body_dynamics *rb, double_vec3d *force, double_vec3d *position, rigid_body_dynamics *owner)
{

	constraint_forces
		*new_constraint = nullptr;

	// debug
	//if ((get_3d_double_vector_magnitude (force) > 0.5))
	// debug
	if (!check_zero_3d_double_vector (force))
	{

		new_constraint = (constraint_forces *) malloc_heap_mem (sizeof (constraint_forces));

		memset (new_constraint, 0, sizeof (constraint_forces));
	
		new_constraint->owner = rb;
		new_constraint->force = *force;
		new_constraint->position = *position;
	
		new_constraint->next = constraint_force_list_head;
	
		constraint_force_list_head = new_constraint;
	
		#if DEBUG_MODULE

		if (((camera_object) && (rb == camera_object->rigid_body)))// && (stricmp (owner->name, "body") == 0))
		{

			double_vec3d
				temp_direction,
				temp_position;
	
			temp_position.x = rb->position_cm [0].x + position->x;
			temp_position.y = rb->position_cm [0].y + position->y;
			temp_position.z = rb->position_cm [0].z + position->z;
	
			temp_direction = *force;
			normalise_any_3d_double_vector (&temp_direction);
	
			//create_arrow ("TAIL_ARROW", &temp_position, &temp_direction, 6.0);
		
			debug_log ("BODY: 	adding %s constraint force %f dir [%f, %f, %f], pos [%f, %f, %f] from %s",
						rb->name,
						get_3d_double_vector_magnitude (force),
						temp_direction.x, temp_direction.y, temp_direction.z,
						position->x, position->y, position->z,
						(owner) ? owner->name : "NONE");
		}

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_constraint_force_and_torque (rigid_body_dynamics *rb, double_vec3d *force, double_vec3d *torque, int index)
{

	double_vec3d
		t;

	constraint_forces
		*cf = nullptr;

	force->x = 0.0;
	force->y = 0.0;
	force->z = 0.0;

	torque->x = 0.0;
	torque->y = 0.0;
	torque->z = 0.0;

	cf = constraint_force_list_head;

	while (cf)
	{

		if ((cf->owner == rb) && (cf->owner->system_id == rb->system_id))
		{
	
			force->x += cf->force.x;
			force->y += cf->force.y;
			force->z += cf->force.z;

			torque->x += cf->torque.x;
			torque->y += cf->torque.y;
			torque->z += cf->torque.z;

			get_3d_double_vector_cross_product (&t, &cf->force, &cf->position);

			torque->x += t.x;
			torque->y += t.y;
			torque->z += t.z;
		}

		cf = cf->next;
	}

	#if DEBUG_MODULE

	debug_log ("BODY: Calculating %s constraint force [%f, %f, %f], torque [%f, %f, %f]", rb->name, force->x, force->y, force->z, torque->x, torque->y, torque->z);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void new_add_constraint_force (rigid_body_dynamics *rb, double_vec3d *force, double_vec3d *torque)
{

	#if DEBUG_MODULE

	//if (rb != camera_object->rigid_body)
	{

		//return;

		debug_log ("BODY: recursively adding %s constraint force [%f, %f, %f]", rb->name, force->x, force->y, force->z);
	}

	#endif

	rb->visited = TRUE;

	recursively_add_constraint_force (rb, rb, force, torque);

	// clear visited flag

	rb = rigid_body_list_head;
	
	while (rb)
	{

		rb->visited = FALSE;

		rb = rb->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recursively_add_constraint_force (rigid_body_dynamics *owner, rigid_body_dynamics *rb, double_vec3d *force, double_vec3d *torque)
{

	rigid_body_dynamics
		*victim = nullptr;

	double
		mag;

	connection_type
		*connection = nullptr;

	double_vec3d
		new_torque,
		this_force,
		point_position,
		victim_position;

	connection = connection_list_head;

	while (connection)
	{

		victim = NULL;

		if ((connection->end_point == rb) && (!connection->start_point->visited))
		{

			victim = connection->start_point;

			victim_position = connection->start_point_position;
		}
		else if ((connection->start_point == rb) && (!connection->end_point->visited))
		{

			victim = connection->end_point;

			victim_position = connection->end_point_position;
		}

		if (victim)
		{

			victim->visited = TRUE;

			// calculate torque as a force

			multiply_double_matrix3x3_double_vec3d (&point_position, victim->attitude, &victim_position);

			mag = normalise_any_3d_double_vector (&point_position);
	
			this_force.x = 0.0;
			this_force.y = 0.0;
			this_force.z = 0.0;

			if (mag > 0.0)
			{
	
				get_3d_double_vector_cross_product (&this_force, &point_position, torque);
			}

			// add in linear force

			this_force.x += force->x;
			this_force.y += force->y;
			this_force.z += force->z;

			this_force.x *= victim->mass / owner->mass;
			this_force.y *= victim->mass / owner->mass;
			this_force.z *= victim->mass / owner->mass;

			multiply_double_matrix3x3_double_vec3d (&point_position, victim->attitude, &victim_position);

			add_constraint_force (victim, &this_force, &point_position, owner);

			// calculate force/torque wrt this object and apply to all connections

			get_3d_double_vector_cross_product (&new_torque, force, &point_position);
	
			//recursively_add_constraint_force (owner, victim, force, &new_torque);
		}

		connection = connection->next;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_constraint_forces (void)
{

	constraint_forces
		*destroy_cf = nullptr,
		*cf = nullptr;

	cf = constraint_force_list_head;

	while (cf)
	{

		destroy_cf = cf;

		cf = cf->next;

		free_mem (destroy_cf);
	}

	constraint_force_list_head = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
