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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// convert altitude (feet) to air density
//

static float air_density_table[] =
{
	1.000,	//	     0
	0.985,	//	 1,000
	0.971,	//	 2,000
	0.957,	//	 3,000
	0.942,	//	 4,000
	0.928,	//	 5,000
	0.914,	//	 6,000
	0.900,	//	 7,000
	0.887,	//	 8,000
	0.873,	//	 9,000
	0.859,	//	10,000
	0.846,	//	11,000
	0.833,	//	12,000
	0.819,	//	13,000
	0.806,	//	14,000
	0.793,	//	15,000
	0.780,	//	16,000
	0.768,	//	17,000
	0.755,	//	18,000
	0.742,	//	19,000
	0.730,	//	20,000
	0.718,	//	21,000
	0.705,	//	22,000
	0.693,	//	23,000
	0.681,	//	24,000
	0.669,	//	25,000
	0.653,	//	26,000
	0.646,	//	27,000
	0.635,	//	28,000
	0.623,	//	29,000
	0.612,	//	30,000
	0.601,	//	31,000
	0.589,	//	32,000
	0.578,	//	33,000
	0.568,	//	34,000
	0.557,	//	35,000
	0.546,	//	36,000
	0.533,	//	37,000
	0.521,	//	38,000
	0.508,	//	39,000
	0.496,	//	40,000
	0.485,	//	41,000
	0.473,	//	42,000
	0.462,	//	43,000
	0.451,	//	44,000
	0.440,	//	45,000
	0.430,	//	46,000
	0.419,	//	47,000
	0.409,	//	48,000
	0.400,	//	49,000
	0.390,	//	50,000
	0.381,	//	51,000
	0.372,	//	52,000
	0.363,	//	53,000
	0.354,	//	54,000
	0.346,	//	55,000
	0.337,	//	56,000
	0.329,	//	57,000
	0.322,	//	58,000
	0.314,	//	59,000
	0.307,	//	60,000
	0.299,	//	61,000
	0.292,	//	62,000
	0.285,	//	63,000
	0.278,	//	64,000
	0.272,	//	65,000
	0.265,	//	66,000
	0.259,	//	67,000
	0.252,	//	68,000
	0.246,	//	69,000
	0.241		//	70,000
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SIMPLIFIED HELICOPTERS FORMULA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_air_density (float altitude)
{
	int
		index;

	float
		mod,
		air_density;

	altitude = feet (altitude);

	altitude = bound (altitude, 0.0, 69999.0);

	index = (int) (altitude / 1000.0);

	mod = fmod (altitude, 1000.0f);

	air_density = air_density_table[index + 1] - air_density_table[index];

	air_density *= mod;

	air_density *= 0.001;

	air_density += air_density_table[index];
	
	return air_density;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PRECISE BALLISTICS FORMULA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_precise_air_density (float altitude)
{
	float
		m = 0.0289644, // physics constants
		r = 8.31447,
		l = 0.0065,
		p0 = 101325, // standard air pressure, Pa
		t0 = 288.15, // standard temperature, K
		t = t0 - l * altitude, // actual temperature, K
		p = p0 * exp(- (G * m * altitude) / (r * t0)), // air pressure, Pa
		air_density = p * m / (r * t); // kg/m^3
	
	return air_density;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float convert_true_airspeed_to_indicated_airspeed (float true_airspeed, float altitude)
{
	float
		air_density,
		indicated_airspeed;

	air_density = get_air_density (altitude);

	indicated_airspeed = true_airspeed * air_density;

	return (indicated_airspeed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float convert_indicated_airspeed_to_true_airspeed (float indicated_airspeed, float altitude)
{
	float
		air_density,
		true_airspeed;

	air_density = get_air_density (altitude);

	true_airspeed = indicated_airspeed / air_density;

	return (true_airspeed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
