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

#ifdef WIN32
#ifdef __WATCOMC__

void asm_convert_float_to_int ( float value, int *ptr );

#pragma aux asm_convert_float_to_int =	\
	"fistp	dword ptr [ edi ]"			\
parm [8087] [edi];


void asm_convert_double_to_int ( double value, int *ptr );

#pragma aux asm_convert_double_to_int =\
	"fistp	dword ptr [ edi ]"			\
parm [8087] [edi];

#elif defined ( __GNUC__ )

inline static void asm_convert_float_to_int ( float value, int *integer ) __attribute__((always_inline));
inline static void asm_convert_float_to_int ( float value, int *integer )
{
  __asm__ __volatile__ ("fistp (%1);"
						: /* no outputs */ : "t" (value), "d" (integer) : "memory" );
}

inline static void asm_convert_double_to_int ( double value, int *integer ) __attribute__((always_inline));
inline static void asm_convert_double_to_int ( double value, int *integer )
{
  __asm__ __volatile__ ("fistp (%1);"
						: /* no outputs */ : "t" (value), "d" (integer) : "memory" );
}

#else

__inline void asm_convert_float_to_int ( float value, int *integer )
{

	__asm
	{

		fld value
		mov edx, integer
		fistp dword ptr [edx]
	}
}

__inline void asm_convert_double_to_int ( double value, int *integer )
{

	__asm
	{

		fld value
		mov edx, integer
		fistp dword ptr [edx]
	}
}

#endif
#else

/* Linux ASM portage by Colin Bayer <vogon@icculus.org> */

__inline void asm_convert_float_to_int ( float value, int *integer )
{
  __asm__ __volatile__ ("fistp (%1);"
						: /* no outputs */ : "t" (value), "d" (integer) : "memory" );
}

__inline void asm_convert_double_to_int ( double value, int *integer )
{
  __asm__ __volatile__ ("fistp (%1);"
						: /* no outputs */ : "t" (value), "d" (integer) : "memory" );
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void convert_float_to_int ( float value, int *ptr );

extern void convert_double_to_int ( double value, int *ptr );

extern void report_fpu_exceptions ( void );

extern unsigned short int get_fpu_control_word_value ( void );

extern void set_fpu_mode_default ( void );

extern void set_fpu_exceptions ( void );

extern void set_fpu_rounding_mode_nearest ( void );

extern void set_fpu_rounding_mode_up ( void );

extern void set_fpu_rounding_mode_down ( void );

extern void set_fpu_rounding_mode_zero ( void );

extern void set_fpu_precision_mode_single ( void );

extern void set_fpu_precision_mode_double ( void );

extern void set_fpu_precision_mode_extended ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

