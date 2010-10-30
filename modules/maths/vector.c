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

#include "maths.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT	0


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float normalise_4d_vector ( vec4d *vector )
{

	float
		x,
		y,
		z,
		length,
		one_over_length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );
	z = ( ( vector->z ) * ( vector->z ) );

	length = sqrt ( x + y + z );

	ASSERT ( length > 0.0 );

	one_over_length = 1.0 / length;

	vector->x = ( vector->x * one_over_length );
	vector->y = ( vector->y * one_over_length );
	vector->z = ( vector->z * one_over_length );
	vector->a = length;

	return ( length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float accurately_normalise_3d_vector ( vec3d *vector )
{

	double
		x,
		y,
		z,
		length;

	x = ( double ) vector->x;
	y = ( double ) vector->y;
	z = ( double ) vector->z;

	length = sqrt ( ( x * x ) + ( y * y ) + ( z * z ) );

	vector->x = ( float ) ( x / length );
	vector->y = ( float ) ( y / length );
	vector->z = ( float ) ( z / length );

	return ( length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float normalise_3d_vector ( vec3d *vector )
{

	float
		x,
		y,
		z,
		length,
		one_over_length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );
	z = ( ( vector->z ) * ( vector->z ) );

	length = sqrt ( x + y + z );

	ASSERT ( length > 0.0 );

	one_over_length = 1.0 / length;

	vector->x = ( vector->x * one_over_length );
	vector->y = ( vector->y * one_over_length );
	vector->z = ( vector->z * one_over_length );

	return ( length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float normalise_2d_vector ( vec2d *vector )
{

	float
		x,
		y,
		length,
		one_over_length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );

	length = sqrt ( x + y );

	ASSERT ( length > 0.0 );

	one_over_length = 1.0 / length;

	vector->x = ( vector->x * one_over_length );
	vector->y = ( vector->y * one_over_length );

	return ( length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float normalise_any_3d_vector ( vec3d *vector )
{

	float
		x,
		y,
		z,
		length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );
	z = ( ( vector->z ) * ( vector->z ) );

	length = sqrt ( x + y + z );

	if ( length > 0 )
	{

		float
			one_over_length;

		one_over_length = 1.0 / length;

		vector->x = ( vector->x * one_over_length );
		vector->y = ( vector->y * one_over_length );
		vector->z = ( vector->z * one_over_length );
	}
	else
	{

		vector->x = 0;
		vector->y = 0;
		vector->z = 0;
	}

	return ( length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float normalise_any_2d_vector ( vec2d *vector )
{

	float
		x,
		y,
		length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );

	length = sqrt ( x + y );

	if ( length > 0 )
	{

		float
			one_over_length;

		one_over_length = 1.0 / length;

		vector->x = ( vector->x * one_over_length );
		vector->y = ( vector->y * one_over_length );
	}
	else
	{

		vector->x = 0;
		vector->y = 0;
	}

	return ( length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_3d_vector_magnitude ( const vec3d *vector )
{

	float
		x,
		y,
		z;

	ASSERT ( vector );

	x = ( vector->x * vector->x );
	y = ( vector->y * vector->y );
	z = ( vector->z * vector->z );

	return ( sqrt ( x + y + z ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_2d_vector_magnitude ( const vec2d *vector )
{

	float
		x,
		y;

	ASSERT ( vector );

	x = ( vector->x * vector->x );
	y = ( vector->y * vector->y );

	return ( sqrt ( x + y ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_3d_vector_inverse_magnitude ( const vec3d *vector )
{

	float
		x,
		y,
		z;

	ASSERT ( vector );

	x = ( vector->x * vector->x );
	y = ( vector->y * vector->y );
	z = ( vector->z * vector->z );

	return ( get_inverse_square_root ( x + y + z ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void normalise_3d_vector_given_magnitude ( vec3d *vector, float length )
{

	float
		one_over_length;

	ASSERT ( vector );

	ASSERT ( length > 0.0 );

	one_over_length = 1.0 / length;

	vector->x = ( vector->x * one_over_length );
	vector->y = ( vector->y * one_over_length );
	vector->z = ( vector->z * one_over_length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void normalise_2d_vector_given_magnitude ( vec2d *vector, float length )
{

	float
		one_over_length;

	ASSERT ( vector );

	ASSERT ( length > 0.0 );

	one_over_length = 1.0 / length;

	vector->x = ( vector->x * one_over_length );
	vector->y = ( vector->y * one_over_length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// calc perpendicular distance of point c from point d along line ab
//
// (point_d may be passed as NULL if the point is not required)

float get_3d_perp_dist_of_point_from_line (const vec3d *point_a, const vec3d *point_b, const vec3d *point_c, vec3d *point_d)
{
	float
		mag_ab,
		mag_ac,
		mag_ad,
		theta,
		cos_theta,
		dist;

	vec3d
		uv_ab,
		uv_ac;

	ASSERT (point_a);

	ASSERT (point_b);

	ASSERT (point_c);

	//
	// calc vector from point a to point b
	//

	uv_ab.x = point_b->x - point_a->x;
	uv_ab.y = point_b->y - point_a->y;
	uv_ab.z = point_b->z - point_a->z;

	mag_ab = sqrt ((uv_ab.x * uv_ab.x) + (uv_ab.y * uv_ab.y) + (uv_ab.z * uv_ab.z));

	if (mag_ab == 0.0)
	{
		if (point_d)
		{
			*point_d = *point_a;
		}

		return (FLT_MAX);
	}

	normalise_3d_vector_given_magnitude (&uv_ab, mag_ab);

	//
	// calc vector from point a to point c
	//

	uv_ac.x = point_c->x - point_a->x;
	uv_ac.y = point_c->y - point_a->y;
	uv_ac.z = point_c->z - point_a->z;

	mag_ac = sqrt ((uv_ac.x * uv_ac.x) + (uv_ac.y * uv_ac.y) + (uv_ac.z * uv_ac.z));

	if (mag_ac == 0.0)
	{
		if (point_d)
		{
			*point_d = *point_a;
		}

		return (FLT_MAX);
	}

	normalise_3d_vector_given_magnitude (&uv_ac, mag_ac);

	//
	// calc angle between vectors (dot product)
	//

	cos_theta = (uv_ab.x * uv_ac.x) + (uv_ab.y * uv_ac.y) + (uv_ab.z * uv_ac.z);

	//
	// check point is perpendicular to line
	//

	if (cos_theta < 0.0)
	{
		if (point_d)
		{
			*point_d = *point_a;
		}

		return (FLT_MAX);
	}

	mag_ad = mag_ac * cos_theta;

	if (mag_ad > mag_ab)
	{
		if (point_d)
		{
			*point_d = *point_b;
		}

		return (FLT_MAX);
	}

	//
	// calc point d
	//

	if (point_d)
	{
		point_d->x = point_a->x + (uv_ab.x * mag_ad);
		point_d->y = point_a->y + (uv_ab.y * mag_ad);
		point_d->z = point_a->z + (uv_ab.z * mag_ad);
	}

	//
	// calc perpendicular distance of point from line
	//

	theta = acos (cos_theta);

	dist = mag_ac * sin (theta);

	return (dist);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calculates the perpendicular vector of point c from the line a -> b

void get_3d_perp_vector_of_point_from_line (const vec3d *line_point_a, const vec3d *line_point_b, const vec3d *point_c, vec3d *result)
{
	vec3d
		A,
		B,
		P;


	float
		mag_ab,
		mag_ac,
		mag_ap,
		cos_theta;

	//
	// need to find a point P on line a->b such that result = P->c
	//

	ASSERT (line_point_a);

	ASSERT (line_point_b);

	ASSERT (point_c);

	ASSERT (result);

	//
	// calc vector from point a to point b
	//

	A.x = line_point_b->x - line_point_a->x;
	A.y = line_point_b->y - line_point_a->y;
	A.z = line_point_b->z - line_point_a->z;

	//
	// calc vector from point a to point c
	//

	B.x = point_c->x - line_point_a->x;
	B.y = point_c->y - line_point_a->y;
	B.z = point_c->z - line_point_a->z;

	//
	// check against two of the points being identical
	//

	mag_ab = get_3d_vector_magnitude (&A);

	mag_ac = get_3d_vector_magnitude (&B);

	if ( mag_ac == 0 )
	{
		// point a == point c :-> point is on the line so dist = 0
		result->x = 0;
		result->y = 0;
		result->z = 0;
		return;
	}
	if ( mag_ab == 0 )
	{
		// point a == point b :-> return vector a -> c
		result->x = B.x;
		result->y = B.y;
		result->z = B.z;
		return;
	}

	normalise_3d_vector_given_magnitude (&A, mag_ab);

	normalise_3d_vector_given_magnitude (&B, mag_ac);

	//
	// calc angle between vectors (dot product), where fabs() guarantees 0 <= angle <= 90
	//

	cos_theta = fabs( (A.x * B.x) + (A.y * B.y) + (A.z * B.z) );

	//
	// find distance of point P along line a->b ( where P->c is our required vector )
	//

	mag_ap = mag_ac * cos_theta;

	P.x = line_point_a->x + ( mag_ap * A.x );
	P.y = line_point_a->y + ( mag_ap * A.y );
	P.z = line_point_a->z + ( mag_ap * A.z );

	//
	// return the vector from P to point c
	//

	result->x = point_c->x - P.x;
	result->y = point_c->y - P.y;
	result->z = point_c->z - P.z;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_2d_perp_dist_of_point_from_line (const vec3d *line_point_a, const vec3d *line_point_b, const vec3d *point_c, float *distance_along_line)
{

	float
		d,
		mag_ab,
		mag_ac,
		mag_ad,
		cos_theta;

	vec3d
		ab, ac;

	if ( distance_along_line )
	{
		*distance_along_line = 0.0;
	}

	//
	// check point is within bounds of the line
	//

	ab.x = line_point_b->x - line_point_a->x;
	ab.y = 0.0;
	ab.z = line_point_b->z - line_point_a->z;

	ac.x = point_c->x - line_point_a->x;
	ac.y = 0.0;
	ac.z = point_c->z - line_point_a->z;

	mag_ab = normalise_3d_vector( &ab );			// line AB must be a line and not a single point
	mag_ac = normalise_any_3d_vector( &ac );		// but C can be same point as A

	//
	// calc angle between vectors (dot product)
	//

	cos_theta = (ab.x * ac.x) + (ab.y * ac.y) + (ab.z * ac.z);

	//
	// check point is perpendicular to line
	//

	if (cos_theta < 0.0)
	{
		return (FLT_MAX);
	}

	mag_ad = mag_ac * cos_theta;

	if (mag_ad > mag_ab)
	{
		return (FLT_MAX);
	}

	//
	// find distance
	//

	d = get_2d_perp_dist_of_point_from_infinite_line (line_point_a, line_point_b, point_c);

	if ( distance_along_line )
	{
		*distance_along_line = mag_ad;
	}

	return d;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_2d_perp_dist_of_point_from_infinite_line (const vec3d *line_point_a, const vec3d *line_point_b, const vec3d *point_c)
{
	vec3d
		normal;

	float
		d,
		dx,
		dz;

	//
	// find distance
	//

	dx = line_point_b->x - line_point_a->x;
	dz = line_point_b->z - line_point_a->z;

	normal.x = dz;
	normal.y = 0;
	normal.z = -dx;

	normalise_3d_vector( &normal );

	d = ( ( point_c->x * normal.x ) + ( point_c->z * normal.z ) )
						- ( ( line_point_a->x * normal.x ) + ( line_point_a->z * normal.z ) );

	return fabs( d );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate the intercept of two lines, p1->p2 and q1->q2.
// if the lines are parellel 0,0,0 and 0,0,0 is returned
// if the lines diverge the nearest point on the lines are returned,
// ie the end points.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0

////////////////////////////////////////
//
// WARNING - This implementation of the function is no longer compliant with the calling convention.
//
////////////////////////////////////////

void line_line_3d_intercept (vec3d p1, vec3d p2, vec3d q1, vec3d q2, vec3d *intercept_point_p, vec3d *intercept_point_q)
{
// - Daves girlie function
	float
		t_xy,
		t_xz,
		t_zy,
		s_xy,
		s_xz,
		s_zy;

	vec3d
		u,
		v;

	// calculate directional vectors

	u.x = p2.x - p1.x;
	u.y = p2.y - p1.y;
	u.z = p2.z - p1.z;

	v.x = q2.x - q1.x;
	v.y = q2.y - q1.y;
	v.z = q2.z - q1.z;

	if ((p1.y - q1.y == 0) || (p1.x - q1.x == 0))
	{

		if ((p1.z - q1.z == 0) || (p1.y - q1.y == 0))
		{

			t_zy = (((p1.z - q1.z) * v.y) - ((p1.y - q1.y) * v.z)) /
					((u.y * v.z) - (u.z * v.y));

			if ((t_zy < 0.0) || (t_zy > 1.0))
			{

				t_zy = bound (t_zy, 0.0, 1.0);

				s_zy = (p1.y - q1.y < p2.y - q2.y) ? 0.0 : 1.0;

				intercept_point_p->x = p1.x + u.x * t_zy;
				intercept_point_p->y = p1.y + u.y * t_zy;
				intercept_point_p->z = p1.z + u.z * t_zy;

				intercept_point_q->x = q1.x + v.x * s_zy;
				intercept_point_q->y = q1.y + v.y * s_zy;
				intercept_point_q->z = q1.z + v.z * s_zy;

				return;
			}

			intercept_point_p->x = intercept_point_q->x = p1.x + u.x * t_xz;
			intercept_point_p->y = intercept_point_q->y = p1.y + u.y * t_xz;
			intercept_point_p->z = intercept_point_q->z = p1.z + u.z * t_xz;
		}
		else
		{

			t_xz = (((p1.z - q1.z) * v.x) - ((p1.x - q1.x) * v.z)) /
					((u.x * v.z) - (u.z * v.x));

			if ((t_xz < 0.0) || (t_xz > 1.0))
			{

				t_xz = bound (t_xz, 0.0, 1.0);

				s_xz = (p1.z - q1.z < p2.z - q2.z) ? 0.0 : 1.0;

				intercept_point_p->x = p1.x + u.x * t_xz;
				intercept_point_p->y = p1.y + u.y * t_xz;
				intercept_point_p->z = p1.z + u.z * t_xz;

				intercept_point_q->x = q1.x + v.x * s_xz;
				intercept_point_q->y = q1.y + v.y * s_xz;
				intercept_point_q->z = q1.z + v.z * s_xz;

				return;
			}

			intercept_point_p->x = intercept_point_q->x = p1.x + u.x * t_xz;
			intercept_point_p->y = intercept_point_q->y = p1.y + u.y * t_xz;
			intercept_point_p->z = intercept_point_q->z = p1.z + u.z * t_xz;
		}
	}
	else
	{

		t_xy = (((p1.y - q1.y) * v.x) - ((p1.x - q1.x) * v.y)) /
				((u.x * v.y) - (u.y * v.x));

		if ((t_xy < 0.0) || (t_xy > 1.0))
		{

			t_xy = bound (t_xy, 0.0, 1.0);

			s_xy = (p1.x - q1.x < p2.x - q2.x) ? 0.0 : 1.0;

			intercept_point_p->x = p1.x + u.x * t_xy;
			intercept_point_p->y = p1.y + u.y * t_xy;
			intercept_point_p->z = p1.z + u.z * t_xy;

			intercept_point_q->x = q1.x + v.x * s_xy;
			intercept_point_q->y = q1.y + v.y * s_xy;
			intercept_point_q->z = q1.z + v.z * s_xy;

			return;
		}

		intercept_point_p->x = intercept_point_q->x = p1.x + u.x * t_xy;
		intercept_point_p->y = intercept_point_q->y = p1.y + u.y * t_xy;
		intercept_point_p->z = intercept_point_q->z = p1.z + u.z * t_xy;
	}
}

#else

line_line_intercept_result_types line_line_3d_intercept (const vec3d *p1, const vec3d *p2, const vec3d *q1, const vec3d *q2, vec3d *intercept_point_p, vec3d *intercept_point_q)
{

	float
		u_x_v_mag_squared,
		s,
		t,
		det_s,
		det_t;

	float
		cofactors [3],
		matrix [3][3];

	vec3d
		u,
		v;

	ASSERT (p1);

	ASSERT (p2);

	ASSERT (q1);

	ASSERT (q2);

	ASSERT (intercept_point_p);

	ASSERT (intercept_point_q);

	// calculate directional vectors

	u.x = p2->x - p1->x;
	u.y = p2->y - p1->y;
	u.z = p2->z - p1->z;

	v.x = q2->x - q1->x;
	v.y = q2->y - q1->y;
	v.z = q2->z - q1->z;

	// to calculate s

	matrix [0][0] = q1->x - p1->x;
	matrix [0][1] = q1->y - p1->y;
	matrix [0][2] = q1->z - p1->z;

	matrix [1][0] = v.x;
	matrix [1][1] = v.y;
	matrix [1][2] = v.z;

	matrix [2][0] = u.y * v.z - u.z * v.y;
	matrix [2][1] = u.z * v.x - u.x * v.z;
	matrix [2][2] = u.x * v.y - u.y * v.x;

	u_x_v_mag_squared = (matrix [2][0] * matrix [2][0]) + (matrix [2][1] * matrix [2][1]) + (matrix [2][2] * matrix [2][2]);

	// check for parallelism

	if (u_x_v_mag_squared == 0)
	{

		float
			range,
			range2;

		// 1st check p1->q1

		range = get_sqr_3d_range (p1, q1);

		*intercept_point_p = *p1;
		*intercept_point_q = *q1;

		// 2nd check p1->q2

		range2 = get_sqr_3d_range (p1, q2);

		if (range2 < range)
		{

			range = range2;

			*intercept_point_p = *p1;
			*intercept_point_q = *q2;
		}

		// 3rd check p2->q1

		range2 = get_sqr_3d_range (p2, q1);

		if (range2 < range)
		{

			range = range2;

			*intercept_point_p = *p2;
			*intercept_point_q = *q1;
		}

		// 4th check p2->q2

		range2 = get_sqr_3d_range (p2, q2);

		if (range2 < range)
		{

			range = range2;

			*intercept_point_p = *p2;
			*intercept_point_q = *q2;
		}

		return LINE_LINE_INTERCEPT_PARALLEL;
	}

	// form cofactors, only some needed

	cofactors [0] = ((matrix [1][1] * matrix [2][2]) - (matrix [1][2] * matrix [2][1]));
	cofactors [1] = ((matrix [0][1] * matrix [2][2]) - (matrix [0][2] * matrix [2][1]));
	cofactors [2] = ((matrix [0][1] * matrix [1][2]) - (matrix [0][2] * matrix [1][1]));

	// determinant

	det_s = (matrix [0][0] * cofactors [0]) - (matrix [1][0] * cofactors [1]) + (matrix [2][0] * cofactors [2]);

	// parametric value

	s = det_s / u_x_v_mag_squared;

	// check for divergence

	if ((s < 0.0) || (s > 1.0))
	{

		s = bound (s, 0.0, 1.0);

		// to calculate t

		matrix [1][0] = u.x;
		matrix [1][1] = u.y;
		matrix [1][2] = u.z;

		// form cofactors, only some needed

		cofactors [0] = ((matrix [1][1] * matrix [2][2]) - (matrix [1][2] * matrix [2][1]));
		cofactors [1] = ((matrix [0][1] * matrix [2][2]) - (matrix [0][2] * matrix [2][1])); // ??
		cofactors [2] = ((matrix [0][1] * matrix [1][2]) - (matrix [0][2] * matrix [1][1]));

		// determinant

		det_t = (matrix [0][0] * cofactors [0]) - (matrix [1][0] * cofactors [1]) + (matrix [2][0] * cofactors [2]);

  		// parametric point

		t = det_t / u_x_v_mag_squared;

		t = bound (t, 0.0, 1.0);

	  	// two nearest points

		intercept_point_q->x = q1->x + v.x * t;
		intercept_point_q->y = q1->y + v.y * t;
		intercept_point_q->z = q1->z + v.z * t;

		intercept_point_p->x = p1->x + u.x * s;
		intercept_point_p->y = p1->y + u.y * s;
		intercept_point_p->z = p1->z + u.z * s;

		return LINE_LINE_INTERCEPT_DIVERGE;
	}
	else
	{

		// to calculate t

		matrix [1][0] = u.x;
		matrix [1][1] = u.y;
		matrix [1][2] = u.z;

		// form cofactors, only some needed

		cofactors [0] = ((matrix [1][1] * matrix [2][2]) - (matrix [1][2] * matrix [2][1]));
		cofactors [2] = ((matrix [0][1] * matrix [1][2]) - (matrix [0][2] * matrix [1][1]));

		// determinant

		det_t = (matrix [0][0] * cofactors [0]) - (matrix [1][0] * cofactors [1]) + (matrix [2][0] * cofactors [2]);

  		// parametric point

		t = det_t / u_x_v_mag_squared;

		t = bound (t, 0.0, 1.0);

	  	// two nearest points

		intercept_point_q->x = q1->x + v.x * t;
		intercept_point_q->y = q1->y + v.y * t;
		intercept_point_q->z = q1->z + v.z * t;

		intercept_point_p->x = p1->x + u.x * s;
		intercept_point_p->y = p1->y + u.y * s;
		intercept_point_p->z = p1->z + u.z * s;

		return LINE_LINE_INTERCEPT_CONVERGE;
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int line_line_2d_intercept (const vec2d *p1, const vec2d *p2, const vec2d *q1, const vec2d *q2, vec2d *intercept_point)
{

	float
		ax1, ax2, ay1, ay2,
		bx1, bx2, by1, by2,
		dax, day,
		dbx, dby;

	float
		x, y,
		s, t,
		ma, mb,
		ca, cb;

	ASSERT (p1);

	ASSERT (p2);

	ASSERT (q1);

	ASSERT (q2);

	ASSERT (intercept_point);

	ax1 = p1->x;
	ay1 = p1->y;

	ax2 = p2->x;
	ay2 = p2->y;

	bx1 = q1->x;
	by1 = q1->y;

	bx2 = q2->x;
	by2 = q2->y;

	dax = ax2 - ax1;
	day = ay2 - ay1;

	dbx = bx2 - bx1;
	dby = by2 - by1;

	//
	// check for verticals
	//

	if ( ( dax == 0.0 ) && ( dbx == 0.0 ) )
	{
		return FALSE;
	}

	if ( dax == 0.0 )
	{
		x = ax1;

		mb = dby / dbx;

		cb = by1 - ( mb * bx1 );

		y = ( mb * x ) + cb;
	}
	else if ( dbx == 0.0 )
	{
		x = bx1;

		ma = day / dax;

		ca = ay1 - ( ma * ax1 );

		y = ( ma * x ) + ca;
	}
	else
	{
		//
		// find gradients
		//

		ma = day / dax;

		mb = dby / dbx;

		if ( ma == mb )
		{
			// lines are parallel

			return FALSE;
		}

		//
		// find constants
		//

		ca = ay1 - ( ma * ax1 );

		cb = by1 - ( mb * bx1 );

		//
		// find intercept points
		//

		x = ( cb - ca ) / ( ma - mb );

		y = ( ma * x ) + ca;
	}

	//
	//

	intercept_point->x = x;
	intercept_point->y = y;

	//
	// now work out if the lines actually cross
	//

	// line a

	if ( fabs( day ) > fabs( dax ) )
	{
		s = ( y - ay1 ) / day;
	}
	else
	{
		s = ( x - ax1 ) / dax;
	}

	// line b

	if ( fabs( dby ) > fabs( dbx ) )
	{
		t = ( y - by1 ) / dby;
	}
	else
	{
		t = ( x - bx1 ) / dbx;
	}

	//
	// if the intercept point lies on both lines then return TRUE ( i.e. the lines cross )
	//

	if ( ( t >= 0.0 ) && ( t <= 1.0 ) )
	{
		if ( ( s >= 0.0 ) && ( s <= 1.0 ) )
		{
			return TRUE;
		}
	}

	return FALSE;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_2d_vector_dot_product( const vec2d *a, const vec2d *b )
{
	vec2d
		p, q;

	ASSERT ( a );

	ASSERT ( b );

	p.x = a->x;
	p.y = a->y;
	q.x = b->x;
	q.y = b->y;

	normalise_2d_vector( &p );
	normalise_2d_vector( &q );

	return get_2d_unit_vector_dot_product( &p, &q );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_3d_vector_dot_product( const vec3d *a, const vec3d *b )
{
	vec3d
		p, q;

	ASSERT ( a );

	ASSERT ( b );

	p.x = a->x;
	p.y = a->y;
	p.z = a->z;
	q.x = b->x;
	q.y = b->y;
	q.z = b->z;

	normalise_3d_vector( &p );
	normalise_3d_vector( &q );

	return get_3d_unit_vector_dot_product( &p, &q );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_2d_unit_vector_dot_product (const vec2d *a, const vec2d *b)
{
	float
		result;

	ASSERT (a);

	ASSERT (b);

	result = (a->x * b->x) + (a->y * b->y);

	result = bound (result, -1.0, 1.0);

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_3d_unit_vector_dot_product (const vec3d *a, const vec3d *b)
{
	float
		result;

	ASSERT (a);

	ASSERT (b);

	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);

	result = bound (result, -1.0, 1.0);

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// result = v1 X v2 (result is a unit vector if v1 and v2 are perpendicular unit vectors)
//

void get_3d_vector_cross_product (vec3d *result, const vec3d *v1, const vec3d *v2)
{
	ASSERT (result);

	ASSERT (v1);

	ASSERT (v2);

	result->x = (v1->y * v2->z) - (v2->y * v1->z);
	result->y = (v1->z * v2->x) - (v2->z * v1->x);
	result->z = (v1->x * v2->y) - (v2->x * v1->y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_unit_vector_from_heading(vec2d* result, float heading)
{
	ASSERT (result);

	result->x = sin ( heading );
	result->y = cos ( heading );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_3d_unit_vector_from_heading_and_pitch (vec3d *result, float heading, float pitch)
{
	float
		sinh,
		cosh,
		sinp,
		cosp;

	ASSERT (result);

	sinh = sin ( heading );
	cosh = cos ( heading );

	sinp = sin ( pitch );
	cosp = cos ( pitch );

	result->x = cosp * sinh;

	result->y = sinp;

	result->z = cosp * cosh;

	normalise_3d_vector (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_heading_and_pitch_from_3d_unit_vector (const vec3d *v, float *heading, float *pitch)
{
	ASSERT (v);

	ASSERT (heading);

	ASSERT (pitch);

	*heading = atan2 (v->x, v->z);

	*pitch = asin (v->y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_3d_vector_cube_cube_intersect (const vec3d *v1a, const vec3d *v1b, const vec3d *v2a, const vec3d *v2b)
{
	float
		x1min,
		x1max,
		x2min,
		x2max,
		y1min,
		y1max,
		y2min,
		y2max,
		z1min,
		z1max,
		z2min,
		z2max;

	ASSERT (v1a);

	ASSERT (v1b);

	ASSERT (v2a);

	ASSERT (v2b);

	////////////////////////////////////////

	if (v1a->x <= v1b->x)
	{
		x1min = v1a->x;
		x1max = v1b->x;
	}
	else
	{
		x1min = v1b->x;
		x1max = v1a->x;
	}

	if (v2a->x <= v2b->x)
	{
		x2min = v2a->x;
		x2max = v2b->x;
	}
	else
	{
		x2min = v2b->x;
		x2max = v2a->x;
	}

	if (x2max < x1min)
	{
		return (FALSE);
	}

	if (x2min > x1max)
	{
		return (FALSE);
	}

	////////////////////////////////////////

	if (v1a->y <= v1b->y)
	{
		y1min = v1a->y;
		y1max = v1b->y;
	}
	else
	{
		y1min = v1b->y;
		y1max = v1a->y;
	}

	if (v2a->y <= v2b->y)
	{
		y2min = v2a->y;
		y2max = v2b->y;
	}
	else
	{
		y2min = v2b->y;
		y2max = v2a->y;
	}

	if (y2max < y1min)
	{
		return (FALSE);
	}

	if (y2min > y1max)
	{
		return (FALSE);
	}

	////////////////////////////////////////

	if (v1a->z <= v1b->z)
	{
		z1min = v1a->z;
		z1max = v1b->z;
	}
	else
	{
		z1min = v1b->z;
		z1max = v1a->z;
	}

	if (v2a->z <= v2b->z)
	{
		z2min = v2a->z;
		z2max = v2b->z;
	}
	else
	{
		z2min = v2b->z;
		z2max = v2a->z;
	}

	if (z2max < z1min)
	{
		return (FALSE);
	}

	if (z2min > z1max)
	{
		return (FALSE);
	}

	////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// calc intersect point (pi) of line (p1, p2) with triangle (pa, pb, pc)
//
// intersect point (pi) and face normal (ni) are only valid if the return value is TRUE

int get_3d_line_triangle_intersection (const vec3d *p1, const vec3d *p2, const vec3d *pa, const vec3d *pb, const vec3d *pc, vec3d *pi, vec3d *ni)
{
	float
		length,
		d,
		denom,
		mu,
		angle_aib,
		angle_aic,
		angle_bic,
		acos_angle_aib,
		acos_angle_aic,
		acos_angle_bic,
		total;

	vec3d
		vec_ab,
		vec_ac,
		vec_12,
		vec_ia,
		vec_ib,
		vec_ic;

	ASSERT (p1);
	ASSERT (p2);
	ASSERT (pa);
	ASSERT (pb);
	ASSERT (pc);
	ASSERT (pi);
	ASSERT (ni);

	////////////////////////////////////////

	vec_ab.x = pb->x - pa->x;
	vec_ab.y = pb->y - pa->y;
	vec_ab.z = pb->z - pa->z;

	vec_ac.x = pc->x - pa->x;
	vec_ac.y = pc->y - pa->y;
	vec_ac.z = pc->z - pa->z;

	ni->x = (vec_ab.y * vec_ac.z) - (vec_ab.z * vec_ac.y);
	ni->y = (vec_ab.z * vec_ac.x) - (vec_ab.x * vec_ac.z);
	ni->z = (vec_ab.x * vec_ac.y) - (vec_ab.y * vec_ac.x);

	length = sqrt ((ni->x * ni->x) + (ni->y * ni->y) + (ni->z * ni->z));

	if (length == 0.0)
	{
		return (FALSE);
	}

	normalise_3d_vector_given_magnitude (ni, length);

	////////////////////////////////////////

	d = - (ni->x * pa->x) - (ni->y * pa->y) - (ni->z * pa->z);

	////////////////////////////////////////

	vec_12.x = p2->x - p1->x;
	vec_12.y = p2->y - p1->y;
	vec_12.z = p2->z - p1->z;

	denom = (ni->x * vec_12.x) + (ni->y * vec_12.y) + (ni->z * vec_12.z);

	if (fabs (denom) == 0.0)
	{
		return (FALSE);
	}

	////////////////////////////////////////

	mu = - (d + (ni->x * p1->x) + (ni->y * p1->y) + (ni->z * p1->z)) / denom;

	if ((mu < 0.0) || (mu > 1.0))
	{
		return (FALSE);
	}

	////////////////////////////////////////

	pi->x = p1->x + mu * (vec_12.x);
	pi->y = p1->y + mu * (vec_12.y);
	pi->z = p1->z + mu * (vec_12.z);

	////////////////////////////////////////

	vec_ia.x = pa->x - pi->x;
	vec_ia.y = pa->y - pi->y;
	vec_ia.z = pa->z - pi->z;

	length = sqrt ((vec_ia.x * vec_ia.x) + (vec_ia.y * vec_ia.y) + (vec_ia.z * vec_ia.z));

	if (length == 0.0)
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ABC");

		#endif

		return (TRUE);
	}

	normalise_3d_vector_given_magnitude (&vec_ia, length);

	////////////////////////////////////////

	vec_ib.x = pb->x - pi->x;
	vec_ib.y = pb->y - pi->y;
	vec_ib.z = pb->z - pi->z;

	length = sqrt ((vec_ib.x * vec_ib.x) + (vec_ib.y * vec_ib.y) + (vec_ib.z * vec_ib.z));

	if (length == 0.0)
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ABC");

		#endif

		return (TRUE);
	}

	normalise_3d_vector_given_magnitude (&vec_ib, length);

	////////////////////////////////////////

	vec_ic.x = pc->x - pi->x;
	vec_ic.y = pc->y - pi->y;
	vec_ic.z = pc->z - pi->z;

	length = sqrt ((vec_ic.x * vec_ic.x) + (vec_ic.y * vec_ic.y) + (vec_ic.z * vec_ic.z));

	if (length == 0.0)
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ABC");

		#endif

		return (TRUE);
	}

	normalise_3d_vector_given_magnitude (&vec_ic, length);

	////////////////////////////////////////

	angle_aib = (vec_ia.x * vec_ib.x) + (vec_ia.y * vec_ib.y) + (vec_ia.z * vec_ib.z);
	angle_bic = (vec_ib.x * vec_ic.x) + (vec_ib.y * vec_ic.y) + (vec_ib.z * vec_ic.z);
	angle_aic = (vec_ic.x * vec_ia.x) + (vec_ic.y * vec_ia.y) + (vec_ic.z * vec_ia.z);

	acos_angle_aib = acos (angle_aib);
	acos_angle_bic = acos (angle_bic);
	acos_angle_aic = acos (angle_aic);

	total = acos_angle_aib + acos_angle_bic + acos_angle_aic;

	if ((total < (-PI2 + 0.01)) || (total > (PI2 - 0.01)))
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ABC");

		#endif

		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// calc intersect point (pi) of line (p1, p2) with quad (pa, pb, pc, pd)
//
// intersect point (pi) and face normal (ni) are only valid if the return value is TRUE
//
// quad points must be ordered

int get_3d_line_quad_intersection (const vec3d *p1, const vec3d *p2, const vec3d *pa, const vec3d *pb, const vec3d *pc, const vec3d *pd, vec3d *pi, vec3d *ni)
{
	float
		length,
		d,
		denom,
		mu,
		angle_aib,
		angle_aic,
		angle_aid,
		angle_bic,
		angle_cid,
		acos_angle_aib,
		acos_angle_aic,
		acos_angle_aid,
		acos_angle_bic,
		acos_angle_cid,
		total;

	vec3d
		vec_ab,
		vec_ac,
		vec_12,
		vec_ia,
		vec_ib,
		vec_ic,
		vec_id;

	ASSERT (p1);
	ASSERT (p2);
	ASSERT (pa);
	ASSERT (pb);
	ASSERT (pc);
	ASSERT (pd);
	ASSERT (pi);
	ASSERT (ni);

	////////////////////////////////////////

	vec_ab.x = pb->x - pa->x;
	vec_ab.y = pb->y - pa->y;
	vec_ab.z = pb->z - pa->z;

	vec_ac.x = pc->x - pa->x;
	vec_ac.y = pc->y - pa->y;
	vec_ac.z = pc->z - pa->z;

	ni->x = (vec_ab.y * vec_ac.z) - (vec_ab.z * vec_ac.y);
	ni->y = (vec_ab.z * vec_ac.x) - (vec_ab.x * vec_ac.z);
	ni->z = (vec_ab.x * vec_ac.y) - (vec_ab.y * vec_ac.x);

	length = sqrt ((ni->x * ni->x) + (ni->y * ni->y) + (ni->z * ni->z));

	if (length == 0.0)
	{
		return (FALSE);
	}

	normalise_3d_vector_given_magnitude (ni, length);

	////////////////////////////////////////

	d = - (ni->x * pa->x) - (ni->y * pa->y) - (ni->z * pa->z);

	////////////////////////////////////////

	vec_12.x = p2->x - p1->x;
	vec_12.y = p2->y - p1->y;
	vec_12.z = p2->z - p1->z;

	denom = (ni->x * vec_12.x) + (ni->y * vec_12.y) + (ni->z * vec_12.z);

	if (fabs (denom) == 0.0)
	{
		return (FALSE);
	}

	////////////////////////////////////////

	mu = - (d + (ni->x * p1->x) + (ni->y * p1->y) + (ni->z * p1->z)) / denom;

	if ((mu < 0.0) || (mu > 1.0))
	{
		return (FALSE);
	}

	////////////////////////////////////////

	pi->x = p1->x + mu * (vec_12.x);
	pi->y = p1->y + mu * (vec_12.y);
	pi->z = p1->z + mu * (vec_12.z);

	////////////////////////////////////////

	vec_ia.x = pa->x - pi->x;
	vec_ia.y = pa->y - pi->y;
	vec_ia.z = pa->z - pi->z;

	length = sqrt ((vec_ia.x * vec_ia.x) + (vec_ia.y * vec_ia.y) + (vec_ia.z * vec_ia.z));

	if (length == 0.0)
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ABC");

		#endif

		return (TRUE);
	}

	normalise_3d_vector_given_magnitude (&vec_ia, length);

	////////////////////////////////////////

	vec_ib.x = pb->x - pi->x;
	vec_ib.y = pb->y - pi->y;
	vec_ib.z = pb->z - pi->z;

	length = sqrt ((vec_ib.x * vec_ib.x) + (vec_ib.y * vec_ib.y) + (vec_ib.z * vec_ib.z));

	if (length == 0.0)
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ABC");

		#endif

		return (TRUE);
	}

	normalise_3d_vector_given_magnitude (&vec_ib, length);

	////////////////////////////////////////

	vec_ic.x = pc->x - pi->x;
	vec_ic.y = pc->y - pi->y;
	vec_ic.z = pc->z - pi->z;

	length = sqrt ((vec_ic.x * vec_ic.x) + (vec_ic.y * vec_ic.y) + (vec_ic.z * vec_ic.z));

	if (length == 0.0)
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ABC");

		#endif

		return (TRUE);
	}

	normalise_3d_vector_given_magnitude (&vec_ic, length);

	////////////////////////////////////////

	angle_aib = (vec_ia.x * vec_ib.x) + (vec_ia.y * vec_ib.y) + (vec_ia.z * vec_ib.z);
	angle_bic = (vec_ib.x * vec_ic.x) + (vec_ib.y * vec_ic.y) + (vec_ib.z * vec_ic.z);
	angle_aic = (vec_ic.x * vec_ia.x) + (vec_ic.y * vec_ia.y) + (vec_ic.z * vec_ia.z);

	acos_angle_aib = acos (angle_aib);
	acos_angle_bic = acos (angle_bic);
	acos_angle_aic = acos (angle_aic);

	total = acos_angle_aib + acos_angle_bic + acos_angle_aic;

	if ((total < (-PI2 + 0.01)) || (total > (PI2 - 0.01)))
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ABC");

		#endif

		return (TRUE);
	}

	////////////////////////////////////////

	vec_id.x = pd->x - pi->x;
	vec_id.y = pd->y - pi->y;
	vec_id.z = pd->z - pi->z;

	length = sqrt ((vec_id.x * vec_id.x) + (vec_id.y * vec_id.y) + (vec_id.z * vec_id.z));

	if (length == 0.0)
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ACD");

		#endif

		return (TRUE);
	}

	normalise_3d_vector_given_magnitude (&vec_id, length);

	////////////////////////////////////////

	angle_cid = (vec_ic.x * vec_id.x) + (vec_ic.y * vec_id.y) + (vec_ic.z * vec_id.z);
	angle_aid = (vec_id.x * vec_ia.x) + (vec_id.y * vec_ia.y) + (vec_id.z * vec_ia.z);

	acos_angle_cid = acos (angle_cid);
	acos_angle_aid = acos (angle_aid);

	total = acos_angle_aic + acos_angle_cid + acos_angle_aid;

	if ((total < (-PI2 + 0.01)) || (total > (PI2 - 0.01)))
	{
		#if DEBUG_MODULE_LINE_TRIANGLE_INTERCEPT

		debug_log ("Collision triangle ACD");

		#endif

		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void invert_3d_vector (vec3d *vector)
{

	vector->x = -vector->x;
	vector->y = -vector->y;
	vector->z = -vector->z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rotate_2d_vector (vec2d *vector, float theta)
{
	float
		cos_theta,
		sin_theta;

	vec2d
		result;

	cos_theta = cos (theta);
	sin_theta = sin (theta);

	result.x = (vector->x * cos_theta) + (vector->y * sin_theta);
	result.y = (-vector->x * sin_theta) + (vector->y * cos_theta);

	vector->x = result.x;
	vector->y = result.y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rotate_3d_vector (vec3d *vector, float theta)
{
	float
		cos_theta,
		sin_theta;

	vec3d
		result;

	cos_theta = cos (theta);
	sin_theta = sin (theta);

	result.x = (vector->x * cos_theta) + (vector->z * sin_theta);
	result.z = (-vector->x * sin_theta) + (vector->z * cos_theta);

	vector->x = result.x;
	vector->z = result.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DOUBLE LIBRARY
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double normalise_3d_double_vector ( double_vec3d *vector )
{

	double
		x,
		y,
		z,
		length,
		one_over_length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );
	z = ( ( vector->z ) * ( vector->z ) );

	length = sqrt ( x + y + z );

	ASSERT ( length > 0.0 );

	one_over_length = 1.0 / length;

	vector->x = ( vector->x * one_over_length );
	vector->y = ( vector->y * one_over_length );
	vector->z = ( vector->z * one_over_length );

	return ( length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double normalise_any_3d_double_vector ( double_vec3d *vector )
{

	double
		x,
		y,
		z,
		length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );
	z = ( ( vector->z ) * ( vector->z ) );

	length = sqrt ( x + y + z );

	if ( length > 0 )
	{

		double
			one_over_length;

		one_over_length = 1.0 / length;

		vector->x = ( vector->x * one_over_length );
		vector->y = ( vector->y * one_over_length );
		vector->z = ( vector->z * one_over_length );
	}
	else
	{

		vector->x = 0;
		vector->y = 0;
		vector->z = 0;
	}

	return ( length );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double get_3d_double_vector_magnitude ( const double_vec3d *vector )
{

	double
		x,
		y,
		z;

	ASSERT ( vector );

	x = ( vector->x * vector->x );
	y = ( vector->y * vector->y );
	z = ( vector->z * vector->z );

	return ( sqrt ( x + y + z ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double get_3d_double_vector_dot_product( const double_vec3d *a, const double_vec3d *b )
{
	double_vec3d
		p, q;

	ASSERT ( a );

	ASSERT ( b );

	p.x = a->x;
	p.y = a->y;
	p.z = a->z;
	q.x = b->x;
	q.y = b->y;
	q.z = b->z;

	normalise_3d_double_vector( &p );
	normalise_3d_double_vector( &q );

	return get_3d_unit_double_vector_dot_product( &p, &q );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double get_3d_unit_double_vector_dot_product (const double_vec3d *a, const double_vec3d *b)
{
	double
		result;

	ASSERT (a);

	ASSERT (b);

	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);

	result = bound (result, -1.0, 1.0);

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_3d_double_vector_cross_product (double_vec3d *result, const double_vec3d *v1, const double_vec3d *v2)
{
	ASSERT (result);

	ASSERT (v1);

	ASSERT (v2);

	result->x = (v1->y * v2->z) - (v2->y * v1->z);
	result->y = (v1->z * v2->x) - (v2->z * v1->x);
	result->z = (v1->x * v2->y) - (v2->x * v1->y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void invert_3d_double_vector (double_vec3d *vector)
{

	vector->x = -vector->x;
	vector->y = -vector->y;
	vector->z = -vector->z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rotate_2d_double_vector (double_vec3d *vector, float theta)
{
	float
		cos_theta,
		sin_theta;

	vec3d
		result;

	cos_theta = cos (theta);
	sin_theta = sin (theta);

	result.x = (vector->x * cos_theta) + (vector->z * sin_theta);
	result.z = (-vector->x * sin_theta) + (vector->z * cos_theta);

	vector->x = result.x;
	vector->y = 0.0;
	vector->z = result.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_3d_unit_double_vector_from_heading_and_pitch (double_vec3d *result, double heading, double pitch)
{
	double
		sinh,
		cosh,
		sinp,
		cosp;

	ASSERT (result);

	sinh = sin ( heading );
	cosh = cos ( heading );

	sinp = sin ( pitch );
	cosp = cos ( pitch );

	result->x = cosp * sinh;

	result->y = sinp;

	result->z = cosp * cosh;

	normalise_3d_double_vector (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void copy_vec3d_to_double_vec3d (const vec3d *vec1, double_vec3d *vec2)
{

	vec2->x = vec1->x;
	vec2->y = vec1->y;
	vec2->z = vec1->z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void copy_double_vec3d_to_vec3d (const double_vec3d *vec1, vec3d *vec2)
{

	vec2->x = vec1->x;
	vec2->y = vec1->y;
	vec2->z = vec1->z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
