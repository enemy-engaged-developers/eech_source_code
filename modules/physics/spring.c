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

spring_type
	*spring_list_head;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_spring (spring_type *spring, struct OBJECT *object, rigid_body_dynamics *rb);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_springs (void)
{

	spring_type
		*destroy_spring;

	while (spring_list_head)
	{

		destroy_spring = spring_list_head;

		spring_list_head = spring_list_head->next;

		free_mem (destroy_spring);
	}

	spring_list_head = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

spring_type *create_spring (float length, float max_compression_percentage, float max_extension_percentage, float moe)
{

	spring_type
		*new_spring;
	
	new_spring = (spring_type *) malloc_heap_mem (sizeof (spring_type));

	if (new_spring)
	{

		ASSERT (moe >= 0.0);
		ASSERT (length >= 0.0);
		ASSERT (max_extension_percentage >= 0.0);
		ASSERT (max_compression_percentage >= 0.0);

		memset (new_spring, 0, sizeof (spring_type));

		new_spring->moe = moe;

		new_spring->length = length;

		new_spring->moe_div_length = moe / length;

		new_spring->max_extension_percentage = max_extension_percentage;

		new_spring->max_compression_percentage = max_compression_percentage;

		new_spring->next = spring_list_head;

		spring_list_head = new_spring;

		return new_spring;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_springs (struct OBJECT *obj, rigid_body_dynamics *rb)
{

	spring_type
		*current_spring;

	current_spring = spring_list_head;

	while (current_spring)
	{

		update_spring (current_spring, obj, rb);

		current_spring = current_spring->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_spring (spring_type *spring, struct OBJECT *obj, rigid_body_dynamics *rb)
{

	vec3d
		start_position,
		end_position,
		direction;

	float
		inverse_actual_length;
		//max_extension,
		//max_compression;
	
	if ((!spring->start_point) && (!spring->end_point))
	{

		return;
	}

	// calculate tension in spring

	//max_extension = spring->length * spring->max_extension_percentage;
	//max_compression = -(spring->length * spring->max_compression_percentage);
	//spring->extension = bound (spring->extension, max_compression, max_extension);

	// apply to both ends

	multiply_matrix3x3_vec3d (&start_position, spring->start_point->rigid_body->attitude, &spring->start_point_position);
	multiply_matrix3x3_vec3d (&end_position, spring->end_point->rigid_body->attitude, &spring->end_point_position);
	
	direction.x = (spring->end_point->position->x + end_position.x) - (spring->start_point->position->x + start_position.x);
	direction.y = (spring->end_point->position->y + end_position.y) - (spring->start_point->position->y + start_position.y);
	direction.z = (spring->end_point->position->z + end_position.z) - (spring->start_point->position->z + start_position.z);

	inverse_actual_length = get_inverse_square_root ((direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z));

	spring->tension = spring->moe_div_length - (spring->moe * inverse_actual_length);
	
	if (spring->start_point == obj)
	{
	
		add_dynamic_force (&rb->forces [0], &start_position, &direction, (spring->tension * spring->start_point->rigid_body->mass) * 0.5, "Spring", rb);
	}
	else if (spring->end_point == obj)
	{
	
		add_dynamic_force (&rb->forces [0], &end_position, &direction, -(spring->tension * spring->end_point->rigid_body->mass) * 0.5, "Spring", rb);
	}

	//debug_log ("SPRING: extension = %f, moe = %f, tension = %f", spring->extension, spring->moe, spring->tension);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_springs (void)
{

	spring_type
		*current_spring;

	current_spring = spring_list_head;

	while (current_spring)
	{

		draw_spring (current_spring);

		current_spring = current_spring->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_spring (spring_type *spring)
{

	rgb_colour
		cable_colour;

	vec3d
		start_position,
		end_position,
		points [2];

	if ((spring->start_point) && (spring->end_point))
	{

		cable_colour.r = bound (128 + (spring->extension / spring->length) * 128, 0, 255);
		cable_colour.g = 20;
		cable_colour.b = 255;
		cable_colour.a = 255;

		multiply_matrix3x3_vec3d (&start_position, spring->start_point->rigid_body [0].attitude, &spring->start_point_position);
		multiply_matrix3x3_vec3d (&end_position, spring->end_point->rigid_body [0].attitude, &spring->end_point_position);

		points [0] = *spring->start_point->position;
		points [0].x += start_position.x;
		points [0].y += start_position.y;
		points [0].z += start_position.z;

		points [1] = *spring->end_point->position;
		points [1].x += end_position.x;
		points [1].y += end_position.y;
		points [1].z += end_position.z;

		insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float calculate_total_spring_energy (void)
{

	float
		epe;

	spring_type
		*current_spring;

	current_spring = spring_list_head;

	epe = 0.0;

	while (current_spring)
	{

		epe += (current_spring->moe * current_spring->extension * current_spring->extension) / (2.0 * current_spring->length);

		//debug_log ("SPRING: Energy = %f", current_spring->moe * current_spring->extension * current_spring->extension) / (2.0 * current_spring->length);

		current_spring = current_spring->next;
	}

	return epe;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
