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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE										0

#define DEBUG_MODULE_ENABLE_COLLISION_BOX_MISS	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define COLLISION_FACE_HIT_COLOUR	(sys_col_red)
#define COLLISION_FACE_MISS_COLOUR	(sys_col_white)
#define COLLISION_BOX_HIT_COLOUR		(sys_col_amber)
#define COLLISION_BOX_MISS_COLOUR	(sys_col_yellow)
#define LOS_COLOUR						(sys_col_blue)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	draw_collision_boxes = FALSE;

float
	collision_box_lifetime = 2.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TERRAIN COLLISION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

terrain_classes get_ground_impact_point (vec3d *above_ground, vec3d *below_ground, vec3d *ground_impact_point)
{
	float
		length;

	vec3d
		point_a,
		point_b,
		point_c;

	ASSERT (above_ground);

	ASSERT (below_ground);

	ASSERT (ground_impact_point);

	ASSERT (point_above_ground (above_ground));

	ASSERT (point_inside_map_area (above_ground));

	ASSERT (!point_above_ground (below_ground));

	ASSERT (point_inside_map_area (below_ground));

	point_a = *above_ground;

	point_b = *below_ground;

	length = 100.0;

	while (length > 1.0)
	{
		point_c.x = (point_a.x + point_b.x) * 0.5;
		point_c.y = (point_a.y + point_b.y) * 0.5;
		point_c.z = (point_a.z + point_b.z) * 0.5;

		if (point_above_ground (&point_c))
		{
			point_a = point_c;
		}
		else
		{
			point_b = point_c;
		}

		length = get_sqr_3d_range (&point_a, &point_b);
	}

	point_b.y = get_3d_terrain_point_data (point_b.x, point_b.z, NULL);

	*ground_impact_point = point_b;

	return (get_terrain_type_class (get_3d_terrain_point_data_type (NULL)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// OBJECT COLLISION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_min_max_box (vec3d *min_position, vec3d *max_position, rgb_colour colour)
{
	vec3d
		p1,
		p2;

	ASSERT (min_position);

	ASSERT (max_position);

	p1.x = min_position->x;
	p1.y = min_position->y;
	p1.z = min_position->z;

	p2.x = min_position->x;
	p2.y = max_position->y;
	p2.z = min_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = min_position->x;
	p1.y = max_position->y;
	p1.z = min_position->z;

	p2.x = max_position->x;
	p2.y = max_position->y;
	p2.z = min_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = max_position->x;
	p1.y = max_position->y;
	p1.z = min_position->z;

	p2.x = max_position->x;
	p2.y = min_position->y;
	p2.z = min_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = max_position->x;
	p1.y = min_position->y;
	p1.z = min_position->z;

	p2.x = min_position->x;
	p2.y = min_position->y;
	p2.z = min_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = min_position->x;
	p1.y = min_position->y;
	p1.z = max_position->z;

	p2.x = min_position->x;
	p2.y = max_position->y;
	p2.z = max_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = min_position->x;
	p1.y = max_position->y;
	p1.z = max_position->z;

	p2.x = max_position->x;
	p2.y = max_position->y;
	p2.z = max_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = max_position->x;
	p1.y = max_position->y;
	p1.z = max_position->z;

	p2.x = max_position->x;
	p2.y = min_position->y;
	p2.z = max_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = max_position->x;
	p1.y = min_position->y;
	p1.z = max_position->z;

	p2.x = min_position->x;
	p2.y = min_position->y;
	p2.z = max_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = min_position->x;
	p1.y = min_position->y;
	p1.z = min_position->z;

	p2.x = min_position->x;
	p2.y = min_position->y;
	p2.z = max_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = min_position->x;
	p1.y = max_position->y;
	p1.z = min_position->z;

	p2.x = min_position->x;
	p2.y = max_position->y;
	p2.z = max_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = max_position->x;
	p1.y = max_position->y;
	p1.z = min_position->z;

	p2.x = max_position->x;
	p2.y = max_position->y;
	p2.z = max_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);

	p1.x = max_position->x;
	p1.y = min_position->y;
	p1.z = min_position->z;

	p2.x = max_position->x;
	p2.y = min_position->y;
	p2.z = max_position->z;

	create_debug_3d_line (&p1, &p2, colour, collision_box_lifetime);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_3d_line_triangle_face_intersection
(
	vec3d *source_old_position,
	vec3d *source_new_position,
	vec3d *p1,
	vec3d *p2,
	vec3d *p3,
	vec3d *source_intercept_point,
	vec3d *face_normal
)
{
	ASSERT (source_old_position);

	ASSERT (source_new_position);

	ASSERT (p1);

	ASSERT (p2);

	ASSERT (p3);

	ASSERT (source_intercept_point);

	ASSERT (face_normal);

	if (get_3d_line_triangle_intersection (source_old_position, source_new_position, p1, p2, p3, source_intercept_point, face_normal))
	{
		if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_debug_3d_line (p1, p2, COLLISION_FACE_HIT_COLOUR, collision_box_lifetime);
			create_debug_3d_line (p2, p3, COLLISION_FACE_HIT_COLOUR, collision_box_lifetime);
			create_debug_3d_line (p3, p1, COLLISION_FACE_HIT_COLOUR, collision_box_lifetime);
		}

		return (TRUE);
	}

	if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
	{
		create_debug_3d_line (p1, p2, COLLISION_FACE_MISS_COLOUR, collision_box_lifetime);
		create_debug_3d_line (p2, p3, COLLISION_FACE_MISS_COLOUR, collision_box_lifetime);
		create_debug_3d_line (p3, p1, COLLISION_FACE_MISS_COLOUR, collision_box_lifetime);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_3d_line_quad_face_intersection
(
	vec3d *source_old_position,
	vec3d *source_new_position,
	vec3d *p1,
	vec3d *p2,
	vec3d *p3,
	vec3d *p4,
	vec3d *source_intercept_point,
	vec3d *face_normal
)
{
	ASSERT (source_old_position);

	ASSERT (source_new_position);

	ASSERT (p1);

	ASSERT (p2);

	ASSERT (p3);

	ASSERT (p4);

	ASSERT (source_intercept_point);

	ASSERT (face_normal);

	if (get_3d_line_quad_intersection (source_old_position, source_new_position, p1, p2, p3, p4, source_intercept_point, face_normal))
	{
		if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_debug_3d_line (p1, p2, COLLISION_FACE_HIT_COLOUR, collision_box_lifetime);
			create_debug_3d_line (p2, p3, COLLISION_FACE_HIT_COLOUR, collision_box_lifetime);
			create_debug_3d_line (p3, p4, COLLISION_FACE_HIT_COLOUR, collision_box_lifetime);
			create_debug_3d_line (p4, p1, COLLISION_FACE_HIT_COLOUR, collision_box_lifetime);
			create_debug_3d_line (p1, p3, COLLISION_FACE_HIT_COLOUR, collision_box_lifetime);
		}

		return (TRUE);
	}

	if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
	{
		create_debug_3d_line (p1, p2, COLLISION_FACE_MISS_COLOUR, collision_box_lifetime);
		create_debug_3d_line (p2, p3, COLLISION_FACE_MISS_COLOUR, collision_box_lifetime);
		create_debug_3d_line (p3, p4, COLLISION_FACE_MISS_COLOUR, collision_box_lifetime);
		create_debug_3d_line (p4, p1, COLLISION_FACE_MISS_COLOUR, collision_box_lifetime);
		create_debug_3d_line (p1, p3, COLLISION_FACE_MISS_COLOUR, collision_box_lifetime);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int accurate_stationary_bounding_box_collision_test
(
	entity *target,
	vec3d *source_old_position,
	vec3d *source_new_position,
	object_3d_index_numbers index_3d_object,
	object_3d_bounds *bounding_box,
	vec3d *source_intercept_point,
	vec3d *face_normal
)
{
	int
		depth;

	float
		heading;

	vec3d
		*position,
		terrain_face_normal,
		p[8];

	matrix3x3
		attitude;

	ASSERT (target);

	ASSERT (source_old_position);

	ASSERT (source_new_position);

	ASSERT ((index_3d_object > OBJECT_3D_INVALID_OBJECT_INDEX) && (index_3d_object < OBJECT_3D_LAST));

	ASSERT (bounding_box);

	ASSERT (source_intercept_point);

	ASSERT (face_normal);

	//
	// get target position and attitude
	//

	if (get_local_entity_int_value (target, INT_TYPE_COLLISION_TEST_MOBILE))
	{
		position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		get_local_entity_attitude_matrix (target, attitude);
	}
	else if (get_local_entity_int_value (target, INT_TYPE_COLLISION_TEST_FIXED))
	{
		ASSERT (get_local_entity_type (target) != ENTITY_TYPE_CITY);

		position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		heading = get_local_entity_float_value (target, FLOAT_TYPE_HEADING);

		if (get_local_entity_int_value (target, INT_TYPE_ALIGN_WITH_TERRAIN))
		{
			get_3d_terrain_face_normal (&terrain_face_normal, position->x, position->z);

			get_3d_transformation_matrix_from_face_normal_and_heading (attitude, &terrain_face_normal, heading);
		}
		else
		{
			get_3d_transformation_matrix (attitude, heading, 0.0, 0.0);
		}
	}
	else
	{
		debug_fatal ("Invalid target (type = %s)", get_local_entity_type_name (target));
	}

	depth = 0;

	if (get_object_3d_collision_object_geometry_triangle (index_3d_object, p, depth++))
	{
		////////////////////////////////////////
		//
		// COLLISION TEST WITH GEOMETRY TRIANGLES
		//
		////////////////////////////////////////

		do
		{
			multiply_matrix3x3_vec3d (&p[0], attitude, &p[0]);
			multiply_matrix3x3_vec3d (&p[1], attitude, &p[1]);
			multiply_matrix3x3_vec3d (&p[2], attitude, &p[2]);

			p[0].x += position->x;
			p[0].y += position->y;
			p[0].z += position->z;

			p[1].x += position->x;
			p[1].y += position->y;
			p[1].z += position->z;

			p[2].x += position->x;
			p[2].y += position->y;
			p[2].z += position->z;

			if (get_3d_line_triangle_face_intersection (source_old_position, source_new_position, &p[0], &p[1], &p[2], source_intercept_point, face_normal))
			{
				return (TRUE);
			}
		}
		while (get_object_3d_collision_object_geometry_triangle (index_3d_object, p, depth++));
	}
	else
	{
		////////////////////////////////////////
		//
		// COLLISION TEST WITH BOUNDING BOX
		//
		////////////////////////////////////////

		//
		// rotate bounding box
		//

		p[0].x = bounding_box->xmin;
		p[0].y = bounding_box->ymin;
		p[0].z = bounding_box->zmin;

		multiply_matrix3x3_vec3d (&p[0], attitude, &p[0]);

		p[0].x += position->x;
		p[0].y += position->y;
		p[0].z += position->z;

		p[1].x = bounding_box->xmin;
		p[1].y = bounding_box->ymax;
		p[1].z = bounding_box->zmin;

		multiply_matrix3x3_vec3d (&p[1], attitude, &p[1]);

		p[1].x += position->x;
		p[1].y += position->y;
		p[1].z += position->z;

		p[2].x = bounding_box->xmax;
		p[2].y = bounding_box->ymax;
		p[2].z = bounding_box->zmin;

		multiply_matrix3x3_vec3d (&p[2], attitude, &p[2]);

		p[2].x += position->x;
		p[2].y += position->y;
		p[2].z += position->z;

		p[3].x = bounding_box->xmax;
		p[3].y = bounding_box->ymin;
		p[3].z = bounding_box->zmin;

		multiply_matrix3x3_vec3d (&p[3], attitude, &p[3]);

		p[3].x += position->x;
		p[3].y += position->y;
		p[3].z += position->z;

		p[4].x = bounding_box->xmin;
		p[4].y = bounding_box->ymin;
		p[4].z = bounding_box->zmax;

		multiply_matrix3x3_vec3d (&p[4], attitude, &p[4]);

		p[4].x += position->x;
		p[4].y += position->y;
		p[4].z += position->z;

		p[5].x = bounding_box->xmin;
		p[5].y = bounding_box->ymax;
		p[5].z = bounding_box->zmax;

		multiply_matrix3x3_vec3d (&p[5], attitude, &p[5]);

		p[5].x += position->x;
		p[5].y += position->y;
		p[5].z += position->z;

		p[6].x = bounding_box->xmax;
		p[6].y = bounding_box->ymax;
		p[6].z = bounding_box->zmax;

		multiply_matrix3x3_vec3d (&p[6], attitude, &p[6]);

		p[6].x += position->x;
		p[6].y += position->y;
		p[6].z += position->z;

		p[7].x = bounding_box->xmax;
		p[7].y = bounding_box->ymin;
		p[7].z = bounding_box->zmax;

		multiply_matrix3x3_vec3d (&p[7], attitude, &p[7]);

		p[7].x += position->x;
		p[7].y += position->y;
		p[7].z += position->z;

		//
		// collision test each face of bounding box
		//

		if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p[0], &p[1], &p[2], &p[3], source_intercept_point, face_normal))
		{
			return (TRUE);
		}

		if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p[3], &p[2], &p[6], &p[7], source_intercept_point, face_normal))
		{
			return (TRUE);
		}

		if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p[7], &p[6], &p[5], &p[4], source_intercept_point, face_normal))
		{
			return (TRUE);
		}

		if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p[4], &p[5], &p[1], &p[0], source_intercept_point, face_normal))
		{
			return (TRUE);
		}

		if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p[1], &p[5], &p[6], &p[2], source_intercept_point, face_normal))
		{
			return (TRUE);
		}

		if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p[0], &p[4], &p[7], &p[3], source_intercept_point, face_normal))
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TEST_OLD_POSITION	(1)
#define TEST_MID_POSITION	(2)
#define TEST_NEW_POSITION	(4)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int accurate_moving_bounding_box_collision_test
(
	entity *target,
	vec3d *source_old_position,
	vec3d *source_new_position,
	vec3d *target_old_position,
	vec3d *target_new_position,
	object_3d_index_numbers index_3d_object,
	object_3d_bounds *bounding_box,
	vec3d *source_intercept_point,
	vec3d *face_normal
)
{
	int
		depth,
		test_flags;

	float
		true_velocity,
		body_length;

	vec3d
		p[8],
		q[8],
		target_mid_position;

	matrix3x3
		*attitude;

	ASSERT (target);

	ASSERT (source_old_position);

	ASSERT (source_new_position);

	ASSERT (target_old_position);

	ASSERT (target_new_position);

	ASSERT ((index_3d_object > OBJECT_3D_INVALID_OBJECT_INDEX) && (index_3d_object < OBJECT_3D_LAST));

	ASSERT (bounding_box);

	ASSERT (source_intercept_point);

	ASSERT (face_normal);

	ASSERT (get_local_entity_int_value (target, INT_TYPE_COLLISION_TEST_MOBILE));

	attitude = get_local_entity_attitude_matrix_ptr (target);

	//
	// determine which tests are required using target velocity and body length
	//

	true_velocity = get_local_entity_vec3d_magnitude (target, VEC3D_TYPE_MOTION_VECTOR);

	body_length = bounding_box->zmax - bounding_box->zmin;

	if (true_velocity > body_length)
	{
		test_flags = TEST_OLD_POSITION + TEST_MID_POSITION + TEST_NEW_POSITION;
	}
	else if (true_velocity > (body_length * 0.25))
	{
		test_flags = TEST_OLD_POSITION + TEST_NEW_POSITION;
	}
	else
	{
		test_flags = TEST_MID_POSITION;
	}

	depth = 0;

	if (get_object_3d_collision_object_geometry_triangle (index_3d_object, p, depth++))
	{
		////////////////////////////////////////
		//
		// COLLISION TEST WITH GEOMETRY TRIANGLES
		//
		////////////////////////////////////////

		do
		{
			multiply_matrix3x3_vec3d (&p[0], *attitude, &p[0]);
			multiply_matrix3x3_vec3d (&p[1], *attitude, &p[1]);
			multiply_matrix3x3_vec3d (&p[2], *attitude, &p[2]);

			//
			// collision test triangle at old position
			//

			if (test_flags & TEST_OLD_POSITION)
			{
				q[0].x = p[0].x + target_old_position->x;
				q[0].y = p[0].y + target_old_position->y;
				q[0].z = p[0].z + target_old_position->z;

				q[1].x = p[1].x + target_old_position->x;
				q[1].y = p[1].y + target_old_position->y;
				q[1].z = p[1].z + target_old_position->z;

				q[2].x = p[2].x + target_old_position->x;
				q[2].y = p[2].y + target_old_position->y;
				q[2].z = p[2].z + target_old_position->z;

				if (get_3d_line_triangle_face_intersection (source_old_position, source_new_position, &q[0], &q[1], &q[2], source_intercept_point, face_normal))
				{
					return (TRUE);
				}
			}

			//
			// collision test triangle at new position
			//

			if (test_flags & TEST_NEW_POSITION)
			{
				q[0].x = p[0].x + target_new_position->x;
				q[0].y = p[0].y + target_new_position->y;
				q[0].z = p[0].z + target_new_position->z;

				q[1].x = p[1].x + target_new_position->x;
				q[1].y = p[1].y + target_new_position->y;
				q[1].z = p[1].z + target_new_position->z;

				q[2].x = p[2].x + target_new_position->x;
				q[2].y = p[2].y + target_new_position->y;
				q[2].z = p[2].z + target_new_position->z;

				if (get_3d_line_triangle_face_intersection (source_old_position, source_new_position, &q[0], &q[1], &q[2], source_intercept_point, face_normal))
				{
					return (TRUE);
				}
			}

			//
			// collision test triangle at mid position
			//

			if (test_flags & TEST_MID_POSITION)
			{
				target_mid_position.x = (target_old_position->x + target_new_position->x) * 0.5;
				target_mid_position.y = (target_old_position->y + target_new_position->y) * 0.5;
				target_mid_position.z = (target_old_position->z + target_new_position->z) * 0.5;

				q[0].x = p[0].x + target_mid_position.x;
				q[0].y = p[0].y + target_mid_position.y;
				q[0].z = p[0].z + target_mid_position.z;

				q[1].x = p[1].x + target_mid_position.x;
				q[1].y = p[1].y + target_mid_position.y;
				q[1].z = p[1].z + target_mid_position.z;

				q[2].x = p[2].x + target_mid_position.x;
				q[2].y = p[2].y + target_mid_position.y;
				q[2].z = p[2].z + target_mid_position.z;

				if (get_3d_line_triangle_face_intersection (source_old_position, source_new_position, &q[0], &q[1], &q[2], source_intercept_point, face_normal))
				{
					return (TRUE);
				}
			}
		}
		while (get_object_3d_collision_object_geometry_triangle (index_3d_object, p, depth++));
	}
	else
	{
		////////////////////////////////////////
		//
		// COLLISION TEST WITH BOUNDING BOX
		//
		////////////////////////////////////////

		//
		// rotate bounding box
		//

		p[0].x = bounding_box->xmin;
		p[0].y = bounding_box->ymin;
		p[0].z = bounding_box->zmin;

		multiply_matrix3x3_vec3d (&p[0], *attitude, &p[0]);

		p[1].x = bounding_box->xmin;
		p[1].y = bounding_box->ymax;
		p[1].z = bounding_box->zmin;

		multiply_matrix3x3_vec3d (&p[1], *attitude, &p[1]);

		p[2].x = bounding_box->xmax;
		p[2].y = bounding_box->ymax;
		p[2].z = bounding_box->zmin;

		multiply_matrix3x3_vec3d (&p[2], *attitude, &p[2]);

		p[3].x = bounding_box->xmax;
		p[3].y = bounding_box->ymin;
		p[3].z = bounding_box->zmin;

		multiply_matrix3x3_vec3d (&p[3], *attitude, &p[3]);

		p[4].x = bounding_box->xmin;
		p[4].y = bounding_box->ymin;
		p[4].z = bounding_box->zmax;

		multiply_matrix3x3_vec3d (&p[4], *attitude, &p[4]);

		p[5].x = bounding_box->xmin;
		p[5].y = bounding_box->ymax;
		p[5].z = bounding_box->zmax;

		multiply_matrix3x3_vec3d (&p[5], *attitude, &p[5]);

		p[6].x = bounding_box->xmax;
		p[6].y = bounding_box->ymax;
		p[6].z = bounding_box->zmax;

		multiply_matrix3x3_vec3d (&p[6], *attitude, &p[6]);

		p[7].x = bounding_box->xmax;
		p[7].y = bounding_box->ymin;
		p[7].z = bounding_box->zmax;

		multiply_matrix3x3_vec3d (&p[7], *attitude, &p[7]);

		//
		// collision test bounding box at old position
		//

		if (test_flags & TEST_OLD_POSITION)
		{
			q[0].x = p[0].x + target_old_position->x;
			q[0].y = p[0].y + target_old_position->y;
			q[0].z = p[0].z + target_old_position->z;

			q[1].x = p[1].x + target_old_position->x;
			q[1].y = p[1].y + target_old_position->y;
			q[1].z = p[1].z + target_old_position->z;

			q[2].x = p[2].x + target_old_position->x;
			q[2].y = p[2].y + target_old_position->y;
			q[2].z = p[2].z + target_old_position->z;

			q[3].x = p[3].x + target_old_position->x;
			q[3].y = p[3].y + target_old_position->y;
			q[3].z = p[3].z + target_old_position->z;

			q[4].x = p[4].x + target_old_position->x;
			q[4].y = p[4].y + target_old_position->y;
			q[4].z = p[4].z + target_old_position->z;

			q[5].x = p[5].x + target_old_position->x;
			q[5].y = p[5].y + target_old_position->y;
			q[5].z = p[5].z + target_old_position->z;

			q[6].x = p[6].x + target_old_position->x;
			q[6].y = p[6].y + target_old_position->y;
			q[6].z = p[6].z + target_old_position->z;

			q[7].x = p[7].x + target_old_position->x;
			q[7].y = p[7].y + target_old_position->y;
			q[7].z = p[7].z + target_old_position->z;

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[0], &q[1], &q[2], &q[3], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[3], &q[2], &q[6], &q[7], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[7], &q[6], &q[5], &q[4], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[4], &q[5], &q[1], &q[0], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[1], &q[5], &q[6], &q[2], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[0], &q[4], &q[7], &q[3], source_intercept_point, face_normal))
			{
				return (TRUE);
			}
		}

		//
		// collision test bounding box at new position
		//

		if (test_flags & TEST_NEW_POSITION)
		{
			q[0].x = p[0].x + target_new_position->x;
			q[0].y = p[0].y + target_new_position->y;
			q[0].z = p[0].z + target_new_position->z;

			q[1].x = p[1].x + target_new_position->x;
			q[1].y = p[1].y + target_new_position->y;
			q[1].z = p[1].z + target_new_position->z;

			q[2].x = p[2].x + target_new_position->x;
			q[2].y = p[2].y + target_new_position->y;
			q[2].z = p[2].z + target_new_position->z;

			q[3].x = p[3].x + target_new_position->x;
			q[3].y = p[3].y + target_new_position->y;
			q[3].z = p[3].z + target_new_position->z;

			q[4].x = p[4].x + target_new_position->x;
			q[4].y = p[4].y + target_new_position->y;
			q[4].z = p[4].z + target_new_position->z;

			q[5].x = p[5].x + target_new_position->x;
			q[5].y = p[5].y + target_new_position->y;
			q[5].z = p[5].z + target_new_position->z;

			q[6].x = p[6].x + target_new_position->x;
			q[6].y = p[6].y + target_new_position->y;
			q[6].z = p[6].z + target_new_position->z;

			q[7].x = p[7].x + target_new_position->x;
			q[7].y = p[7].y + target_new_position->y;
			q[7].z = p[7].z + target_new_position->z;

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[0], &q[1], &q[2], &q[3], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[3], &q[2], &q[6], &q[7], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[7], &q[6], &q[5], &q[4], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[4], &q[5], &q[1], &q[0], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[1], &q[5], &q[6], &q[2], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[0], &q[4], &q[7], &q[3], source_intercept_point, face_normal))
			{
				return (TRUE);
			}
		}

		//
		// collision test bounding box at mid position
		//

		if (test_flags & TEST_MID_POSITION)
		{
			target_mid_position.x = (target_old_position->x + target_new_position->x) * 0.5;
			target_mid_position.y = (target_old_position->y + target_new_position->y) * 0.5;
			target_mid_position.z = (target_old_position->z + target_new_position->z) * 0.5;

			q[0].x = p[0].x + target_mid_position.x;
			q[0].y = p[0].y + target_mid_position.y;
			q[0].z = p[0].z + target_mid_position.z;

			q[1].x = p[1].x + target_mid_position.x;
			q[1].y = p[1].y + target_mid_position.y;
			q[1].z = p[1].z + target_mid_position.z;

			q[2].x = p[2].x + target_mid_position.x;
			q[2].y = p[2].y + target_mid_position.y;
			q[2].z = p[2].z + target_mid_position.z;

			q[3].x = p[3].x + target_mid_position.x;
			q[3].y = p[3].y + target_mid_position.y;
			q[3].z = p[3].z + target_mid_position.z;

			q[4].x = p[4].x + target_mid_position.x;
			q[4].y = p[4].y + target_mid_position.y;
			q[4].z = p[4].z + target_mid_position.z;

			q[5].x = p[5].x + target_mid_position.x;
			q[5].y = p[5].y + target_mid_position.y;
			q[5].z = p[5].z + target_mid_position.z;

			q[6].x = p[6].x + target_mid_position.x;
			q[6].y = p[6].y + target_mid_position.y;
			q[6].z = p[6].z + target_mid_position.z;

			q[7].x = p[7].x + target_mid_position.x;
			q[7].y = p[7].y + target_mid_position.y;
			q[7].z = p[7].z + target_mid_position.z;

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[0], &q[1], &q[2], &q[3], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[3], &q[2], &q[6], &q[7], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[7], &q[6], &q[5], &q[4], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[4], &q[5], &q[1], &q[0], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[1], &q[5], &q[6], &q[2], source_intercept_point, face_normal))
			{
				return (TRUE);
			}

			if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &q[0], &q[4], &q[7], &q[3], source_intercept_point, face_normal))
			{
				return (TRUE);
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// For weapon collision detection:-
//
// los_source				= launcher (NULL if none)
// los_target				= NULL
// source_old_position	= weapon old position
// source_new_position	= weapon new position
//
// For radar line of sight:-
//
// los_source				= gunship entity
// los_target				= los target
// source_old_position	= radar los start
// source_new_position	= radar los end
//
// If the line of sight is clear then NULL is returned and source_intercept_point and face_normal are invalid.
//
// If the line of sight is not clear then the collision entity is returned and source_intercept_point and face_normal are valid.
//
////////////////////////////////////////

entity *get_line_of_sight_collision_entity
(
	entity *los_source,
	entity *los_target,
	vec3d *source_old_position,
	vec3d *source_new_position,
	vec3d *source_intercept_point,
	vec3d *face_normal
)
{
	int
		x_sector_min,
		z_sector_min,
		x_sector_max,
		z_sector_max,
		x_sector,
		z_sector,
		ignore_all_fixed_entities_in_sector;

	float
		radius,
		sqr_velocity;

	entity
		*sector,
		*target,
		*target_succ,
		*building;

	vec3d
		source_min_position,
		source_max_position,
		*target_position,
		*target_motion_vector,
		target_old_position,
		target_new_position,
		target_min_position,
		target_max_position;

	object_3d_index_numbers
		object_3d_index;

	object_3d_bounds
		*bounding_box;

	ASSERT (source_old_position);

	ASSERT (source_new_position);

	ASSERT (source_intercept_point);

	ASSERT (face_normal);

	if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
	{
		create_debug_3d_line (source_old_position, source_new_position, LOS_COLOUR, collision_box_lifetime);
	}

	////////////////////////////////////////
	//
	// get source min and max positions
	//
	////////////////////////////////////////

	if (source_old_position->x <= source_new_position->x)
	{
		source_min_position.x = source_old_position->x;
		source_max_position.x = source_new_position->x;
	}
	else
	{
		source_min_position.x = source_new_position->x;
		source_max_position.x = source_old_position->x;
	}

	if (source_old_position->y <= source_new_position->y)
	{
		source_min_position.y = source_old_position->y;
		source_max_position.y = source_new_position->y;
	}
	else
	{
		source_min_position.y = source_new_position->y;
		source_max_position.y = source_old_position->y;
	}

	if (source_old_position->z <= source_new_position->z)
	{
		source_min_position.z = source_old_position->z;
		source_max_position.z = source_new_position->z;
	}
	else
	{
		source_min_position.z = source_new_position->z;
		source_max_position.z = source_old_position->z;
	}

	////////////////////////////////////////
	//
	// calc sector scan (widened to include entites which are overlapping sector edges)
	//
	////////////////////////////////////////

	get_x_sector (x_sector_min, max (source_min_position.x - LARGEST_3D_OBJECT_RADIUS, MIN_MAP_X));
	get_z_sector (z_sector_min, max (source_min_position.z - LARGEST_3D_OBJECT_RADIUS, MIN_MAP_Z));
	get_x_sector (x_sector_max, min (source_max_position.x + LARGEST_3D_OBJECT_RADIUS, MAX_MAP_X));
	get_z_sector (z_sector_max, min (source_max_position.z + LARGEST_3D_OBJECT_RADIUS, MAX_MAP_Z));

	////////////////////////////////////////
	//
	// sector scan
	//
	////////////////////////////////////////

	//
	// scan
	//

	for (x_sector = x_sector_min; x_sector <= x_sector_max; x_sector++)
	{
		for (z_sector = z_sector_min; z_sector <= z_sector_max; z_sector++)
		{
			sector = get_local_raw_sector_entity (x_sector, z_sector);

			if (source_min_position.y > get_local_entity_float_value (sector, FLOAT_TYPE_TALLEST_STRUCTURE_HEIGHT))
			{
				ignore_all_fixed_entities_in_sector = TRUE;
			}
			else
			{
				ignore_all_fixed_entities_in_sector = FALSE;
			}

			//
			// search sector list backwards so that static objects are checked before mobile objects
			//
			// (mobile objects tend to be at the start of the list as they are dynamic)
			//

			target = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

			if (target)
			{
				target_succ = get_local_entity_child_succ (target, LIST_TYPE_SECTOR);

				while (target_succ)
				{
					target = target_succ;

					target_succ = get_local_entity_child_succ (target, LIST_TYPE_SECTOR);
				}
			}

			while (target)
			{
				if ((target != los_source) && (target != los_target))
				{
					if (get_local_entity_int_value (target, INT_TYPE_COLLISION_TEST_MOBILE))
					{
						////////////////////////////////////////
						//
						// MOBILE TARGET
						//
						////////////////////////////////////////

						object_3d_index = get_local_entity_int_value (target, INT_TYPE_OBJECT_3D_SHAPE);

						ASSERT (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

						bounding_box = get_object_3d_bounding_box_without_lines (object_3d_index);

						ASSERT (bounding_box);

						target_motion_vector = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_MOTION_VECTOR);

						sqr_velocity =
						(
							target_motion_vector->x * target_motion_vector->x +
							target_motion_vector->y * target_motion_vector->y +
							target_motion_vector->z * target_motion_vector->z
						);

						if (sqr_velocity > 1.0)
						{
							//
							// moving mobile
							//

							if (get_local_entity_int_value (target, INT_TYPE_UPDATED))
							{
								get_local_entity_vec3d (target, VEC3D_TYPE_POSITION, &target_new_position);

								target_old_position.x = target_new_position.x - target_motion_vector->x * get_delta_time ();
								target_old_position.y = target_new_position.y - target_motion_vector->y * get_delta_time ();
								target_old_position.z = target_new_position.z - target_motion_vector->z * get_delta_time ();
							}
							else
							{
								get_local_entity_vec3d (target, VEC3D_TYPE_POSITION, &target_old_position);

								target_new_position.x = target_old_position.x + target_motion_vector->x * get_delta_time ();
								target_new_position.y = target_old_position.y + target_motion_vector->y * get_delta_time ();
								target_new_position.z = target_old_position.z + target_motion_vector->z * get_delta_time ();
							}

							//
							// get target min and max positions (widened to target radius)
							//

							if (target_old_position.x <= target_new_position.x)
							{
								target_min_position.x = target_old_position.x;
								target_max_position.x = target_new_position.x;
							}
							else
							{
								target_min_position.x = target_new_position.x;
								target_max_position.x = target_old_position.x;
							}

							if (target_old_position.y <= target_new_position.y)
							{
								target_min_position.y = target_old_position.y;
								target_max_position.y = target_new_position.y;
							}
							else
							{
								target_min_position.y = target_new_position.y;
								target_max_position.y = target_old_position.y;
							}

							if (target_old_position.z <= target_new_position.z)
							{
								target_min_position.z = target_old_position.z;
								target_max_position.z = target_new_position.z;
							}
							else
							{
								target_min_position.z = target_new_position.z;
								target_max_position.z = target_old_position.z;
							}

							radius = get_object_3d_radius (object_3d_index);

							target_min_position.x -= radius;
							target_min_position.y -= radius;
							target_min_position.z -= radius;

							target_max_position.x += radius;
							target_max_position.y += radius;
							target_max_position.z += radius;

							if
							(
								(!(target_max_position.x < source_min_position.x)) &&
								(!(target_min_position.x > source_max_position.x)) &&
								(!(target_max_position.y < source_min_position.y)) &&
								(!(target_min_position.y > source_max_position.y)) &&
								(!(target_max_position.z < source_min_position.z)) &&
								(!(target_min_position.z > source_max_position.z))
							)
							{
								if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
								{
									draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_HIT_COLOUR);
									draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_HIT_COLOUR);
								}

								if
								(
									accurate_moving_bounding_box_collision_test
									(
										target,
										source_old_position,
										source_new_position,
										&target_old_position,
										&target_new_position,
										object_3d_index,
										bounding_box,
										source_intercept_point,
										face_normal
									)
								)
								{
									return (target);
								}
							}
							else
							{
								#if DEBUG_MODULE_ENABLE_COLLISION_BOX_MISS

								if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
								{
									draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_MISS_COLOUR);
									draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_MISS_COLOUR);
								}

								#endif
							}
						}
						else
						{
							//
							// stationary mobile (usually on ground but could be helicopter on deck of ship etc.)
							//

	 						target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

							if
							(
								(source_min_position.y <= (target_position->y + bounding_box->ymax)) &&
								(source_max_position.y >= (target_position->y + bounding_box->ymin))
							)
							{
								radius = get_object_3d_radius (object_3d_index);

								target_min_position.x = target_position->x - radius;
								target_min_position.y = target_position->y - radius;
								target_min_position.z = target_position->z - radius;

								target_max_position.x = target_position->x + radius;
								target_max_position.y = target_position->y + radius;
								target_max_position.z = target_position->z + radius;

								if
								(
									(!(target_max_position.x < source_min_position.x)) &&
									(!(target_min_position.x > source_max_position.x)) &&
									(!(target_max_position.y < source_min_position.y)) &&
									(!(target_min_position.y > source_max_position.y)) &&
									(!(target_max_position.z < source_min_position.z)) &&
									(!(target_min_position.z > source_max_position.z))
								)
								{
									if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
									{
										draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_HIT_COLOUR);
										draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_HIT_COLOUR);
									}

									if
									(
										accurate_stationary_bounding_box_collision_test
										(
											target,
											source_old_position,
											source_new_position,
											object_3d_index,
											bounding_box,
											source_intercept_point,
											face_normal
										)
									)
									{
										return (target);
									}
								}
								else
								{
									#if DEBUG_MODULE_ENABLE_COLLISION_BOX_MISS

									if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
									{
										draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_MISS_COLOUR);
										draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_MISS_COLOUR);
									}

									#endif
								}
							}
						}
					}
					else if (!ignore_all_fixed_entities_in_sector)
					{
						if (get_local_entity_int_value (target, INT_TYPE_COLLISION_TEST_FIXED))
						{
							////////////////////////////////////////
							//
							// FIXED TARGET
							//
							////////////////////////////////////////

							if (get_local_entity_type (target) == ENTITY_TYPE_CITY)
							{
								building = get_local_entity_first_child (target, LIST_TYPE_CITY_BUILDING);

								if (building)
								{
									target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

									get_local_entity_vec3d (target, VEC3D_TYPE_BOUNDING_BOX_MIN, &target_min_position);
									get_local_entity_vec3d (target, VEC3D_TYPE_BOUNDING_BOX_MAX, &target_max_position);

									target_min_position.y += target_position->y;
									target_max_position.y += target_position->y;

									if
									(
										(!(target_max_position.y < source_min_position.y)) &&
										(!(target_min_position.y > source_max_position.y))
									)
									{
										target_min_position.x += target_position->x;
										target_min_position.z += target_position->z;

										target_max_position.x += target_position->x;
										target_max_position.z += target_position->z;

										if
										(
											(!(target_max_position.x < source_min_position.x)) &&
											(!(target_min_position.x > source_max_position.x)) &&
											(!(target_max_position.z < source_min_position.z)) &&
											(!(target_min_position.z > source_max_position.z))
										)
										{
											if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
											{
												draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_HIT_COLOUR);
												draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_HIT_COLOUR);
											}

											while (building)
											{
												object_3d_index = get_local_entity_int_value (building, INT_TYPE_OBJECT_3D_SHAPE);

												ASSERT (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

												bounding_box = get_object_3d_bounding_box_without_lines (object_3d_index);

												ASSERT (bounding_box);

 												target_position = get_local_entity_vec3d_ptr (building, VEC3D_TYPE_POSITION);

												if
												(
													(source_min_position.y <= (target_position->y + bounding_box->ymax)) &&
													(source_max_position.y >= (target_position->y + bounding_box->ymin))
												)
												{
													radius = get_object_3d_radius (object_3d_index);

													target_min_position.x = target_position->x - radius;
													target_min_position.y = target_position->y - radius;
													target_min_position.z = target_position->z - radius;

													target_max_position.x = target_position->x + radius;
													target_max_position.y = target_position->y + radius;
													target_max_position.z = target_position->z + radius;

													if
													(
														(!(target_max_position.x < source_min_position.x)) &&
														(!(target_min_position.x > source_max_position.x)) &&
														(!(target_max_position.y < source_min_position.y)) &&
														(!(target_min_position.y > source_max_position.y)) &&
														(!(target_max_position.z < source_min_position.z)) &&
														(!(target_min_position.z > source_max_position.z))
													)
													{
														if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
														{
															draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_HIT_COLOUR);
															draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_HIT_COLOUR);
														}

														if
														(
															accurate_stationary_bounding_box_collision_test
															(
																building,
																source_old_position,
																source_new_position,
																object_3d_index,
																bounding_box,
																source_intercept_point,
																face_normal
															)
														)
														{
															return (building);
														}
													}
													else
													{
														#if DEBUG_MODULE_ENABLE_COLLISION_BOX_MISS

														if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
														{
															draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_MISS_COLOUR);
															draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_MISS_COLOUR);
														}

														#endif
													}
												}

												building = get_local_entity_child_succ (building, LIST_TYPE_CITY_BUILDING);
											}
										}
										else
										{
											#if DEBUG_MODULE_ENABLE_COLLISION_BOX_MISS

											if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
											{
												draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_MISS_COLOUR);
												draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_MISS_COLOUR);
											}

											#endif
										}
									}
								}
							}
							else if (get_local_entity_type (target) != ENTITY_TYPE_CITY_BUILDING)
							{
								object_3d_index = get_local_entity_int_value (target, INT_TYPE_OBJECT_3D_SHAPE);

								ASSERT (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

								bounding_box = get_object_3d_bounding_box_without_lines (object_3d_index);

								ASSERT (bounding_box);

 								target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

								if
								(
									(source_min_position.y <= (target_position->y + bounding_box->ymax)) &&
									(source_max_position.y >= (target_position->y + bounding_box->ymin))
								)
								{
									radius = get_object_3d_radius (object_3d_index);

									target_min_position.x = target_position->x - radius;
									target_min_position.y = target_position->y - radius;
									target_min_position.z = target_position->z - radius;

									target_max_position.x = target_position->x + radius;
									target_max_position.y = target_position->y + radius;
									target_max_position.z = target_position->z + radius;

									if
									(
										(!(target_max_position.x < source_min_position.x)) &&
										(!(target_min_position.x > source_max_position.x)) &&
										(!(target_max_position.y < source_min_position.y)) &&
										(!(target_min_position.y > source_max_position.y)) &&
										(!(target_max_position.z < source_min_position.z)) &&
										(!(target_min_position.z > source_max_position.z))
									)
									{
										if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
										{
											draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_HIT_COLOUR);
											draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_HIT_COLOUR);
										}

										if
										(
											accurate_stationary_bounding_box_collision_test
											(
												target,
												source_old_position,
												source_new_position,
												object_3d_index,
												bounding_box,
												source_intercept_point,
												face_normal
											)
										)
										{
											return (target);
										}
									}
									else
									{
										if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
										{
											#if DEBUG_MODULE_ENABLE_COLLISION_BOX_MISS

											draw_min_max_box (&source_min_position, &source_max_position, COLLISION_BOX_MISS_COLOUR);
											draw_min_max_box (&target_min_position, &target_max_position, COLLISION_BOX_MISS_COLOUR);

											#endif
										}
									}
								}
							}
						}
					}
				}

				//
				// search list backwards
				//

				target = get_local_entity_child_pred (target, LIST_TYPE_SECTOR);
			}
		}
	}

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TREE COLLISION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// BE AWARE THAT THIS TREE COLLISION DETECTION CAN SEE THROUGH RAISED FOREST CANOPY
//
////////////////////////////////////////

#define TREE_RADIUS	(5.0)

int get_line_of_sight_collision_tree
(
	vec3d *source_old_position,
	vec3d *source_new_position,
	vec3d *source_intercept_point,
	vec3d *face_normal,
	int ignore_forest_edge_trees,
	int skip_tree_top_test
)
{
	int
		x_sector_min,
		z_sector_min,
		x_sector_max,
		z_sector_max,
		x_sector,
		z_sector,
		hit_tree,
		num_trees;

	float
		source_old_position_rad_alt,
		source_new_position_rad_alt,
		source_range,
		source_dy,
		source_ratio,
		height,
		tree_top,
		tree_range,
		nearest_tree_range,
		tree_intercept_y,
		x_sector_mid_point,
		z_sector_mid_point,
		dx,
		dz,
		dx1,
		dz1,
		dx2,
		dz2,
		ddx,
		ddz;

	vec3d
		nearest_tree_intercept_point,
		nearest_tree_face_normal,
		source_min_position,
		source_max_position,
		tree_position,
		p1,
		p2,
		p3,
		p4;

	terrain_3d_tree_data
		*tree;

	ASSERT (source_old_position);

	ASSERT (source_new_position);

	ASSERT (source_intercept_point);

	ASSERT (face_normal);

	if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
	{
		create_debug_3d_line (source_old_position, source_new_position, LOS_COLOUR, collision_box_lifetime);
	}

	////////////////////////////////////////
	//
	// check if source is above highest tree
	//
	////////////////////////////////////////

	if (point_inside_map_area (source_old_position))
	{
		source_old_position_rad_alt = source_old_position->y - get_3d_terrain_elevation (source_old_position->x, source_old_position->z);
	}
	else
	{
		source_old_position_rad_alt = 0.0;
	}

	if (point_inside_map_area (source_new_position))
	{
		source_new_position_rad_alt = source_new_position->y - get_3d_terrain_elevation (source_new_position->x, source_new_position->z);
	}
	else
	{
		source_new_position_rad_alt = source_old_position_rad_alt;
	}

	if (min (source_old_position_rad_alt, source_new_position_rad_alt) > TERRAIN_3D_MAX_TREE_HEIGHT)
	{
		return (FALSE);
	}

	////////////////////////////////////////
	//
	// source values
	//
	////////////////////////////////////////

	source_range = get_2d_range (source_old_position, source_new_position);

	if (source_range < 0.1f)
	{
		return (FALSE);
	}

	source_dy = source_new_position->y - source_old_position->y;

	source_ratio = source_dy / source_range;

	////////////////////////////////////////
	//
	// get source min and max positions
	//
	////////////////////////////////////////

	if (source_old_position->x <= source_new_position->x)
	{
		source_min_position.x = source_old_position->x;
		source_max_position.x = source_new_position->x;
	}
	else
	{
		source_min_position.x = source_new_position->x;
		source_max_position.x = source_old_position->x;
	}

	if (source_old_position->y <= source_new_position->y)
	{
		source_min_position.y = source_old_position->y;
		source_max_position.y = source_new_position->y;
	}
	else
	{
		source_min_position.y = source_new_position->y;
		source_max_position.y = source_old_position->y;
	}

	if (source_old_position->z <= source_new_position->z)
	{
		source_min_position.z = source_old_position->z;
		source_max_position.z = source_new_position->z;
	}
	else
	{
		source_min_position.z = source_new_position->z;
		source_max_position.z = source_old_position->z;
	}

	////////////////////////////////////////
	//
	// calc sector scan
	//
	////////////////////////////////////////

	bound_position_to_map_area (&source_min_position);

	bound_position_to_map_area (&source_max_position);

	get_terrain_3d_sector (source_min_position.x, source_min_position.z, &x_sector_min, &z_sector_min);

	get_terrain_3d_sector (source_max_position.x, source_max_position.z, &x_sector_max, &z_sector_max);

	if (draw_collision_boxes && (get_view_mode () == VIEW_MODE_EXTERNAL))
	{
		draw_min_max_box (&source_min_position, &source_max_position, sys_col_cyan);
	}

	////////////////////////////////////////
	//
	// sector scan
	//
	////////////////////////////////////////

	hit_tree = FALSE;

	nearest_tree_range = FLT_MAX;

	for (x_sector = x_sector_min; x_sector <= x_sector_max; x_sector++)
	{
		for (z_sector = z_sector_min; z_sector <= z_sector_max; z_sector++)
		{
			num_trees = get_terrain_3d_tree_sector_data (x_sector, z_sector, &tree);

			if (num_trees > 0)
			{
				x_sector_mid_point = (x_sector * TERRAIN_3D_SECTOR_SIDE_LENGTH) + (TERRAIN_3D_SECTOR_SIDE_LENGTH * 0.5);
				z_sector_mid_point = (z_sector * TERRAIN_3D_SECTOR_SIDE_LENGTH) + (TERRAIN_3D_SECTOR_SIDE_LENGTH * 0.5);

				tree--;

				while (num_trees--)
				{
					tree++;

					if (!(ignore_forest_edge_trees && (tree->type == 0)))
					{
						tree_position.y = (tree->y * terrain_3d_map_scaled_height_difference * 0.5) + terrain_3d_map_minimum_height;

						if (source_max_position.y >= tree_position.y)
						{
							//
							// scale down height to make the tree top soft
							//

							height = get_terrain_3d_tree_scale (tree) * 0.75;

							tree_top = tree_position.y + height;

							if (source_min_position.y <= tree_top)
							{
								tree_position.x = x_sector_mid_point + (tree->x * TERRAIN_3D_XZ_SCALE * 0.5);

								if ((tree_position.x >= source_min_position.x) && (tree_position.x <= source_max_position.x))
								{
									tree_position.z = z_sector_mid_point + (tree->z * TERRAIN_3D_XZ_SCALE * 0.5);

									if ((tree_position.z >= source_min_position.z) && (tree_position.z <= source_max_position.z))
									{
										//
										// use similar triangles (xz plane) to determine 2D distance from the line
										//

										dx = source_new_position->x - source_old_position->x;
										dz = source_new_position->z - source_old_position->z;

										dx1 = tree_position.x - source_old_position->x;
										dz1 = dx1 * dz / dx;

										dz2 = tree_position.z - source_old_position->z;
										dx2 = dz2 * dx / dz;

										ddx = dx1 - dx2;
										ddz = dz1 - dz2;

										if (((ddx > -TREE_RADIUS) && (ddx < TREE_RADIUS)) || ((ddz > -TREE_RADIUS) && (ddz < TREE_RADIUS)))
										{
											//
											// use similar triangles to determine if line intercepts tree
											//

											tree_range = get_2d_range (source_old_position, &tree_position);

											tree_intercept_y = (tree_range * source_ratio) + source_old_position->y;

											if ((tree_position.y <= tree_intercept_y) && (tree_top >= tree_intercept_y))
											{
												p1.x = tree_position.x - (TREE_RADIUS * 0.5);
												p1.y = tree_position.y;
												p1.z = tree_position.z;

												p4.x = tree_position.x + (TREE_RADIUS * 0.5);
												p4.y = tree_position.y;
												p4.z = tree_position.z;

												p2.x = p1.x;
												p2.y = tree_top;
												p2.z = p1.z;

												p3.x = p4.x;
												p3.y = tree_top;
												p3.z = p4.z;

												if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p1, &p2, &p3, &p4, source_intercept_point, face_normal))
												{
													if (tree_range < nearest_tree_range)
													{
														hit_tree = TRUE;

														nearest_tree_range = tree_range;

														nearest_tree_intercept_point = *source_intercept_point;

														nearest_tree_face_normal = *face_normal;

														continue;
													}
												}

												p1.x = tree_position.x;
												p1.y = tree_position.y;
												p1.z = tree_position.z - (TREE_RADIUS * 0.5);

												p4.x = tree_position.x;
												p4.y = tree_position.y;
												p4.z = tree_position.z + (TREE_RADIUS * 0.5);

												p2.x = p1.x;
												p2.y = tree_top;
												p2.z = p1.z;

												p3.x = p4.x;
												p3.y = tree_top;
												p3.z = p4.z;

												if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p1, &p2, &p3, &p4, source_intercept_point, face_normal))
												{
													if (tree_range < nearest_tree_range)
													{
														hit_tree = TRUE;

														nearest_tree_range = tree_range;

														nearest_tree_intercept_point = *source_intercept_point;

														nearest_tree_face_normal = *face_normal;

														continue;
													}
												}

												if (!skip_tree_top_test)
												{
													p1.x = tree_position.x - (TREE_RADIUS * 0.5);
													p1.y = tree_top;
													p1.z = tree_position.z - (TREE_RADIUS * 0.5);

													p2.x = tree_position.x - (TREE_RADIUS * 0.5);
													p2.y = tree_top;
													p2.z = tree_position.z + (TREE_RADIUS * 0.5);

													p3.x = tree_position.x + (TREE_RADIUS * 0.5);
													p3.y = tree_top;
													p3.z = tree_position.z + (TREE_RADIUS * 0.5);

													p4.x = tree_position.x + (TREE_RADIUS * 0.5);
													p4.y = tree_top;
													p4.z = tree_position.z - (TREE_RADIUS * 0.5);

													if (get_3d_line_quad_face_intersection (source_old_position, source_new_position, &p1, &p2, &p3, &p4, source_intercept_point, face_normal))
													{
														if (tree_range < nearest_tree_range)
														{
															hit_tree = TRUE;

															nearest_tree_range = tree_range;

															nearest_tree_intercept_point = *source_intercept_point;

															nearest_tree_face_normal = *face_normal;

															continue;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (hit_tree)
	{
		*source_intercept_point = nearest_tree_intercept_point;

		*face_normal = nearest_tree_face_normal;
	}

	return (hit_tree);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
