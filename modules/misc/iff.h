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

enum IFF_HEADER_TYPES
{

	NOT_RECOGNISED,
	FORM,
	LWOB,					// Lightwave object
	PNTS,					// Points
	SRFS,					// Surfaces
	POLS,					// Polygons
	SURF,					// Surface description
	COLR,					// Colour
	DIFF,					// Diffuse level
	SMAN,					// Smoothing angle
	FLAG,					// Surface flags
	TFLG,					// Texture Flags
	TSIZ,					// Texture size
	TIMG,					// Texture image
	TCTR,					// Texture centre
	TWRP,					// Texture wrapping
	TFP0,					// Texture float parameter 0
	TFP1,					// Texture float parameter 1
	CTEX,					// Colour Texture
	ILBM,					// Interleaved bitmap
	PBM,					// Packed Byte Mode
	BMHD,					// Bitmap header
	CMAP,					// Colour map
	BODY,					// The main data body
	VDIF,					// Floating point diffuse setting
	TRAN,					// Transparency value
	TREF,					// Texture reference object name
	TAAS,					// Texture anti-aliasing strength
	LUMI,					// Luminosity setting
	IMSQ,					// Image sequence settings
	REFL,					// Reflectivity setting
	EDGE,					// Edge transparency
	DTEX,					// Diffuse texture
	STEX,					// Specular texture
	RTEX,					// Reflection texture
	TTEX,					// Transparency texture
	LTEX,					// Luminosity texture
	BTEX,					// Bumpmap texture
	VSPC,					// Specular level
};

typedef enum IFF_HEADER_TYPES iff_header_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct	IFF_HEADER
{

	char
		*name;

	iff_header_types
		id;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern iff_header_types get_iff_type ( FILE *fp );

extern iff_header_types get_iff_type_from_string ( char *buf );

extern void put_iff_type ( FILE *fp, iff_header_types type );

extern float iff_float_read ( FILE *fp );

extern int iff_int_read ( FILE *fp );

extern short int iff_short_int_read ( FILE *fp );

extern void iff_float_write ( float value, FILE *fp );

extern void iff_int_write ( int value, FILE *fp );

extern void iff_short_int_write ( short int value, FILE *fp );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

