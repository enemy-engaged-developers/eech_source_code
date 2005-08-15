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

enum
{

	CLIP_LEFT_BIT,
	CLIP_TOP_BIT,
	CLIP_RIGHT_BIT,
	CLIP_BOTTOM_BIT,
	CLIP_YONDER_BIT,
	CLIP_HITHER_BIT,
};

#define CLIP_LEFT ( 1<<CLIP_LEFT_BIT )
#define CLIP_TOP ( 1<<CLIP_TOP_BIT )
#define CLIP_RIGHT ( 1<<CLIP_RIGHT_BIT )
#define CLIP_BOTTOM ( 1<<CLIP_BOTTOM_BIT )
#define CLIP_YONDER ( 1<<CLIP_YONDER_BIT )
#define CLIP_HITHER ( 1<<CLIP_HITHER_BIT )
#define CLIP_ALL ( CLIP_LEFT | CLIP_TOP | CLIP_RIGHT | CLIP_BOTTOM | CLIP_YONDER | CLIP_HITHER )

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// DONT TOUCH THIS STRUCTURE
//

struct VIEWPORT
{

	float
		x_min,
		y_min,
		x_max,
		y_max;
};

typedef struct VIEWPORT viewport;

//
// CHANGING ANYTHING HERE WILL AFFECT THE PRAGMA BELOW
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct INT_VIEWPORT
{
	int
		x_min,
		y_min,
		x_max,
		y_max;
};

typedef struct INT_VIEWPORT int_viewport;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern viewport
	active_viewport;

extern int_viewport
	active_int_viewport;

extern int
	left_clip_bit_array[],
	right_clip_bit_array[],
	top_clip_bit_array[],
	bottom_clip_bit_array[];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_viewport ( float x_min, float y_min, float x_max, float y_max );

extern void set_basic_viewport ( float x_min, float y_min, float x_max, float y_max );

extern void set_full_viewport ( float x_min, float y_min, float x_max, float y_max, float z_min, float z_max );

extern void clear_viewport ( const struct REAL_COLOUR colour );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __WATCOMC__

extern int generate_lookup_outcode ( int xmin, int ymin, int xmax, int ymax );

#pragma aux generate_lookup_outcode =							\
	"shr	eax, 31"														\
	"and	ebx, 0x80000000"											\
	"shr	ecx, 29"														\
	"and	edx, 0x80000000"											\
	"shr	ebx, 30"														\
	"and	eax, 0x00000001"											\
	"shr	edx, 28"														\
	"and	ecx, 0x00000004"											\
	"or	eax, ebx"													\
	"or	ecx, edx"													\
	"or	eax, ecx"													\
parm [ eax ] [ ebx ] [ ecx ] [ edx ]							\
value no8087 [ eax ]															\
modify exact [ eax ebx ecx edx ];

#elif defined ( __GNUC__ )

__inline int generate_lookup_outcode ( int xmin, int ymin, int xmax, int ymax )
{
	xmin >>= 31;
	ymin &= 0x80000000;
	xmax >>= 29;
	ymax &= 0x80000000;
	ymin >>= 30;
	xmin &= 0x00000001;
	ymax >>= 28;
	xmax &= 0x00000004;
	xmin |= ymin;
	xmax |= ymax;
	xmin |= xmax;

	return xmin;
}

#else

__inline int generate_lookup_outcode ( int xmin, int ymin, int xmax, int ymax )
{

	__asm mov eax, xmin;
	__asm mov ebx, ymin;
	__asm mov ecx, xmax;
	__asm mov edx, ymax;
	__asm shr	eax, 31;
	__asm and	ebx, 0x80000000;
	__asm shr	ecx, 29;
	__asm and	edx, 0x80000000;
	__asm shr	ebx, 30;
	__asm and	eax, 0x00000001;
	__asm shr	edx, 28;
	__asm and	ecx, 0x00000004;
	__asm or	eax, ebx;
	__asm or	ecx, edx;
	__asm or	eax, ecx;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __WATCOMC__

extern int generate_old_lookup_outcode ( int xmin, int ymin, int xmax, int ymax );

#pragma aux generate_old_lookup_outcode =							\
	"sar	eax, 31"														\
	"sar	ebx, 31"														\
	"mov	eax, left_clip_bit_array [ eax * 4 + 4 ]"			\
	"sar	ecx, 31"														\
	"or	eax, top_clip_bit_array [ ebx * 4 + 4 ]"			\
	"sar	edx, 31"														\
	"or	eax, right_clip_bit_array [ ecx * 4 + 4 ]"		\
	"mov	edx, bottom_clip_bit_array [ edx * 4 + 4 ]"		\
	"or	eax, edx"													\
parm [ eax ] [ ebx ] [ ecx ] [ edx ]							\
value no8087 [ eax ]															\
modify exact [ eax ebx ecx edx ];

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
