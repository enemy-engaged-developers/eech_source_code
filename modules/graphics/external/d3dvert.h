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
// If we need to artificially elevate polygons ( ZBias ), use this constant
//

#define POLYGON_ZDISTANCE_ELEVATED_BIAS ( 1.0 - 8.0 / 65535.0 )

//
// If we need
//

#define POLYGON_ZDISTANCE_SHADOW_ELEVATED_BIAS ( 1.0 - 6.0 / 65535.0 )

//
// Sometimes we don't need that much bias, so a minimal bias is required
//

#define POLYGON_ZDISTANCE_MINIMAL_ELEVATED_BIAS ( 1.0 - 1.0 / 65535.0 )

//
// Otherwise, the default bias is:
//

#define POLYGON_ZDISTANCE_NORMAL_BIAS ( 1.0 - 0.0 )

//
// Sometimes we need to artificially lower polygons:
//

#define POLYGON_ZDISTANCE_LOWERED_BIAS ( 1.0 - -4.0 / 65535.0 )

//
// Again, sometimes we don't need to lower by that much, so minimal bias:
//

#define POLYGON_ZDISTANCE_MINIMAL_LOWERED_BIAS ( 1.0 - -0.0 / 65535.0 )

//
// Farthest distance value in the Z buffer
//

#define POLYGON_ZDISTANCE_FARTHEST ( 1.0 )

//
// Nearest distance value in the Z buffer
//

#define POLYGON_ZDISTANCE_NEAREST ( 0.0 )

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

