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

const crater_data
	crater_database[NUM_CRATER_TYPES] =
	{
		////////////////////////////////////////
		//
		// CRATER_TYPE_NONE
		//
		////////////////////////////////////////
		{
			OBJECT_3D_INVALID_OBJECT_INDEX,			// object 3d shape

			0.0,												// min scale
			0.0,												// max scale
	
			0.0,												// lifetime
		},

		////////////////////////////////////////
		//
		// CRATER_TYPE_SMALL_AP_SHELL
		//
		////////////////////////////////////////
		{
			OBJECT_3D_EFFECT_CRATER,					// object 3d shape

			1.0,												// min scale
			2.0,												// max scale
	
			20.0,												// lifetime
		},

		////////////////////////////////////////
		//
		// CRATER_TYPE_LARGE_AP_SHELL
		//
		////////////////////////////////////////
		{
			OBJECT_3D_CRATER_ROUND,						// object 3d shape

			10.0,												// min scale
			20.0,												// max scale
	
			200.0,											// lifetime
		},

		////////////////////////////////////////
		//
		// CRATER_TYPE_SMALL_EXPLOSION
		//
		////////////////////////////////////////
		{
			OBJECT_3D_CRATER_ROUND,					// object 3d shape

			1.0,												// min scale
			6.0,												// max scale
	
			200.0,											// lifetime
		},

		////////////////////////////////////////
		//
		// CRATER_TYPE_MEDIUM_EXPLOSION
		//
		////////////////////////////////////////
		{
			OBJECT_3D_CRATER_ROUND,						// object 3d shape

			4.0,												// min scale
			10.0,												// max scale
	
			400.0,											// lifetime
		},

		////////////////////////////////////////
		//
		// CRATER_TYPE_LARGE_EXPLOSION
		//
		////////////////////////////////////////
		{
			OBJECT_3D_CRATER_ROUND,						// object 3d shape

			8.0,												// min scale
			16.0,												// max scale
	
			510.0,											// lifetime
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

