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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Compute Hermite spline coeficients for t, where 0 <= t <= 1.
//

static void generate_hermite_values ( float t, float *h1, float *h2, float *h3, float *h4 )
{

	float
		t2,
		t3,
		z;

	t2 = t * t;
	t3 = t * t2;
	z = 3.0 * t2 - t3 - t3;

	*h1 = 1.0 - z;
	*h2 = z;
	*h3 = t3 - t2 - t2 + t;
	*h4 = t3 - t2;
}

//
// Compute the motion channel vector for the given step. Step varies from 0 to 1
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_keyframe ( int number_of_keyframes, object_3d_sub_object_keyframe *keyframes, object_3d_sub_object_keyframe *result, float step )
{

	object_3d_sub_object_keyframe
		*key0 = nullptr,
		*key1 = nullptr;

	float
		t,
		h1,
		h2,
		h3,
		h4,
		dd0a,
		dd0b,
		ds1a,
		ds1b,
		adj0,
		adj1;

	int
		tlength;

	//
	// If there is one keyframe, that is the one to return
	//

	if ( number_of_keyframes == 1 )
	{

		*result = *keyframes;
	}
	else
	{
	
		//
		// Get keyframe pair to evaluate.  This should be within the range
		// of the motion or this will raise an illegal access.
		//

		step *= keyframes[ ( number_of_keyframes - 1 ) ].index;

		key0 = keyframes;
	
		while ( step > key0[1].index )
		{
	
			key0++;
		}
	
		key1 = key0 + 1;
	
		step -= key0->index;
	
		//
		// Get tween length and fractional tween position.
		//
	
		tlength = key1->index - key0->index;
	
		t = step / tlength;
	
		//
		// Precompute spline coefficients.
		//
	
		if ( !key1->linear )
		{
	
			generate_hermite_values ( t, &h1, &h2, &h3, &h4 );
	
			dd0a = ( 1.0 - key0->tension ) * ( 1.0 + key0->continuity ) * ( 1.0 + key0->bias );
			dd0b = ( 1.0 - key0->tension ) * ( 1.0 - key0->continuity ) * ( 1.0 - key0->bias );
			ds1a = ( 1.0 - key1->tension ) * ( 1.0 - key1->continuity ) * ( 1.0 + key1->bias );
			ds1b = ( 1.0 - key1->tension ) * ( 1.0 + key1->continuity ) * ( 1.0 - key1->bias );
	
			if ( key0->index != 0 )
			{
	
				adj0 = ( float ) tlength /  ( float ) ( key1->index - key0[-1].index );
			}
	
			if ( key1 != &keyframes[ ( number_of_keyframes -1 ) ] )
			{
	
				 adj1 = ( float ) tlength / ( float ) ( key1[1].index - key0->index );
			}
		}
	
		//
		// Compute the interpolate terms
		//
	
		{

			float
				dheading,
				dpitch,
				droll,
				dx,
				dy,
				dz,
				dscale_x,
				dscale_y,
				dscale_z;

			dheading = key1->heading - key0->heading;
			dpitch = key1->pitch - key0->pitch;
			droll = key1->roll - key0->roll;
			dx = key1->x - key0->x;
			dy = key1->y - key0->y;
			dz = key1->z - key0->z;
			dscale_x = key1->scale_x - key0->scale_x;
			dscale_y = key1->scale_y - key0->scale_y;
			dscale_z = key1->scale_z - key0->scale_z;

			if ( !key1->linear )
			{

				float
					dd0heading, ds1heading,
					dd0pitch, ds1pitch,
					dd0roll, ds1roll,
					dd0x, ds1x,
					dd0y, ds1y,
					dd0z, ds1z,
					dd0scale_x, ds1scale_x,
					dd0scale_y, ds1scale_y,
					dd0scale_z, ds1scale_z;

				if ( key0->index == 0 )
				{
	
					dd0heading	= 0.5 * ( dd0a + dd0b ) * dheading;
					dd0pitch		= 0.5 * ( dd0a + dd0b ) * dpitch;
					dd0roll		= 0.5 * ( dd0a + dd0b ) * droll;
					dd0x			= 0.5 * ( dd0a + dd0b ) * dx;
					dd0y			= 0.5 * ( dd0a + dd0b ) * dy;
					dd0z			= 0.5 * ( dd0a + dd0b ) * dz;
					dd0scale_x	= 0.5 * ( dd0a + dd0b ) * dscale_x;
					dd0scale_y	= 0.5 * ( dd0a + dd0b ) * dscale_y;
					dd0scale_z	= 0.5 * ( dd0a + dd0b ) * dscale_z;
				}
				else
				{
	
					dd0heading	= adj0 * ( dd0a * ( key0->heading - key0[-1].heading ) + dd0b * dheading );
					dd0pitch		= adj0 * ( dd0a * ( key0->pitch - key0[-1].pitch ) + dd0b * dpitch );
					dd0roll		= adj0 * ( dd0a * ( key0->roll - key0[-1].roll ) + dd0b * droll );
					dd0x			= adj0 * ( dd0a * ( key0->x - key0[-1].x ) + dd0b * dx );
					dd0y			= adj0 * ( dd0a * ( key0->y - key0[-1].y ) + dd0b * dy );
					dd0z			= adj0 * ( dd0a * ( key0->z - key0[-1].z ) + dd0b * dz );
					dd0scale_x	= adj0 * ( dd0a * ( key0->scale_x - key0[-1].scale_x ) + dd0b * dscale_x );
					dd0scale_y	= adj0 * ( dd0a * ( key0->scale_y - key0[-1].scale_y ) + dd0b * dscale_y );
					dd0scale_z	= adj0 * ( dd0a * ( key0->scale_z - key0[-1].scale_z ) + dd0b * dscale_z );
				}
	
				if ( key1 == &keyframes[( number_of_keyframes - 1 ) ] )
				{
	
					ds1heading	= 0.5 * ( ds1a + ds1b ) * dheading;
					ds1pitch		= 0.5 * ( ds1a + ds1b ) * dpitch;
					ds1roll		= 0.5 * ( ds1a + ds1b ) * droll;
					ds1x			= 0.5 * ( ds1a + ds1b ) * dx;
					ds1y			= 0.5 * ( ds1a + ds1b ) * dy;
					ds1z			= 0.5 * ( ds1a + ds1b ) * dz;
					ds1scale_x	= 0.5 * ( ds1a + ds1b ) * dscale_x;
					ds1scale_y	= 0.5 * ( ds1a + ds1b ) * dscale_y;
					ds1scale_z	= 0.5 * ( ds1a + ds1b ) * dscale_z;
				}
				else
				{
	
					ds1heading	= adj1 * ( ( ds1a * dheading ) + ds1b * ( key1[1].heading - key1->heading ) );
					ds1pitch		= adj1 * ( ( ds1a * dpitch ) + ds1b * ( key1[1].pitch - key1->pitch ) );
					ds1roll		= adj1 * ( ( ds1a * droll ) + ds1b * ( key1[1].roll - key1->roll ) );
					ds1x			= adj1 * ( ( ds1a * dx ) + ds1b * ( key1[1].x - key1->x ) );
					ds1y			= adj1 * ( ( ds1a * dy ) + ds1b * ( key1[1].y - key1->y ) );
					ds1z			= adj1 * ( ( ds1a * dz ) + ds1b * ( key1[1].z - key1->z ) );
					ds1scale_x	= adj1 * ( ( ds1a * dscale_x ) + ds1b * ( key1[1].scale_x - key1->scale_x ) );
					ds1scale_y	= adj1 * ( ( ds1a * dscale_y ) + ds1b * ( key1[1].scale_y - key1->scale_y ) );
					ds1scale_z	= adj1 * ( ( ds1a * dscale_z ) + ds1b * ( key1[1].scale_z - key1->scale_z ) );
				}
	
				result->heading	= key0->heading * h1 + key1->heading * h2 + dd0heading * h3 + ds1heading * h4;
				result->pitch		= key0->pitch * h1 + key1->pitch * h2 + dd0pitch * h3 + ds1pitch * h4;
				result->roll		= key0->roll * h1 + key1->roll * h2 + dd0roll * h3 + ds1roll * h4;
				result->x			= key0->x * h1 + key1->x * h2 + dd0x * h3 + ds1x * h4;
				result->y			= key0->y * h1 + key1->y * h2 + dd0y * h3 + ds1y * h4;
				result->z			= key0->z * h1 + key1->z * h2 + dd0z * h3 + ds1z * h4;
				result->scale_x	= key0->scale_x * h1 + key1->scale_x * h2 + dd0scale_x * h3 + ds1scale_x * h4;
				result->scale_y	= key0->scale_y * h1 + key1->scale_y * h2 + dd0scale_y * h3 + ds1scale_y * h4;
				result->scale_z	= key0->scale_z * h1 + key1->scale_z * h2 + dd0scale_z * h3 + ds1scale_z * h4;
			}
			else
			{
	
				result->heading	= key0->heading + t * dheading;
				result->pitch		= key0->pitch + t * dpitch;
				result->roll		= key0->roll + t * droll;
				result->x			= key0->x + t * dx;
				result->y			= key0->y + t * dy;
				result->z			= key0->z + t * dz;
				result->scale_x	= key0->scale_x + t * dscale_x;
				result->scale_y	= key0->scale_y + t * dscale_y;
				result->scale_z	= key0->scale_z + t * dscale_z;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_value_keyframe ( int number_of_keyframes, object_3d_sub_object_value_keyframe *keyframes, object_3d_sub_object_value_keyframe *result, float step )
{

	object_3d_sub_object_value_keyframe
		*key0 = nullptr,
		*key1 = nullptr;

	float
		t,
		h1,
		h2,
		h3,
		h4,
		dd0a,
		dd0b,
		ds1a,
		ds1b,
		adj0,
		adj1;

	int
		tlength;

	//
	// If there is one keyframe, that is the one to return
	//

	if ( number_of_keyframes == 1 )
	{

		*result = *keyframes;
	}
	else
	{
	
		//
		// Get keyframe pair to evaluate.  This should be within the range
		// of the motion or this will raise an illegal access.
		//

		step *= keyframes[ ( number_of_keyframes - 1 ) ].index;

		key0 = keyframes;
	
		while ( step > key0[1].index )
		{
	
			key0++;
		}
	
		key1 = key0 + 1;
	
		step -= key0->index;
	
		//
		// Get tween length and fractional tween position.
		//
	
		tlength = key1->index - key0->index;
	
		t = step / tlength;
	
		//
		// Precompute spline coefficients.
		//
	
		if ( !key1->linear )
		{
	
			generate_hermite_values ( t, &h1, &h2, &h3, &h4 );
	
			dd0a = ( 1.0 - key0->tension ) * ( 1.0 + key0->continuity ) * ( 1.0 + key0->bias );
			dd0b = ( 1.0 - key0->tension ) * ( 1.0 - key0->continuity ) * ( 1.0 - key0->bias );
			ds1a = ( 1.0 - key1->tension ) * ( 1.0 - key1->continuity ) * ( 1.0 + key1->bias );
			ds1b = ( 1.0 - key1->tension ) * ( 1.0 + key1->continuity ) * ( 1.0 - key1->bias );
	
			if ( key0->index != 0 )
			{
	
				adj0 = ( float ) tlength /  ( float ) ( key1->index - key0[-1].index );
			}
	
			if ( key1 != &keyframes[ ( number_of_keyframes -1 ) ] )
			{
	
				 adj1 = ( float ) tlength / ( float ) ( key1[1].index - key0->index );
			}
		}
	
		//
		// Compute the interpolate terms
		//
	
		{

			float
				dvalue;

			dvalue = key1->value - key0->value;

			if ( !key1->linear )
			{

				float
					dd0value, ds1value;

				if ( key0->index == 0 )
				{
	
					dd0value	= 0.5 * ( dd0a + dd0b ) * dvalue;
				}
				else
				{
	
					dd0value	= adj0 * ( dd0a * ( key0->value - key0[-1].value ) + dd0b * dvalue );
				}
	
				if ( key1 == &keyframes[( number_of_keyframes - 1 ) ] )
				{
	
					ds1value	= 0.5 * ( ds1a + ds1b ) * dvalue;
				}
				else
				{
	
					ds1value	= adj1 * ( ( ds1a * dvalue ) + ds1b * ( key1[1].value - key1->value ) );
				}
	
				result->value	= key0->value * h1 + key1->value * h2 + dd0value * h3 + ds1value * h4;
			}
			else
			{
	
				result->value	= key0->value + t * dvalue;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
