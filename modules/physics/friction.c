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
	*friction_force_list_head = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_friction (rigid_body_dynamics *rb, int index)
{

	double
		dot,
		mag,
		fdotn,
		velocity_mag,
		coll_point_mag;

	int
		loop;

	double_vec3d
		torque,
		impulse,
		coll_point,
		linear_force,
		cross_result,
		*face_normal = nullptr,
		angular_force,
		point_velocity,
		constraint_force,
		constraint_vector;

	for (loop = 0; loop < rb->collided_flag; loop ++)
	{
	
		memset (&torque, 0, sizeof (double_vec3d));
	
		memset (&linear_force, 0, sizeof (double_vec3d));
	
		face_normal = &rb->collision_normal [loop];
		
		get_rigid_body_angular_constraint (rb, &constraint_vector);
	
		normalise_any_3d_double_vector (&constraint_vector);
	
		if (check_zero_3d_double_vector (&constraint_vector))
		{
	
			constraint_vector = rb->velocity_cm [0];
	
			normalise_any_3d_double_vector (&constraint_vector);
	
			if (check_zero_3d_double_vector (&constraint_vector))
			{
	
				constraint_vector = *((double_vec3d *) rb->attitude [2]);
			}
		}
	
		///////////////////////////////////////////////////////
		// probably should deal with the ground reaction force
		///////////////////////////////////////////////////////
	
		// max frictional force
	
		fdotn =  (face_normal->x * rb->linear_force [index].x) +
					(face_normal->y * rb->linear_force [index].y) +
					(face_normal->z * rb->linear_force [index].z);
	
		fdotn = fabs (fdotn * rb->coefficient_of_static_friction);
	
		// calculate force to oppose
	
		coll_point = rb->collision_point [loop];
	
		coll_point_mag = normalise_any_3d_double_vector (&coll_point);
	
		// get constraint forces & torques
	
		calculate_constraint_force_and_torque (rb, &linear_force, &torque, index);
	
		// add in rigid body forces & torques
	
		torque.x += rb->torque [index].x;
		torque.y += rb->torque [index].y;
		torque.z += rb->torque [index].z;
	
		linear_force.x += rb->linear_force [index].x;
		linear_force.y += 0.0;
		linear_force.z += rb->linear_force [index].z;
	
		// calculate impulse required to kill wheel slide (laterally) in 1 frame
	
		point_velocity.x = rb->velocity_cm [index].x;
		point_velocity.y = rb->velocity_cm [index].y;
		point_velocity.z = rb->velocity_cm [index].z;
		point_velocity.y = 0.0;
	
		dot = 0.0;
	
		if (!check_zero_3d_double_vector (&point_velocity))
		{
	
			dot = get_3d_double_vector_dot_product (&point_velocity, &constraint_vector);
		}
	
		velocity_mag = get_3d_double_vector_magnitude (&point_velocity);
	
		mag = velocity_mag * dot;// * rb->mass * dot * get_one_over_rigid_body_delta_time ();
	
		impulse.x = mag * constraint_vector.x;
		impulse.y = mag * constraint_vector.y;
		impulse.z = mag * constraint_vector.z;
	
		invert_3d_double_vector (&impulse);
	
		// debug
		{
	
			double_vec3d
				temp;
	
			// new velocity
	
			temp.x = point_velocity.x + impulse.x;
			temp.y = point_velocity.y + impulse.y;
			temp.z = point_velocity.z + impulse.z;
	
			mag = normalise_any_3d_double_vector (&temp);
	
			temp.x *= (velocity_mag - mag);
			temp.y *= (velocity_mag - mag);
			temp.z *= (velocity_mag - mag);
	
			impulse.x += temp.x;
			impulse.y += temp.y;
			impulse.z += temp.z;
		}
	
		mag = normalise_any_3d_double_vector (&impulse);
	
		if (mag > fdotn)
		{
	
			//debug_log ("FRICTION: %s impulse Wheelspinning %f (fdotn %f)", rb->name, mag, fdotn);
		}
	
		mag = min (mag, fdotn);
	
		impulse.x = mag * impulse.x * rb->mass * get_one_over_rigid_body_delta_time ();
		impulse.y = mag * impulse.y * rb->mass * get_one_over_rigid_body_delta_time ();
		impulse.z = mag * impulse.z * rb->mass * get_one_over_rigid_body_delta_time ();
	
		/////////////////////////////////////////////////////////////////////////////////
		// angular (linear forces are translated into angular forces)
		/////////////////////////////////////////////////////////////////////////////////
	
		// project onto angular constraint vector (tyres sideways friction)
	
		memset (&cross_result, 0, sizeof (double_vec3d));
	
		if (!check_zero_3d_double_vector (&linear_force))
		{
		
			dot = get_3d_double_vector_dot_product (&constraint_vector, &linear_force);
	
			mag = get_3d_double_vector_magnitude (&linear_force) * dot;
	
			constraint_force.x = mag * constraint_vector.x;
			constraint_force.y = mag * constraint_vector.y;
			constraint_force.z = mag * constraint_vector.z;
		
			linear_force.x -= constraint_force.x;
			linear_force.y -= constraint_force.y;
			linear_force.z -= constraint_force.z;
	
			if (fabs ((linear_force.x * linear_force.x) + (linear_force.y * linear_force.y) + (linear_force.z * linear_force.z)) > (fdotn * fdotn))
			{
			
				mag = normalise_any_3d_double_vector (&linear_force);
	
				if (mag > fdotn)
				{
	
					//debug_log ("FRICTION: Linear %s Wheelspinning %f (fdotn %f)", rb->name, mag, fdotn);
				}
			
				mag = min (mag, fdotn);
			
				linear_force.x *= mag;
				linear_force.y *= mag;
				linear_force.z *= mag;
			}
		
			invert_3d_double_vector (&linear_force);
		
			get_3d_double_vector_cross_product (&cross_result, &linear_force, &rb->collision_point [loop]);
	
			//debug_log ("FRICTION: collision point [%f, %f, %f]", rb->collision_point.x, rb->collision_point.y, rb->collision_point.z);
		}
	
		/////////////////////////////////////////////////////////////////////////////////
		// linear (angular forces are translated into linear forces)
		/////////////////////////////////////////////////////////////////////////////////
	
		get_3d_double_vector_cross_product (&angular_force, &coll_point, &torque);
	
		angular_force.x /= coll_point_mag;
		angular_force.y /= coll_point_mag;
		angular_force.z /= coll_point_mag;
	
		angular_force.x += constraint_force.x;
		angular_force.y += constraint_force.y;
		angular_force.z += constraint_force.z;
	
		invert_3d_double_vector (&angular_force);
	
		if (fabs ((angular_force.x * angular_force.x) + (angular_force.y * angular_force.y) + (angular_force.z * angular_force.z)) > (fdotn * fdotn))
		{
		
			mag = normalise_any_3d_double_vector (&angular_force);
	
			if (mag > fdotn)
			{
	
				//debug_log ("FRICTION: %s Angular Wheelspinning %f (fdotn %f)", rb->name, mag, fdotn);
			}
		
			mag = min (mag, fdotn);
		
			angular_force.x *= mag;
			angular_force.y *= mag;
			angular_force.z *= mag;
		}
	
		// apply impulse
	
		angular_force.x += impulse.x;
		angular_force.y += 0.0;
		angular_force.z += impulse.z;
	
		//
		// results
		//
	
		#if DEBUG_MODULE
	/*
		{
	
			double_vec3d
				point_velocity,
				temp;
	
			get_3d_double_vector_cross_product (&point_velocity, &rb->angular_velocity [index], &rb->collision_point);
	
			point_velocity.x -= rb->velocity_cm [index].x;
			point_velocity.y -= rb->velocity_cm [index].y;
			point_velocity.z -= rb->velocity_cm [index].z;
	
			point_velocity.y = 0.0;
	
			debug_log ("BODY: 	%s Relative Wheel speed %f [%f, %f, %f]. Impulse %f [%f, %f, %f]", rb->name, get_3d_double_vector_magnitude (&point_velocity), point_velocity.x, point_velocity.y, point_velocity.z, get_3d_double_vector_magnitude (&impulse), impulse.x, impulse.y, impulse.z);
	
			get_3d_double_vector_cross_product (&temp, &angular_force, &rb->collision_point);
	
			//debug_log ("BODY: torque [%f, %f, %f], calc torque from linear force [%f, %f, %f]", torque.x, torque.y, torque.z, temp.x, temp.y, temp.z);
		}
	*/
		#endif
	
		add_friction_force (rb, &angular_force, &cross_result);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_friction_force (rigid_body_dynamics *rb, double_vec3d *force, double_vec3d *torque)
{

	constraint_forces
		*new_friction = nullptr;

	new_friction = (constraint_forces *) malloc_heap_mem (sizeof (constraint_forces));

	new_friction->owner = rb;
	new_friction->force = *force;
	new_friction->torque = *torque;

	new_friction->next = friction_force_list_head;

	friction_force_list_head = new_friction;

	#if DEBUG_MODULE

	//if (rb == camera_object->rigid_body)
	{
	
			debug_log ("BODY: FRICTION: adding %s friction force [%f, %f, %f] and torque [%f, %f, %f]",
						rb->name,
						force->x, force->y, force->z,
						torque->x, torque->y, torque->z);
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_friction_forces (int index)
{

	constraint_forces
		*destroy_cf = nullptr,
		*cf = nullptr;

	cf = friction_force_list_head;

	while (cf)
	{

		cf->owner->linear_force [index].x += cf->force.x;
		cf->owner->linear_force [index].y += cf->force.y;
		cf->owner->linear_force [index].z += cf->force.z;

		cf->owner->torque [index].x += cf->torque.x;
		cf->owner->torque [index].y += cf->torque.y;
		cf->owner->torque [index].z += cf->torque.z;

		#if DEBUG_MODULE

		if (cf->owner == camera_object->rigid_body)
		{
/*	
			double_vec3d
				temp_direction,
				temp_position;
	
			temp_position.x = cf->owner->position_cm [0].x;
			temp_position.y = cf->owner->position_cm [0].y;
			temp_position.z = cf->owner->position_cm [0].z;
	
			temp_direction = cf->force;
			normalise_any_3d_double_vector (&temp_direction);
	
			create_arrow ("TAIL_ARROW", &temp_position, &temp_direction, 6.0);
*/
			debug_log ("BODY: FRICTION: Applying %s force [%f, %f, %f] torque [%f, %f, %f]",
						cf->owner->name,
						cf->force.x, cf->force.y, cf->force.z,
						cf->torque.x, cf->torque.y, cf->torque.z);

		}

		#endif

		destroy_cf = cf;

		cf = cf->next;

		free_mem (destroy_cf);
	}

	friction_force_list_head = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_friction_forces (void)
{

	constraint_forces
		*destroy_cf = nullptr,
		*cf = nullptr;

	cf = friction_force_list_head;

	while (cf)
	{

		destroy_cf = cf;

		cf = cf->next;

		free_mem (destroy_cf);
	}

	friction_force_list_head = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_friction_force_and_torque (rigid_body_dynamics *rb, double_vec3d *force, double_vec3d *torque, int index)
{

	constraint_forces
		*cf = nullptr;

	force->x = 0.0;
	force->y = 0.0;
	force->z = 0.0;

	torque->x = 0.0;
	torque->y = 0.0;
	torque->z = 0.0;

	cf = friction_force_list_head;

	while (cf)
	{

		if (cf->owner == rb)
		{
	
			force->x += cf->force.x;
			force->y += cf->force.y;
			force->z += cf->force.z;

			torque->x += cf->torque.x;
			torque->y += cf->torque.y;
			torque->z += cf->torque.z;
		}

		cf = cf->next;
	}

	#if DEBUG_MODULE

	debug_log ("BODY: calculating friction on %s force [%f, %f, %f] torque [%f, %f, %f]", rb->name, force->x, force->y, force->z, torque->x, torque->y, torque->z);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

