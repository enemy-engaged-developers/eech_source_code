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

connection_type
	*connection_list_head = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_connection_parameters (connection_type *connection, int index);

static void update_connection_forces (rigid_body_dynamics *rb, connection_type *connection, int index);

static void draw_connection (connection_type *connection);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_connections (void)
{

	connection_type
		*destroy_connection = nullptr;

	while (connection_list_head)
	{

		destroy_connection = connection_list_head;

		connection_list_head = connection_list_head->next;

		free_mem (destroy_connection);
	}

	connection_list_head = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

connection_type *create_connection (double length, double max_compression_percentage, double max_extension_percentage, double moe)
{

	connection_type
		*new_connection = nullptr;
	
	new_connection = (connection_type *) malloc_heap_mem (sizeof (connection_type));

	if (new_connection)
	{

		ASSERT (moe >= 0.0);
		ASSERT (length >= 0.0);
		ASSERT (max_extension_percentage >= 0.0);
		ASSERT (max_compression_percentage >= 0.0);

		memset (new_connection, 0, sizeof (connection_type));

		new_connection->moe = moe;

		new_connection->natural_length = length;

		new_connection->actual_length = length;

		new_connection->delta_extension = 0.0;

		new_connection->moe_div_length = moe / length;

		new_connection->max_extension_percentage = max_extension_percentage;

		new_connection->max_compression_percentage = max_compression_percentage;

		new_connection->next = connection_list_head;

		connection_list_head = new_connection;

		return new_connection;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_connections_parameters (int index)
{

	connection_type
		*current_connection = nullptr;

	current_connection = connection_list_head;

	while (current_connection)
	{

		update_connection_parameters (current_connection, index);

		current_connection = current_connection->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_connections_forces (rigid_body_dynamics *rb, int index)
{

	connection_type
		*current_connection = nullptr;

	current_connection = connection_list_head;

	while (current_connection)
	{

		update_connection_forces (rb, current_connection, index);

		current_connection = current_connection->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_connection_parameters (connection_type *connection, int index)
{

	double
		length,
		inverse_actual_length,
		one_over_rigid_body_delta_time;

	double_vec3d
		velocity,
		direction,
		end_position,
		start_position,
		normalised_direction;

	if ((!connection->start_point) || (!connection->end_point))
	{

		return;
	}

	multiply_double_matrix3x3_double_vec3d (&start_position, connection->start_point->attitude, &connection->start_point_position);
	multiply_double_matrix3x3_double_vec3d (&end_position, connection->end_point->attitude, &connection->end_point_position);
	
	direction.x = (connection->end_point->position_cm [index].x - connection->start_point->position_cm [index].x) + (end_position.x - start_position.x);
	direction.y = (connection->end_point->position_cm [index].y - connection->start_point->position_cm [index].y) + (end_position.y - start_position.y);
	direction.z = (connection->end_point->position_cm [index].z - connection->start_point->position_cm [index].z) + (end_position.z - start_position.z);

	normalised_direction = direction;

	normalise_any_3d_double_vector (&normalised_direction);

	//
	// Stuff to only do once per frame
	//

	one_over_rigid_body_delta_time = 1.0 / get_rigid_body_delta_time ();

	length = get_3d_double_vector_magnitude (&direction);

	connection->delta_extension = length - connection->actual_length;

	connection->actual_length = length;

	connection->extension = connection->actual_length - connection->natural_length;

	velocity.x = (normalised_direction.x * connection->delta_extension) * one_over_rigid_body_delta_time;
	velocity.y = (normalised_direction.y * connection->delta_extension) * one_over_rigid_body_delta_time;
	velocity.z = (normalised_direction.z * connection->delta_extension) * one_over_rigid_body_delta_time;

	connection->damping_force = connection->damping *
										(((velocity.x * direction.x) + (velocity.y * direction.y) + (velocity.z * direction.z)) /
										((direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z)));

	inverse_actual_length = get_inverse_square_root ((direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z));

	connection->tension = connection->moe_div_length - (connection->moe * inverse_actual_length);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_connection_forces (rigid_body_dynamics *rb, connection_type *connection, int index)
{

	double_vec3d
		direction,
		end_position,
		start_position,
		normalised_direction;

	if ((!connection->start_point) || (!connection->end_point))
	{

		return;
	}

	if ((connection->start_point != rb) && (connection->end_point != rb))
	{

		return;
	}

	multiply_double_matrix3x3_double_vec3d (&start_position, connection->start_point->attitude, &connection->start_point_position);
	multiply_double_matrix3x3_double_vec3d (&end_position, connection->end_point->attitude, &connection->end_point_position);
	
	direction.x = (connection->end_point->position_cm [index].x - connection->start_point->position_cm [index].x) + (end_position.x - start_position.x);
	direction.y = (connection->end_point->position_cm [index].y - connection->start_point->position_cm [index].y) + (end_position.y - start_position.y);
	direction.z = (connection->end_point->position_cm [index].z - connection->start_point->position_cm [index].z) + (end_position.z - start_position.z);

	normalised_direction = direction;

	normalise_any_3d_double_vector (&normalised_direction);

	//
	// Stuff to only do once per frame
	//
	
	// start of connection
	if (connection->start_point == rb)
	{

		double_vec3d
			cross1,
			tension_force,
			damping_force;

		// damping
		damping_force.x = 0.5 * connection->damping_force * direction.x;
		damping_force.y = 0.5 * connection->damping_force * direction.y;
		damping_force.z = 0.5 * connection->damping_force * direction.z;

		connection->start_point->linear_force [index].x += damping_force.x;
		connection->start_point->linear_force [index].y += damping_force.y;
		connection->start_point->linear_force [index].z += damping_force.z;

		get_3d_double_vector_cross_product (&cross1, &start_position, &damping_force);

		connection->start_point->torque [index].x -= cross1.x;
		connection->start_point->torque [index].y -= cross1.y;
		connection->start_point->torque [index].z -= cross1.z;

		// spring
		tension_force.x = 0.5 * connection->tension * direction.x;
		tension_force.y = 0.5 * connection->tension * direction.y;
		tension_force.z = 0.5 * connection->tension * direction.z;
		
		connection->start_point->linear_force [index].x += tension_force.x;
		connection->start_point->linear_force [index].y += tension_force.y;
		connection->start_point->linear_force [index].z += tension_force.z;

		get_3d_double_vector_cross_product (&cross1, &start_position, &tension_force);

		connection->start_point->torque [index].x -= cross1.x;
		connection->start_point->torque [index].y -= cross1.y;
		connection->start_point->torque [index].z -= cross1.z;

		// torque
		connection->start_point->torque [index].x += normalised_direction.x * connection->start_torque;
		connection->start_point->torque [index].y += normalised_direction.y * connection->start_torque;
		connection->start_point->torque [index].z += normalised_direction.z * connection->start_torque;
	}

	// end of connection
	if (connection->end_point == rb)
	{

		double_vec3d
			cross1,
			tension_force,
			damping_force;

		invert_3d_double_vector (&direction);

		// damping
		damping_force.x = 0.5 * connection->damping_force * direction.x;
		damping_force.y = 0.5 * connection->damping_force * direction.y;
		damping_force.z = 0.5 * connection->damping_force * direction.z;

		connection->end_point->linear_force [index].x += damping_force.x;
		connection->end_point->linear_force [index].y += damping_force.y;
		connection->end_point->linear_force [index].z += damping_force.z;

		get_3d_double_vector_cross_product (&cross1, &end_position, &damping_force);

		connection->end_point->torque [index].x -= cross1.x;
		connection->end_point->torque [index].y -= cross1.y;
		connection->end_point->torque [index].z -= cross1.z;

		// spring
		tension_force.x = 0.5 * connection->tension * direction.x;
		tension_force.y = 0.5 * connection->tension * direction.y;
		tension_force.z = 0.5 * connection->tension * direction.z;

		connection->end_point->linear_force [index].x += tension_force.x;
		connection->end_point->linear_force [index].y += tension_force.y;
		connection->end_point->linear_force [index].z += tension_force.z;

		get_3d_double_vector_cross_product (&cross1, &end_position, &tension_force);

		connection->end_point->torque [index].x -= cross1.x;
		connection->end_point->torque [index].y -= cross1.y;
		connection->end_point->torque [index].z -= cross1.z;

		// torque
		connection->end_point->torque [index].x += normalised_direction.x * connection->end_torque;
		connection->end_point->torque [index].y += normalised_direction.y * connection->end_torque;
		connection->end_point->torque [index].z += normalised_direction.z * connection->end_torque;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_connections_constraints (int index)
{

	connection_type
		*current_connection = nullptr;

	// calculate constraint forces

	current_connection = connection_list_head;

	while (current_connection)
	{

		update_connection_constraints (current_connection, index);

		current_connection = current_connection->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_connection_constraints (connection_type *connection, int index)
{

	double_vec3d
		torque,
		linear_force,
		constraint_vector,
		angular_constraint,
		//childs_angular_constraint,
		end_point_position,
		start_point_position;

	if ((!connection->start_point) || (!connection->end_point))
	{

		return;
	}
	
	multiply_double_matrix3x3_double_vec3d (&start_point_position, connection->start_point->attitude, &connection->start_point_position);
	multiply_double_matrix3x3_double_vec3d (&end_point_position, connection->end_point->attitude, &connection->end_point_position);

	constraint_vector.x = (connection->end_point->original_position_cm [0].x - connection->start_point->original_position_cm [0].x) + (connection->end_point_position.x - connection->start_point_position.x);
	constraint_vector.y = (connection->end_point->original_position_cm [0].y - connection->start_point->original_position_cm [0].y) + (connection->end_point_position.y - connection->start_point_position.y);
	constraint_vector.z = (connection->end_point->original_position_cm [0].z - connection->start_point->original_position_cm [0].z) + (connection->end_point_position.z - connection->start_point_position.z);

	multiply_double_matrix3x3_double_vec3d (&constraint_vector, connection->start_point->attitude, &constraint_vector);
	
	multiply_double_matrix3x3_double_vec3d (&angular_constraint, connection->start_point->attitude, &connection->angular_constraint);

	if (!check_zero_3d_double_vector (&constraint_vector))
	{

		/////////////////////////////////////////////////////////////////////////////////////////
		//
		// Linearly
		//
		/////////////////////////////////////////////////////////////////////////////////////////

		// child must exist along this constraint vector
	
		normalise_3d_double_vector (&constraint_vector);

		/////////////////////////////////////////////////////////////////////////
		// project child's total linear forces onto constraint vector
		/////////////////////////////////////////////////////////////////////////

		calculate_friction_force_and_torque (connection->end_point, &linear_force, &torque, index);

		linear_force.x += connection->end_point->linear_force [index].x;
		linear_force.y += connection->end_point->linear_force [index].y;
		linear_force.z += connection->end_point->linear_force [index].z;

		torque.x += connection->end_point->torque [index].x;
		torque.y += connection->end_point->torque [index].y;
		torque.z += connection->end_point->torque [index].z;

		if (!check_zero_3d_double_vector (&linear_force))
		{

			double
				dot,
				mag;

			double_vec3d
				remaining_force,
				constraint_force;

			//double_vec3d
				//childs_angular_constraint;

			//multiply_transpose_double_matrix3x3_double_vec3d (&childs_angular_constraint, connection->start_point->attitude, &connection->angular_constraint);
			//multiply_double_matrix3x3_double_vec3d (&childs_angular_constraint, connection->end_point->attitude, &connection->angular_constraint);

			dot = get_3d_double_vector_dot_product (&linear_force, &constraint_vector);
	
			mag = get_3d_double_vector_magnitude (&linear_force);
	
			constraint_force.x = mag * dot * constraint_vector.x;
			constraint_force.y = mag * dot * constraint_vector.y;
			constraint_force.z = mag * dot * constraint_vector.z;
	
			remaining_force.x = (linear_force.x - constraint_force.x);
			remaining_force.y = (linear_force.y - constraint_force.y);
			remaining_force.z = (linear_force.z - constraint_force.z);

			if (!connection->end_point->powered)
			{

				// project remaining force onto angular constraint vector
	
				dot = get_3d_double_vector_dot_product (&remaining_force, &connection->angular_constraint);
		
				mag = get_3d_double_vector_magnitude (&remaining_force);
		
				remaining_force.x = mag * dot * connection->angular_constraint.x;
				remaining_force.y = mag * dot * connection->angular_constraint.y;
				remaining_force.z = mag * dot * connection->angular_constraint.z;
			}

			if (!check_zero_3d_double_vector (&remaining_force))
			{
	
				// add remaining force to parent (start_point)

				torque.x = 0.0;
				torque.y = 0.0;
				torque.z = 0.0;

				//debug
				if (connection->end_point == camera_object->rigid_body)
				{
			
					double_vec3d
						temp_direction,
						temp_position;
			
					temp_position.x = connection->end_point->position_cm [0].x;
					temp_position.y = connection->end_point->position_cm [0].y;
					temp_position.z = connection->end_point->position_cm [0].z;
			
					temp_direction = remaining_force;
					temp_direction.y = 0.0;
					normalise_any_3d_double_vector (&temp_direction);
			
					create_arrow ("CENTRE_ARROW", &temp_position, &temp_direction, 6.0);

					debug_log ("CONNECT: force [%f, %f, %f]", remaining_force.x, remaining_force.y, remaining_force.z);
				}
				//debug

				new_add_constraint_force (connection->end_point, &remaining_force, &torque);
			}
		}

		/////////////////////////////////////////////////////////////////////////
		// project parents's total linear forces onto constraint vector
		/////////////////////////////////////////////////////////////////////////
/*
		calculate_friction_force_and_torque (connection->start_point, &linear_force, &torque, index);

		linear_force.x += connection->start_point->linear_force [index].x;
		linear_force.y += connection->start_point->linear_force [index].y;
		linear_force.z += connection->start_point->linear_force [index].z;

		torque.x += connection->start_point->torque [index].x;
		torque.y += connection->start_point->torque [index].y;
		torque.z += connection->start_point->torque [index].z;

		if (!check_zero_3d_double_vector (&linear_force))
		{

			double
				dot,
				mag;

			double_vec3d
				constraint_force,
				remaining_force;
	
			dot = get_3d_double_vector_dot_product (&linear_force, &constraint_vector);
	
			mag = get_3d_double_vector_magnitude (&linear_force);
	
			constraint_force.x = mag * dot * constraint_vector.x;
			constraint_force.y = mag * dot * constraint_vector.y;
			constraint_force.z = mag * dot * constraint_vector.z;
	
			remaining_force.x = (linear_force.x - constraint_force.x);
			remaining_force.y = (linear_force.y - constraint_force.y);
			remaining_force.z = (linear_force.z - constraint_force.z);
	
			if (!check_zero_3d_double_vector (&remaining_force))
			{

				// add remaining force to parent (start_point)

				torque.x = 0.0;
				torque.y = 0.0;
				torque.z = 0.0;

				if (connection->end_point == camera_object->rigid_body)
				{
			
					double_vec3d
						temp_direction,
						temp_position;
			
					temp_position.x = connection->start_point->position_cm [0].x;
					temp_position.y = connection->start_point->position_cm [0].y;
					temp_position.z = connection->start_point->position_cm [0].z;
			
					temp_direction = remaining_force;
					//temp_direction = childs_angular_constraint;
					//temp_direction = connection->angular_constraint;
					//temp_direction = linear_force;
					temp_direction.y = 0.0;
					normalise_any_3d_double_vector (&temp_direction);
			
					create_arrow ("TAIL_ARROW", &temp_position, &temp_direction, 6.0);
				}

				new_add_constraint_force (connection->start_point, &remaining_force, &torque);
			}
		}
		*/

		/////////////////////////////////////////////////////////////////////////
		// project child's position onto the constraint vector
		/////////////////////////////////////////////////////////////////////////

		{

			double
				dot,
				mag;
	
			double_vec3d
				new_position,
				delta_position;
	
			delta_position.x = (connection->end_point->position_cm [index].x - connection->start_point->position_cm [index].x) + (end_point_position.x - start_point_position.x);
			delta_position.y = (connection->end_point->position_cm [index].y - connection->start_point->position_cm [index].y) + (end_point_position.y - start_point_position.y);
			delta_position.z = (connection->end_point->position_cm [index].z - connection->start_point->position_cm [index].z) + (end_point_position.z - start_point_position.z);
	
			if (!check_zero_3d_double_vector (&delta_position))
			{

				// position
	
				dot = get_3d_double_vector_dot_product (&delta_position, &constraint_vector);

				dot = max (dot, 0.0);
		
				mag = get_3d_double_vector_magnitude (&delta_position);
		
				delta_position.x = mag * dot * constraint_vector.x;
				delta_position.y = mag * dot * constraint_vector.y;
				delta_position.z = mag * dot * constraint_vector.z;
	
				new_position.x = connection->start_point->position_cm [index].x + start_point_position.x + delta_position.x;
				new_position.y = connection->start_point->position_cm [index].y + start_point_position.y + delta_position.y;
				new_position.z = connection->start_point->position_cm [index].z + start_point_position.z + delta_position.z;
	
				new_position.x -= end_point_position.x;
				new_position.y -= end_point_position.y;
				new_position.z -= end_point_position.z;
	
				connection->end_point->position_cm [index] = new_position;
			}
		}

		/////////////////////////////////////////////////////////////////////////
		// parents velocity mapped onto child
		/////////////////////////////////////////////////////////////////////////
/*
		if (!check_zero_3d_double_vector (&connection->start_point->velocity_cm [index]))
		{

			double
				dot,
				mag;

			double_vec3d
				cross1,
				position,
				total_velocity,
				constraint_velocity,
				remaining_velocity;
	
  			// projects parents velocity onto constraint vector and get remaining velocity

			dot = get_3d_double_vector_dot_product (&connection->start_point->velocity_cm [index], &constraint_vector);
	
			mag = get_3d_double_vector_magnitude (&connection->start_point->velocity_cm [index]);
	
			constraint_velocity.x = mag * dot * constraint_vector.x;
			constraint_velocity.y = mag * dot * constraint_vector.y;
			constraint_velocity.z = mag * dot * constraint_vector.z;
	
			remaining_velocity.x = connection->start_point->velocity_cm [index].x - constraint_velocity.x;
			remaining_velocity.y = connection->start_point->velocity_cm [index].y - constraint_velocity.y;
			remaining_velocity.z = connection->start_point->velocity_cm [index].z - constraint_velocity.z;
	
  			// project childs velocity onto constraint

			if (!check_zero_3d_double_vector (&connection->end_point->velocity_cm [index]))
			{
	
				dot = get_3d_double_vector_dot_product (&connection->end_point->velocity_cm [index], &constraint_vector);
		
				mag = get_3d_double_vector_magnitude (&connection->end_point->velocity_cm [index]);
		
				constraint_velocity.x = mag * dot * constraint_vector.x;
				constraint_velocity.y = mag * dot * constraint_vector.y;
				constraint_velocity.z = mag * dot * constraint_vector.z;
	
				connection->end_point->velocity_cm [index] = constraint_velocity;
			}

			// add in parents linear velocity

			total_velocity.x = remaining_velocity.x;
			total_velocity.y = remaining_velocity.y;
			total_velocity.z = remaining_velocity.z;

			// add in parents angular velocity

			if (!check_zero_3d_double_vector (&connection->start_point->angular_velocity [index]))
			{
	
				position.x = connection->end_point->position_cm [index].x - connection->start_point->position_cm [index].x;
				position.y = connection->end_point->position_cm [index].y - connection->start_point->position_cm [index].y;
				position.z = connection->end_point->position_cm [index].z - connection->start_point->position_cm [index].z;
	
				get_3d_double_vector_cross_product (&cross1, &position, &connection->start_point->angular_velocity [index]);

				if (!check_zero_3d_double_vector (&cross1))
				{
		
					dot = get_3d_double_vector_dot_product (&cross1, &constraint_vector);
			
					mag = get_3d_double_vector_magnitude (&cross1);
			
					constraint_velocity.x = mag * dot * constraint_vector.x;
					constraint_velocity.y = mag * dot * constraint_vector.y;
					constraint_velocity.z = mag * dot * constraint_vector.z;
			
					remaining_velocity.x = cross1.x - constraint_velocity.x;
					remaining_velocity.y = cross1.y - constraint_velocity.y;
					remaining_velocity.z = cross1.z - constraint_velocity.z;
			
					total_velocity.x += remaining_velocity.x;
					total_velocity.y += remaining_velocity.y;
					total_velocity.z += remaining_velocity.z;
				}
			}

			connection->end_point->velocity_cm [index].x += total_velocity.x;
			connection->end_point->velocity_cm [index].y += total_velocity.y;
			connection->end_point->velocity_cm [index].z += total_velocity.z;
		}
		*/

		/////////////////////////////////////////////////////////////////////////////////////////
		//
		// Angularly
		//
		/////////////////////////////////////////////////////////////////////////////////////////

		if (!check_zero_3d_double_vector (&connection->angular_constraint))
		{
/*
			double
				dot,
				mag;

			double_vec3d
				constraint_torque;
*/
			// angular constraint in parents object space

			// limit childs torque to angular constraint vector
/*
			if (!check_zero_3d_double_vector (&connection->end_point->torque [index]))
			{
		
				// projects childs torque onto constraint vector 
	
				dot = get_3d_double_vector_dot_product (&connection->end_point->torque [index], &connection->angular_constraint);
		
				mag = get_3d_double_vector_magnitude (&connection->end_point->torque [index]);
		
				constraint_torque.x = mag * dot * connection->angular_constraint.x;
				constraint_torque.y = mag * dot * connection->angular_constraint.y;
				constraint_torque.z = mag * dot * connection->angular_constraint.z;
	
				connection->end_point->torque [index] = constraint_torque;
			}
*/
  			// projects childs angular_velocity onto constraint vector
/*
			if (!check_zero_3d_double_vector (&connection->end_point->angular_velocity [index]))
			{
	
				dot = get_3d_double_vector_dot_product (&connection->end_point->angular_velocity [index], &connection->angular_constraint);
		
				mag = get_3d_double_vector_magnitude (&connection->end_point->angular_velocity [index]);
		
				constraint_torque.x = mag * dot * connection->angular_constraint.x;
				constraint_torque.y = mag * dot * connection->angular_constraint.y;
				constraint_torque.z = mag * dot * connection->angular_constraint.z;
	
				connection->end_point->angular_velocity [index] = constraint_torque;
			}
			*/

  			// projects childs angular_momentum onto constraint vector
/*
			if (!check_zero_3d_double_vector (&connection->end_point->angular_momentum [index]))
			{
	
				dot = get_3d_double_vector_dot_product (&connection->end_point->angular_momentum [index], &childs_angular_constraint);
		
				mag = get_3d_double_vector_magnitude (&connection->end_point->angular_momentum [index]);
		
				constraint_torque.x = mag * dot * childs_angular_constraint.x;
				constraint_torque.y = mag * dot * childs_angular_constraint.y;
				constraint_torque.z = mag * dot * childs_angular_constraint.z;
	
				connection->end_point->angular_momentum [index] = constraint_torque;
			}
			*/
		}

		// Orientation

		if (!check_zero_3d_double_vector (&connection->angular_constraint))
		{

			double_vec3d
				cross1,
				angular_constraint;

			// angular constraint in parents object space

			multiply_double_matrix3x3_double_vec3d (&angular_constraint, connection->start_point->attitude, &connection->angular_constraint);

			get_3d_double_vector_cross_product ((double_vec3d *) &connection->end_point->attitude [2], &angular_constraint, (double_vec3d *) &connection->end_point->attitude [1] );

			get_3d_double_vector_cross_product (&cross1, &angular_constraint, (double_vec3d *) &connection->end_point->attitude [2] );

			connection->end_point->attitude [0][0] = angular_constraint.x;
			connection->end_point->attitude [0][1] = angular_constraint.y;
			connection->end_point->attitude [0][2] = angular_constraint.z;

			connection->end_point->attitude [1][0] = cross1.x;
			connection->end_point->attitude [1][1] = cross1.y;
			connection->end_point->attitude [1][2] = cross1.z;

			connection->end_point->attitude [2][0] = connection->end_point->attitude [2][0];
			connection->end_point->attitude [2][1] = connection->end_point->attitude [2][1];
			connection->end_point->attitude [2][2] = connection->end_point->attitude [2][2];
		}

	}
	// add parents torque onto children
/*
	if (!check_zero_3d_double_vector (&connection->start_point->torque [index]))
	{

		double_vec3d
			torque,
			cross1;

		double
			dot,
			mag;

		dot = get_3d_double_vector_dot_product (&constraint_vector, &connection->start_point->torque [index]);
		
		mag = get_3d_double_vector_magnitude (&connection->start_point->torque [index]);
		
		torque.x = mag * dot * constraint_vector.x;
		torque.y = mag * dot * constraint_vector.y;
		torque.z = mag * dot * constraint_vector.z;

		//torque.x += connection->start_point->torque [index].x;
		//torque.y += connection->start_point->torque [index].y;
		//torque.z += connection->start_point->torque [index].z;

		get_3d_double_vector_cross_product (&cross1, &start_point_position, &torque);

		add_constraint_force (connection->end_point, &cross1, &end_point_position);

		// debug
		{

			double_vec3d
				temp_position,
				temp_direction;

			temp_position = connection->end_point->position_cm [index];
			temp_position.x += start_point_position.x;
			temp_position.y += start_point_position.y;
			temp_position.z += start_point_position.z;

			temp_direction = cross1;

			normalise_any_3d_double_vector (&temp_direction);

			create_arrow ("TAIL_ARROW", &temp_position, &temp_direction, 5.0);

			//debug_log ("CONNECT: Torque [%f, %f, %f]", cross1.x, cross1.y, cross1.z);
		}
		// debug
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_connections (void)
{

	connection_type
		*current_connection = nullptr;

	current_connection = connection_list_head;

	while (current_connection)
	{

		draw_connection (current_connection);
/*
		if (current_connection->start_point)
		{

			draw_rigid_body_bounding_box (current_connection->start_point);
		}

		if (current_connection->end_point)
		{

			draw_rigid_body_bounding_box (current_connection->end_point);
		}
*/
		current_connection = current_connection->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_connection (connection_type *connection)
{

	rgb_colour
		cable_colour;

	double_vec3d
		start_position,
		end_position;

	vec3d
		points [2];

	if ((connection->start_point) && (connection->end_point))
	{

		if (connection->extension > 0.0)
		{
	
			cable_colour.r = 0.0;
			cable_colour.g = 20;
			cable_colour.b = 255;
			cable_colour.a = 255;
		}
		else
		{
	
			cable_colour.r = 255.0;
			cable_colour.g = 20;
			cable_colour.b = 0.0;
			cable_colour.a = 255;
		}

		multiply_double_matrix3x3_double_vec3d (&start_position, connection->start_point->attitude, &connection->start_point_position);
		multiply_double_matrix3x3_double_vec3d (&end_position, connection->end_point->attitude, &connection->end_point_position);

		points [0].x = connection->start_point->position_cm->x + start_position.x;
		points [0].y = connection->start_point->position_cm->y + start_position.y;
		points [0].z = connection->start_point->position_cm->z + start_position.z;

		points [1].x = connection->end_point->position_cm->x + end_position.x;
		points [1].y = connection->end_point->position_cm->y + end_position.y;
		points [1].z = connection->end_point->position_cm->z + end_position.z;

		insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double get_total_connection_energies (void)
{

	double_vec3d
		end_position,
		start_position,
		direction;
	
	double
		total_epe;

	connection_type
		*current_connection = nullptr;

	current_connection = connection_list_head;

	total_epe = 0.0;

	while (current_connection)
	{

		if ((current_connection->start_point) && (current_connection->end_point))
		{
	
			multiply_double_matrix3x3_double_vec3d (&start_position, current_connection->start_point->attitude, &current_connection->start_point_position);
			multiply_double_matrix3x3_double_vec3d (&end_position, current_connection->end_point->attitude, &current_connection->end_point_position);
		
			direction.x = (current_connection->end_point->position_cm->x + end_position.x) - (current_connection->start_point->position_cm->x + start_position.x);
			direction.y = (current_connection->end_point->position_cm->y + end_position.y) - (current_connection->start_point->position_cm->y + start_position.y);
			direction.z = (current_connection->end_point->position_cm->z + end_position.z) - (current_connection->start_point->position_cm->z + start_position.z);
	
			current_connection->extension = get_3d_double_vector_magnitude (&direction) - current_connection->natural_length;
	
			total_epe += (current_connection->moe * current_connection->extension * current_connection->extension) / (2.0 * current_connection->natural_length);
	
			//debug_log ("CONNECT: epe = %f", total_epe);
		}

		current_connection = current_connection->next;
	}

	return total_epe;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_rigid_body_angular_constraint (rigid_body_dynamics *rb, double_vec3d *constraint_vector)
{

	connection_type
		*connection = nullptr;
		
	connection = connection_list_head;

	while (connection)
	{

		if (connection->end_point == rb)
		{
	
			multiply_double_matrix3x3_double_vec3d (constraint_vector, connection->start_point->attitude, &connection->angular_constraint);

			return TRUE;
		}

		connection = connection->next;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
