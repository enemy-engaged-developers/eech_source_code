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

#include "graphics.h"

//
// The intensity of fog on the current face
//

D3DCOLOR
	d3d_fog_intensity;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	d3d_fog_start,
	d3d_fog_end,
	d3d_fog_factor,
	d3d_fog_constant,
	d3d_fog_density;

//
// The actual colour of the fog itself
//

rgb_colour
	d3d_fog_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	d3d_fog_enabled;

static float
	d3d_fog_distance,
	d3d_fog_distance_reciprocal,
	d3d_fog_distance_scaled;

static double
	d3d_fog_start_squared,
	d3d_fog_end_squared,
	d3d_fog_distance_squared,
	d3d_fog_distance_squared_reciprocal;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_fog_distance_value ( float z )
{

	float
		value;

	//
	// The equation for working out the fog value is:
	//
	//    Fog = 255 * ( 1 - ( ( Z - fog_start ) / ( fog_end - fog_start ) ) )
	//
	//	Which simplifies to:
	//
	//		distance = fog_end - fog_start
	//
	//    Fog = ( 255 / distance ) * ( distance - Z - fog_start )
	//
	//
	// Which again simplifies down:
	//
	//    distance = fog_end - fog_start
	//
	//		constant = distance - fog_start
	//
	//    factor = 255 / distance
	//
	//
	//    Fog = factor * ( constant - Z )
	//
	// The value this gives needs to be bounded to between 0 and 255.
	//
	// Optimisation:
	//
	//    because the factor value is always positive, we can do the check for the value of ( constant - Z )
	//     before we multiply by the factor. This means an early out for some cases.
	//

	value = d3d_fog_constant - z;

	if ( *( ( int * ) &value ) < *( ( int * ) &float_value_zero ) )
	{

		return ( 0.0 );
	}
	else
	{

		value *= d3d_fog_factor;

		if ( *( ( int * ) &value ) > *( ( int * ) &float_value_255 ) )
		{
	
			value = 255;
		}
	
		return ( value );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_int_fog_distance_value ( float z )
{

//	float
//		value;

	int
		ivalue;

	asm_convert_float_to_int ( ( ( d3d_fog_constant - z ) * d3d_fog_factor ), &ivalue );

//	ivalue = bound ( ivalue, 0, 255 );

	return ( ivalue );
/*



	value = d3d_fog_constant - z;

	if ( *( ( int * ) &value ) < *( ( int * ) &float_value_zero ) )
	{

		return ( 0 );
	}
	else
	{

		value *= d3d_fog_factor;

		if ( *( ( int * ) &value ) > *( ( int * ) &float_value_255 ) )
		{

			return ( 255 );
		}
		else
		{

			int
				int_value;

			convert_float_to_int ( value, &int_value );

			return ( int_value );
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_fog_parameters ( int enabled, rgb_colour colour, float start, float end )
{

	d3d_fog_start = start;

	d3d_fog_end = end;

	d3d_fog_distance = end - start;

	d3d_fog_distance_reciprocal = 1.0 / d3d_fog_distance;

	d3d_fog_distance_scaled = 255.0 / d3d_fog_distance;

	d3d_fog_start_squared = start * start;

	d3d_fog_end_squared = end * end;

	d3d_fog_distance_squared = d3d_fog_distance * d3d_fog_distance;

	d3d_fog_distance_squared_reciprocal = 1.0 / d3d_fog_distance_squared;

	d3d_fog_constant = d3d_fog_distance - d3d_fog_start;

	d3d_fog_factor = 255.0 / d3d_fog_distance;

	d3d_fog_density = 5.545177444 / d3d_fog_end;

	d3d_fog_colour = colour;

	d3d_fog_enabled = enabled;

	//
	// Initialise the fog face intensity to no fog.
	//

	d3d_fog_intensity = RGBA_MAKE ( 0, 0, 0, 255 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_fog_renderstates ( void )
{

	if ( d3d_fog_enabled )
	{

		set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, TRUE );

		set_d3d_int_state ( D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_NONE );
		set_d3d_int_state ( D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_NONE );

//		set_d3d_float_state ( D3DRENDERSTATE_FOGSTART, d3d_fog_start );
//		set_d3d_float_state ( D3DRENDERSTATE_FOGEND, d3d_fog_end );

		set_d3d_int_state ( D3DRENDERSTATE_FOGCOLOR, RGB_MAKE ( d3d_fog_colour.r, d3d_fog_colour.g, d3d_fog_colour.b ) );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_fog_face_intensity ( int value )
{

	d3d_fog_intensity = RGBA_MAKE ( 0, 0, 0, value );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void suspend_d3d_fog ( void )
{

	set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reinstate_d3d_fog ( void )
{

	if ( d3d_fog_enabled )
	{

		set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, TRUE );

		set_d3d_int_state ( D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_NONE );
		set_d3d_int_state ( D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_NONE );

	//	set_d3d_float_state ( D3DRENDERSTATE_FOGSTART, d3d_fog_start );
	//	set_d3d_float_state ( D3DRENDERSTATE_FOGEND, d3d_fog_end );

		set_d3d_int_state ( D3DRENDERSTATE_FOGCOLOR, RGB_MAKE ( d3d_fog_colour.r, d3d_fog_colour.g, d3d_fog_colour.b ) );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
