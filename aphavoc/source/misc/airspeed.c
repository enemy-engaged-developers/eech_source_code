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
	1.000f,	//	     0
	0.985f,	//	 1,000
	0.971f,	//	 2,000
	0.957f,	//	 3,000
	0.942f,	//	 4,000
	0.928f,	//	 5,000
	0.914f,	//	 6,000
	0.900f,	//	 7,000
	0.887f,	//	 8,000
	0.873f,	//	 9,000
	0.859f,	//	10,000
	0.846f,	//	11,000
	0.833f,	//	12,000
	0.819f,	//	13,000
	0.806f,	//	14,000
	0.793f,	//	15,000
	0.780f,	//	16,000
	0.768f,	//	17,000
	0.755f,	//	18,000
	0.742f,	//	19,000
	0.730f,	//	20,000
	0.718f,	//	21,000
	0.705f,	//	22,000
	0.693f,	//	23,000
	0.681f,	//	24,000
	0.669f,	//	25,000
	0.653f,	//	26,000
	0.646f,	//	27,000
	0.635f,	//	28,000
	0.623f,	//	29,000
	0.612f,	//	30,000
	0.601f,	//	31,000
	0.589f,	//	32,000
	0.578f,	//	33,000
	0.568f,	//	34,000
	0.557f,	//	35,000
	0.546f,	//	36,000
	0.533f,	//	37,000
	0.521f,	//	38,000
	0.508f,	//	39,000
	0.496f,	//	40,000
	0.485f,	//	41,000
	0.473f,	//	42,000
	0.462f,	//	43,000
	0.451f,	//	44,000
	0.440f,	//	45,000
	0.430f,	//	46,000
	0.419f,	//	47,000
	0.409f,	//	48,000
	0.400f,	//	49,000
	0.390f,	//	50,000
	0.381f,	//	51,000
	0.372f,	//	52,000
	0.363f,	//	53,000
	0.354f,	//	54,000
	0.346f,	//	55,000
	0.337f,	//	56,000
	0.329f,	//	57,000
	0.322f,	//	58,000
	0.314f,	//	59,000
	0.307f,	//	60,000
	0.299f,	//	61,000
	0.292f,	//	62,000
	0.285f,	//	63,000
	0.278f,	//	64,000
	0.272f,	//	65,000
	0.265f,	//	66,000
	0.259f,	//	67,000
	0.252f,	//	68,000
	0.246f,	//	69,000
	0.241f		//	70,000
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	air_density *= 0.001f;

	air_density += air_density_table[index];

	return (air_density);
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
