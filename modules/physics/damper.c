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

damper_type
	*damper_list_head = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_damper (damper_type *damper, struct OBJECT *obj, rigid_body_dynamics *rb);;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_dampers (void)
{

	damper_type
		*destroy_damper = nullptr;

	while (damper_list_head)
	{

		destroy_damper = damper_list_head;

		damper_list_head = damper_list_head->next;

		free_mem (destroy_damper);
	}

	damper_list_head = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

damper_type *create_damper (float damping)
{

	damper_type
		*new_damper = nullptr;
	
	new_damper = (damper_type *) malloc_heap_mem (sizeof (damper_type));

	if (new_damper)
	{

		memset (new_damper, 0, sizeof (damper_type));

		new_damper->damping = damping;

		new_damper->next = damper_list_head;

		damper_list_head = new_damper;

		return new_damper;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_dampers (struct OBJECT *obj, rigid_body_dynamics *rb)
{

	damper_type
		*damper = nullptr;

	damper = damper_list_head;

	while (damper)
	{

		update_damper (damper, obj, rb);

		damper = damper->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_damper (damper_type *damper, struct OBJECT *obj, rigid_body_dynamics *rb)
{

	vec3d
		start_position,
		end_position,
		velocity,
		direction;

	float
		temp,
		damping;
	
	if ((!damper->start_point) && (!damper->end_point))
	{

		return;
	}

	multiply_matrix3x3_vec3d (&start_position, damper->start_point->rigid_body->attitude, &damper->start_point_position);
	multiply_matrix3x3_vec3d (&end_position, damper->end_point->rigid_body->attitude, &damper->end_point_position);
	
	direction.x = (damper->end_point->position->x + end_position.x) - (damper->start_point->position->x + start_position.x);
	direction.y = (damper->end_point->position->y + end_position.y) - (damper->start_point->position->y + start_position.y);
	direction.z = (damper->end_point->position->z + end_position.z) - (damper->start_point->position->z + start_position.z);

	velocity.x = (damper->end_point->rigid_body->velocity_cm [0].x + damper->end_point->rigid_body->angular_velocity [0].x) -
					(damper->start_point->rigid_body->velocity_cm [0].x + damper->start_point->rigid_body->angular_velocity [0].x);

	velocity.y = (damper->end_point->rigid_body->velocity_cm [0].y + damper->end_point->rigid_body->angular_velocity [0].y) -
					(damper->start_point->rigid_body->velocity_cm [0].y + damper->start_point->rigid_body->angular_velocity [0].y);

	velocity.z = (damper->end_point->rigid_body->velocity_cm [0].z + damper->end_point->rigid_body->angular_velocity [0].z) -
					(damper->start_point->rigid_body->velocity_cm [0].z + damper->start_point->rigid_body->angular_velocity [0].z);

	//velocity.x = damper->end_point->rigid_body [0].velocity_cm.x - damper->start_point->rigid_body [0].velocity_cm.x;
	//velocity.y = damper->end_point->rigid_body [0].velocity_cm.y - damper->start_point->rigid_body [0].velocity_cm.y;
	//velocity.z = damper->end_point->rigid_body [0].velocity_cm.z - damper->start_point->rigid_body [0].velocity_cm.z;

	temp = ((velocity.x * direction.x) + (velocity.y * direction.y) + (velocity.z * direction.z)) /
				((direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z));
	
	damping = damper->damping * temp * rb->mass;
	
	if (damper->start_point == obj)
	{

		add_dynamic_force (&rb->forces [0], &start_position, &direction, damping, "Damping", rb);
	}
	else if (damper->end_point == obj)
	{
	
		add_dynamic_force (&rb->forces [0], &end_position, &direction, -damping, "Damping", rb);
	}

	//debug_log ("DAMPER: %f : direction [%f, %f, %f]", get_3d_vector_magnitude (&direction), direction.x, direction.y, direction.z);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_dampers (void)
{

	damper_type
		*current_damper = nullptr;

	current_damper = damper_list_head;

	while (current_damper)
	{

		draw_damper (current_damper);

		current_damper = current_damper->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_damper (damper_type *damper)
{

	rgb_colour
		cable_colour;

	vec3d
		start_position,
		end_position,
		points [2];

	if ((damper->start_point) && (damper->end_point))
	{
	
		cable_colour.r = 0.0;
		cable_colour.g = 255;;
		cable_colour.b = 0.0;
		cable_colour.a = 255;

		multiply_matrix3x3_vec3d (&start_position, damper->start_point->rigid_body [0].attitude, &damper->start_point_position);
		multiply_matrix3x3_vec3d (&end_position, damper->end_point->rigid_body [0].attitude, &damper->end_point_position);

		points [0] = *damper->start_point->position;
		points [0].x += start_position.x;
		points [0].y += start_position.y;
		points [0].z += start_position.z;

		points [1] = *damper->end_point->position;
		points [1].x += end_position.x;
		points [1].y += end_position.y;
		points [1].z += end_position.z;

		insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
