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
//
// NOTES:	If you call one macro from another macro, the compiler will not fully optimise the expression.
//
// 			Each time a macro is expanded (evaluated to a constant), the constant is stored locally.
//				This is faster than having a single 'extern const' value. Probably due to caching.
//
//				Brackets around constant sub-expressions helps the compiler produce better code.
//
//				For instance:
//
//					#define deg(RAD) ((RAD) * (180.0 / PI))
//
//				Produces better code than:
//
//					#define deg(RAD) ((RAD) * 180.0 / PI)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// IMPLICIT PARAMETERS (deg to rad and rad to deg conversion)
//

#define deg(RAD) ((RAD) * (180.0f / PI))

#define rad(DEG) ((DEG) * (PI / 180.0f))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// IMPLICIT PARAMETERS (distance units in metres, time units in seconds)
//

#define feet(METRES) ((METRES) * ONE_OVER_ONE_FOOT)

#define miles(METRES) ((METRES) * ONE_OVER_ONE_MILE)

#define feet_per_minute(METRES_PER_SECOND) ((METRES_PER_SECOND) * (60.0f / ONE_FOOT))

#define miles_per_hour(METRES_PER_SECOND) ((METRES_PER_SECOND) * ((60.0f * 60.0f) / ONE_MILE))

#define metres_per_minute(METRES_PER_SECOND) ((METRES_PER_SECOND) * 60.0f)

#define kilometres_per_hour(METRES_PER_SECOND) ((METRES_PER_SECOND) * ((60.0f * 60.0f) / KILOMETRE))

#define nautical_miles(METRES) ((METRES) * ONE_OVER_ONE_NAUTICAL_MILE)

#define knots(METRES_PER_SECOND) ((METRES_PER_SECOND) * ((60.0f * 60.0f) / ONE_NAUTICAL_MILE))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// EXPLICIT PARAMETERS
//

#define metres_per_second_to_knots(METRES_PER_SECOND) (((METRES_PER_SECOND) * (60.0f * 60.0f)) / ONE_NAUTICAL_MILE)

#define knots_to_metres_per_second(KNOTS) ((KNOTS) * (ONE_NAUTICAL_MILE / (60.0f * 60.0f)))

#define kilometres_per_hour_to_metres_per_second(KPH) (((KPH) * 1000.0f) / (60.0f * 60.0f))

#define kilograms_to_pounds(KG) ((KG) * 2.205f)

#define pounds_to_kilograms(LBS) ((LBS) * 0.4535)

#define feet_to_metres(FEET) ((FEET) * ONE_FOOT)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
