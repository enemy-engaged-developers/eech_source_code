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
// Parameters of the IEEE float number
//

// Number of mantissa bits for lookup
#define	LOOKUP_BITS		8

// Position of the exponent
#define EXP_POS       23

// Bias of the exponent
#define EXP_BIAS     127

//
// The mantissa is assumed to be just down from the exponent
//

//
// Derive other constants
//

// Position of mantissa lookup
#define LOOKUP_POS   (EXP_POS-LOOKUP_BITS)

// Position of mantissa seed
#define SEED_POS     (EXP_POS-8)

// Number of entries in table
#define TABLE_SIZE   (2 << LOOKUP_BITS)

// Mask for table input
#define LOOKUP_MASK  (TABLE_SIZE - 1)

// Extract exponent
#define GET_EXP(a)   (((a) >> EXP_POS) & 0xFF)

// Set exponent
#define SET_EXP(a)   ((a) << EXP_POS)

// Extended mantissa MSB's
#define GET_EMANT(a) (((a) >> LOOKUP_POS) & LOOKUP_MASK)

// Set mantissa 8 MSB's
#define SET_MANTSEED(a) (((unsigned long)(a)) << SEED_POS)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

union FLOAT_AND_INT
{

	unsigned int
		i;

	float
		f;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned int *inverse_sqrt_table;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_inverse_square_root_table ( void );

extern float get_inverse_square_root ( float x );

extern float get_medium_accurary_inverse_square_root ( float x );

extern float get_low_accurary_inverse_square_root ( float x );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Quick execution macros for the two fast routines
//

#define get_inverse_square_root_macro(VALUE,RESULT)											\
			{ 																									\
				unsigned int a;																			\
				float	r;																						\
				union FLOAT_AND_INT seed;																\
																												\
				a = ( ( union FLOAT_AND_INT * ) ( &VALUE ) )->i;								\
				seed.i = SET_EXP ( ( ( ( 3*EXP_BIAS ) - 1 ) - GET_EXP ( a ) ) >> 1 );	\
				seed.i |= SET_MANTSEED ( inverse_sqrt_table[ GET_EMANT ( a ) ] );			\
				r = seed.f;																					\
				r = ( 3.0 - r * r * VALUE ) * r * 0.5;												\
				RESULT = ( 3.0 - r * r * VALUE ) * r * 0.5;										\
			}

#define get_medium_accurary_inverse_square_root_macro(VALUE,RESULT)						\
			{ 																									\
				unsigned int a;																			\
				float	r;																						\
				union FLOAT_AND_INT seed;																\
																												\
				a = ( ( union FLOAT_AND_INT * ) ( &VALUE ) )->i;								\
				seed.i = SET_EXP ( ( ( ( 3*EXP_BIAS ) - 1 ) - GET_EXP ( a ) ) >> 1 );	\
				seed.i |= SET_MANTSEED ( inverse_sqrt_table[ GET_EMANT ( a ) ] );			\
				r = seed.f;																					\
				RESULT = ( 3.0 - r * r * VALUE ) * r * 0.5;										\
			}

#define get_low_accurary_inverse_square_root_macro(VALUE,RESULT)							\
			{																									\
				unsigned int a;																			\
				union FLOAT_AND_INT seed;																\
																												\
				a = ( ( union FLOAT_AND_INT * ) ( &VALUE ) )->i;								\
				seed.i = SET_EXP ( ( ( ( 3*EXP_BIAS ) - 1 ) - GET_EXP ( a ) ) >> 1 );	\
				seed.i |= SET_MANTSEED ( inverse_sqrt_table[ GET_EMANT ( a ) ] );			\
				RESULT = seed.f;																			\
			}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

