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

#define SLERP_DELTA 0.000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void slerp_quaternion ( quaternion *result, quaternion *from, quaternion *to, float t )
{

	double
		to1[4];

	double
		omega,
		cosom,
		sinom,
		scale0,
		scale1;

	//
	// Dot product to get the cosine of the angle between the two quaternions
	//

	cosom = ( ( from->x * to->x ) + ( from->y * to->y ) + ( from->z * to->z ) + ( from->w * to->w ) );

	//
	// Adjust the signs ( if necessary )
	//

	if ( cosom < 0.0 )
	{

		cosom = -cosom;

		to1[0] = - to->x;
		to1[1] = - to->y;
		to1[2] = - to->z;
		to1[3] = - to->w;
	}
	else
	{

		to1[0] = to->x;
		to1[1] = to->y;
		to1[2] = to->z;
		to1[3] = to->w;
	}

	//
	// Calculate coefficients
	//

	if ( ( 1.0 - cosom ) > SLERP_DELTA )
	{

		//
		// Slerp routine
		//

		omega = acos ( cosom );

		sinom = sin ( omega );

		scale0 = sin ( ( 1.0 - t ) * omega ) / sinom;

		scale1 = sin ( t * omega ) / sinom;
	}
	else
	{

		//
		// Two positions very close together - interpolate
		//

		scale0 = 1.0 - t;
		scale1 = t;
	}

	result->x = scale0 * ( double )from->x + scale1 * ( double ) to1[0];
	result->y = scale0 * ( double )from->y + scale1 * ( double ) to1[1];
	result->z = scale0 * ( double )from->z + scale1 * ( double ) to1[2];
	result->w = scale0 * ( double )from->w + scale1 * ( double ) to1[3];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void multiply_quaternion_by_quaternion ( quaternion *result, quaternion *q1, quaternion *q2 )
{

	float
		a,
		b,
		c,
		d,
		e,
		f,
		g,
		h;

	a = ( q1->w + q1->x ) * ( q2->w + q2->x );
	b = ( q1->z - q1->y ) * ( q2->y - q2->z );
	c = ( q1->x - q1->w ) * ( q2->y - q2->z );
	d = ( q1->y + q1->z ) * ( q2->x - q2->w );
	e = ( q1->x + q1->z ) * ( q2->x + q2->y );
	f = ( q1->x - q1->z ) * ( q2->x - q2->y );
	g = ( q1->w + q1->y ) * ( q2->w - q2->z );
	h = ( q1->w - q1->y ) * ( q2->w + q2->z );

	result->w = b + ( -e - f + g + h ) / 2;
	result->x = a - ( e + f + g + h ) / 2;
	result->y = -c + ( e - f + g - h ) / 2;
	result->z = -d + ( e - f - g + h ) / 2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void multiply_quaternion_by_vec3d ( vec3d *result, quaternion *q, vec3d *v )
{

	float
		a,
		c,
		d,
		e,
		f,
		g,
		h;

	a = ( q->w + q->x ) * ( v->x );
	c = ( q->x - q->w ) * ( v->y - v->z );
	d = ( q->y + q->z ) * ( v->x );
	e = ( q->x + q->z ) * ( v->x + v->y );
	f = ( q->x - q->z ) * ( v->x - v->y );
	g = ( q->w + q->y ) * ( v->z );
	h = ( q->w - q->y ) * ( v->z );

	result->x = a - ( e + f + g + h ) / 2;
	result->y = -c + ( e - f + g - h ) / 2;
	result->z = -d + ( e - f - g + h ) / 2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_quaternion_to_matrix3x3 ( matrix3x3 result, quaternion *q )
{

	double
		wx,
		wy,
		wz,
		xx,
		yy,
		yz,
		xy,
		xz,
		zz,
		x2,
		y2,
		z2;

	x2 = q->x + q->x;
	y2 = q->y + q->y;
	z2 = q->z + q->z;

	xx = q->x * x2;
	xy = q->x * y2;
	xz = q->x * z2;

	yy = q->y * y2;
	yz = q->y * z2;

	zz = q->z * z2;

	wx = q->w * x2;
	wy = q->w * y2;
	wz = q->w * z2;

	result[0][0] = 1.0 - ( yy + zz );
	result[0][1] = xy - wz;
	result[0][2] = xz + wy;

	result[1][0] = xy + wz;
	result[1][1] = 1.0 - ( xx + zz );
	result[1][2] = yz - wx;

	result[2][0] = xz - wy;
	result[2][1] = yz + wx;
	result[2][2] = 1.0 - ( xx + yy );

	normalise_3d_vector ( ( vec3d * ) &result[0][0] );
	normalise_3d_vector ( ( vec3d * ) &result[1][0] );
	normalise_3d_vector ( ( vec3d * ) &result[2][0] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_matrix3x3_to_quaternion ( quaternion *result, matrix3x3 matrix )
{

	double
		tr,
		s,
		q[4];

	int
		i,
		j,
		k,
		nxt[3] = { 1, 2, 0 };

	//
	// Calculate the matrix diagonal
	//

	tr = matrix[0][0] + matrix[1][1] + matrix[2][2];

	if ( tr > 0.0 )
	{

		//
		// Matrix diagonal is positive.
		//

		s = sqrt ( tr + 1.0 );

		result->w = s / 2.0;

		s = 0.5 / s;

		result->x = ( matrix[2][1] - matrix[1][2] ) * s;
		result->y = ( matrix[0][2] - matrix[2][0] ) * s;
		result->z = ( matrix[1][0] - matrix[0][1] ) * s;
	}
	else
	{

		//
		// Matrix diagonal is negative.
		//

		i = 0;

		if ( matrix[1][1] > matrix[0][0] )
		{

			i = 1;
		}

		if ( matrix[2][2] > matrix[i][i] )
		{

			i = 2;
		}

		j = nxt[i];
		k = nxt[j];

		s = sqrt ( ( matrix[i][i] - ( matrix[j][j] + matrix[k][k] ) ) + 1.0 );

		q[i] = s * 0.5;

		if ( s != 0.0 )
		{

			s = 0.5 / s;
		}

		q[3] = ( matrix[k][j] - matrix[j][k] ) * s;
		q[j] = ( matrix[j][i] + matrix[i][j] ) * s;
		q[k] = ( matrix[k][i] + matrix[i][k] ) * s;

		result->x = q[0];
		result->y = q[1];
		result->z = q[2];
		result->w = q[3];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

