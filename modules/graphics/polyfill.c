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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	lhs_x[MAX_SCREEN_HEIGHT],
	rhs_x[MAX_SCREEN_HEIGHT];

float
	lhs_i[MAX_SCREEN_HEIGHT],
	rhs_i[MAX_SCREEN_HEIGHT],

	lhs_u[MAX_SCREEN_HEIGHT],
	lhs_v[MAX_SCREEN_HEIGHT],
	lhs_uz[MAX_SCREEN_HEIGHT],
	lhs_vz[MAX_SCREEN_HEIGHT],
	lhs_q[MAX_SCREEN_HEIGHT],
	
	rhs_u[MAX_SCREEN_HEIGHT],
	rhs_v[MAX_SCREEN_HEIGHT],
	rhs_uz[MAX_SCREEN_HEIGHT],
	rhs_vz[MAX_SCREEN_HEIGHT],
	rhs_q[MAX_SCREEN_HEIGHT];

int
	y_min,									// Minimum y coordinate for filling from
	y_max;									// Maximum y coordinate for filling to

static unsigned int
	iufraction,
	ivfraction,
	idufraction,
	idvfraction,
	*shading_table;


static int
	idu,
	idv,
	idintensity,
	uvstepvcarry[2];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

texture_map
	*default_texture;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void solid_fill_horizontal_line ( unsigned short int *ptr, int colour, int count );


#pragma aux solid_fill_horizontal_line =	\
	"test edi, 2"									\
	"jne	noleadin"								\
	"dec	edx"										\
	"mov	[ edi ], cx"							\
	"add	edi, 2"									\
"noleadin:"											\
	"cmp	edx, 8"									\
	"jl	leadout"									\
"innerloop:"										\
	"mov	[ edi + 0 ], ecx"					\
	"mov	[ edi + 4 ], ecx"						\
	"mov	[ edi + 8 ], ecx"						\
	"mov	[ edi + 12 ], ecx"						\
	"add	edi, 16"									\
	"sub	edx, 8"									\
	"cmp	edx, 8"									\
	"jge	innerloop"								\
"leadout:"											\
	"cmp	edx, 6"									\
	"jl	leadout4"								\
	"mov	[ edi ], ecx"							\
	"mov	[ edi + 4 ], ecx"						\
	"mov	[ edi + 8 ], ecx"						\
	"add	edi, 12"									\
	"sub	edx, 6"									\
"leadout4:"											\
	"cmp	edx, 4"									\
	"jl	leadout2"								\
	"mov	[ edi ], ecx"							\
	"mov	[ edi + 4 ], ecx"						\
	"add	edi, 8"									\
	"sub	edx, 4"									\
"leadout2:"											\
	"cmp	edx, 2"									\
	"jl	leadout0"								\
	"mov	[ edi ], ecx"							\
	"add	edi, 4"									\
	"sub	edx, 2"									\
"leadout0:"											\
	"test	edx, edx"								\
	"jl	endprag"									\
	"mov	[ edi ], cx"							\
"endprag:"											\
parm [ edi ] [ ecx ]	[ edx ]					\
modify exact [ eax ebx ecx edx edi ];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void preread_4lines ( unsigned char *ptr );

#pragma aux preread_4lines =					\
	"mov	eax, [ esi ]"							\
	"mov	ebx, [ esi + 36 ]"					\
	"mov	eax, [ esi + 64 ]"					\
	"mov	ebx, [ esi + 100 ]"					\
parm [ esi ]										\
modify exact [ eax ebx esi ];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_plain_polygon ( unsigned int colour )
{

	int
		y,
		x1,
		x2,
		pitch,
		temp;

	unsigned char
		*ptr;

	unsigned short int
		*dst;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	ptr = get_screen_data ( active_screen );

	pitch = get_screen_pitch ( active_screen );

	ptr += y_min * pitch;

	for ( y=y_min; y<=y_max; y++ )
	{

		int
			x = 0;

		x1 = lhs_x[y];

		x2 = rhs_x[y];

		if ( x1 > x2 )
		{

			temp = x2;

			x2 = x1;

			x1 = temp;
		}

		dst = ( unsigned short int * ) ( ptr + ( x1 * 2 ) );

		x = x2 - x1;
/*
		if ( ( int ) dst & 0x2 )
		{

			*dst++ = colour;

			x--;
		}

		//
		// dst is guaranteed dword aligned now, x could be -1 or more.
		//

		while ( x >= 0 )
		{

			if ( x >= 15 )
			{

				*( ( unsigned int * ) dst + 0 ) = colour;
				*( ( unsigned int * ) dst + 1 ) = colour;
				*( ( unsigned int * ) dst + 2 ) = colour;
				*( ( unsigned int * ) dst + 3 ) = colour;
				*( ( unsigned int * ) dst + 4 ) = colour;
				*( ( unsigned int * ) dst + 5 ) = colour;
				*( ( unsigned int * ) dst + 6 ) = colour;
				*( ( unsigned int * ) dst + 7 ) = colour;

				x -= 16;
				dst += 16;
			}
//			else if ( x >= 7 )
//			{
//
//				*( ( unsigned int * ) dst + 0 ) = colour;
//				*( ( unsigned int * ) dst + 1 ) = colour;
//				*( ( unsigned int * ) dst + 2 ) = colour;
//				*( ( unsigned int * ) dst + 3 ) = colour;
//
//				x -= 8;
//				dst += 8;
//			}
			else if ( x >= 4 )
			{

				*( ( unsigned int * ) dst + 0 ) = colour;
				*( ( unsigned int * ) dst + 1 ) = colour;

				x -= 4;
				dst += 4;
			}
			else
			{

				*dst++ = colour;
				x -= 1;
			}
		}
		*/

		if ( ( x2 < 0 ) || ( x2 > 639 ) || ( x1 < 0 ) || ( x1 > 639 ) || ( x < 0 ) || ( x > 640 ) )
		{

                        debug_log ( "CLIP!" );
		}

		solid_fill_horizontal_line ( dst, colour, x );
	
//		for ( ; x>=0; x-- )
//		{
//
//			*dst++ = colour;
//		}
//
		ptr += pitch;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_zbuffer_plain_polygon ( unsigned int colour )
{

	int
		y,
		x1,
		x2,
		pitch;

	unsigned char
		*ptr;

//	unsigned short int
//		*dst;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	ptr = get_screen_data ( active_screen );

	pitch = get_screen_pitch ( active_screen );

	ptr += y_min * pitch;

	for ( y=y_min; y<=y_max; y++ )
	{

		float
			q1,
			q2;
//			dq;

//		float
//			*zbuffer_line;

		x1 = lhs_x[y];

		x2 = rhs_x[y];

		q1 = lhs_q[y];

		q2 = rhs_q[y];

		if ( x1 > x2 )
		{

			int
				itemp;

			float
				ftemp;

			itemp = x2;

			x2 = x1;

			x1 = itemp;

			ftemp = q2;

			q2 = q1;

			q1 = ftemp;
		}

//		construct_zbuffer_bitmask_instructions ( x1, x2, y, q1, q2 );
		construct_zbuffer_rle_instructions ( x1, x2, y, q1, q2 );
/*		if ( construct_zbuffer_bitmask_instructions ( x1, x2, y, q1, q2 ) )
		{

			char
				*bitmask_instructions,
				mask,
				bitmask;

			int
				length;

			dst = ( unsigned short int * ) ( ptr + ( x1 * 2 ) );

			bitmask_instructions = zbuffer_bitmask_instructions;

			length = x2 - x1 + 1;

			length >>= 3;

			length++;

			while ( length )
			{

				bitmask = *bitmask_instructions++;

				switch ( ( bitmask >> 4 ) & 0xf )
				{

					case 0x0:	break;
					case 0x1:	dst[3] = colour; break;
					case 0x2:	dst[2] = colour; break;
					case 0x3:	dst[3] = colour; dst[2] = colour; break;
					case 0x4:	dst[1] = colour; break;
					case 0x5:	dst[1] = colour; dst[3] = colour; break;
					case 0x6:	dst[1] = colour; dst[2] = colour; break;
					case 0x7:	dst[1] = colour; dst[2] = colour; dst[3] = colour; break;
					case 0x8:	dst[0] = colour; break;
					case 0x9:	dst[0] = colour; dst[3] = colour; break;
					case 0xa:	dst[0] = colour; dst[2] = colour; break;
					case 0xb:	dst[0] = colour; dst[3] = colour; dst[2] = colour; break;
					case 0xc:	dst[0] = colour; dst[1] = colour; break;
					case 0xd:	dst[0] = colour; dst[1] = colour; dst[3] = colour; break;
					case 0xe:	dst[0] = colour; dst[1] = colour; dst[2] = colour; break;
					case 0xf:	dst[0] = colour; dst[1] = colour; dst[2] = colour; dst[3] = colour; break;
				}

				switch ( bitmask & 0xf )
				{

					case 0x0:	break;
					case 0x1:	dst[7] = colour; break;
					case 0x2:	dst[6] = colour; break;
					case 0x3:	dst[7] = colour; dst[6] = colour; break;
					case 0x4:	dst[5] = colour; break;
					case 0x5:	dst[5] = colour; dst[7] = colour; break;
					case 0x6:	dst[5] = colour; dst[6] = colour; break;
					case 0x7:	dst[5] = colour; dst[6] = colour; dst[7] = colour; break;
					case 0x8:	dst[4] = colour; break;
					case 0x9:	dst[4] = colour; dst[7] = colour; break;
					case 0xa:	dst[4] = colour; dst[6] = colour; break;
					case 0xb:	dst[4] = colour; dst[7] = colour; dst[6] = colour; break;
					case 0xc:	dst[4] = colour; dst[5] = colour; break;
					case 0xd:	dst[4] = colour; dst[5] = colour; dst[7] = colour; break;
					case 0xe:	dst[4] = colour; dst[5] = colour; dst[6] = colour; break;
					case 0xf:	dst[4] = colour; dst[5] = colour; dst[6] = colour; dst[7] = colour; break;
				}

				length--;

				dst += 8;
			}
		}
		*/

		ptr += pitch;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gouraud_fill_horizontal_line ( unsigned short int *ptr, unsigned int *table, int count, int intensity, int dintensity );

#pragma aux gouraud_fill_horizontal_line =	\
	"push	ebp"											\
	"push	ebx"											\
	"test	edi, 2"										\
	"je	loop2start"									\
	"mov	edx, eax"									\
	"add	eax, [ esp ]"								\
	"shr	edx, 0x10"									\
	"sub	ecx, 1"										\
	"mov	edx, [ esi + edx * 4 ]"					\
	"mov	[ edi ], dx"								\
	"add	edi, 2"										\
"loop2start:"											\
	"mov	ebp, ecx"									\
	"shr	ecx, 1"										\
	"test	ecx, ecx"									\
	"je	loopout"										\
"loop2:"													\
	"mov	edx, eax"									\
	"add	eax, [ esp ]"								\
	"shr	edx, 0x10"									\
	"mov	ebx, eax"									\
	"shr	ebx, 0x10"									\
	"mov	edx, [ esi + edx * 4 ]"					\
	"mov	ebx, [ esi + ebx * 4 ]"					\
	"add	eax, [ esp ]"								\
	"add	edi, 4"										\
	"and	edx, 0x0000FFFF"							\
	"and	ebx, 0xFFFF0000"							\
	"or	edx, ebx"									\
	"mov	[ edi - 4], edx"							\
	"sub	ecx, 1"										\
	"jg	loop2"										\
"loopout:"												\
	"test	ebp, 1"										\
	"je	loopend"										\
	"mov	edx, eax"									\
	"shr	edx, 0x10"									\
	"mov	edx, [ esi + edx * 4 ]"					\
	"mov	[ edi ], dx"								\
"loopend:"												\
	"pop	ebx"											\
	"pop	ebp"											\
parm [ edi ] [ esi ]	[ ecx ] [ eax ] [ ebx ]	\
modify exact [ eax ebx ecx edx edi esi ];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_gouraud_polygon ( int colour )
{

	int
		y,
		x1,
		x2,
		pitch,
		length,
		itmp,
		int1,
		int2,
		dintensity;

	unsigned short int
		*dst;

	unsigned char
		*ptr;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	ptr = get_screen_data ( active_screen );

	pitch = get_screen_pitch ( active_screen );

	ptr += y_min * pitch;

	for ( y = y_min; y < y_max; y++ )
	{

		x1 = lhs_x[y];

		x2 = rhs_x[y];

		convert_float_to_int ( ( lhs_i[y] * 32 * 65535 ), &int1 );

		convert_float_to_int ( ( rhs_i[y] * 32 * 65535 ), &int2 );

		int1 = bound ( int1, 0, ( 32 * 65535 ) );

		int2 = bound ( int2, 0, ( 32 * 65335 ) );

		if ( x1 > x2 )
		{

			itmp = x2; x2 = x1; x1 = itmp;

			itmp = int2; int2 = int1; int1 = itmp;
		}

		dst = ( unsigned short int * ) ( ptr + ( x1 * 2 ) );

		length = x2 - x1 + 1;

		dintensity = ( int2 - int1 ) / length;

		gouraud_fill_horizontal_line ( dst, application_shading_table[colour], length, int1, dintensity );
	/*
		while ( x1 <= x2 )
		{

			*dst++ = application_shading_table[colour][( int1 >> 16 )];

			int1 += dintensity;

			x1 ++;
		}
		*/

		ptr += pitch;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fill_flat_shaded_textured_horizontal_line ( unsigned char *ptr, unsigned short int *screen, int length, unsigned int iufraction, unsigned int ivfraction );

#pragma aux fill_flat_shaded_textured_horizontal_line =	\
	"push	ebp"															\
	"xor	edx, edx"													\
"loop1:"																	\
	"mov	dl, [ esi ]"												\
	"mov	ebp, dword ptr shading_table"							\
	"add	ebx, idvfraction"											\
	"lea	edx, [ edx * 4 + ebp ]"									\
	"sbb	ebp, ebp"													\
	"lea	edi, [ edi + 2 ]"											\
	"mov	edx, dword ptr [edx]"									\
	"add	eax, idufraction"											\
	"adc	esi, [ uvstepvcarry + ebp*4 + 4 ]"					\
	"mov	[ edi - 2 ], dx"											\
	"xor	edx, edx"													\
	"dec	ecx"															\
	"jge	loop1"														\
	"pop	ebp"															\
parm [ esi ] [ edi ] [ ecx ] [ eax ] [ ebx ]					\
modify exact [ eax ebx ecx edx esi edi ];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_plain_textured_polygon ( struct TEXTURE_MAP *texture )
{

	int
		y,
		x1,
		x2,
		pitch,
		texture_width,
		texture_height;

	float
		u,
		v,
		du,
		dv;

	int
		iu,
		iv,
		idu,
		idv;

	unsigned char
		*texture_data,
		*ptr;

	unsigned short int
		*dst;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	if ( !texture )
	{

		texture = default_texture;
	}

	ptr = get_screen_data ( active_screen );

	pitch = get_screen_pitch ( active_screen );

	texture_width = get_texture_width ( texture );

	texture_height = get_texture_height ( texture );

	texture_data = get_texture_data ( texture );

	ptr += y_min * pitch;

	for ( y = y_min; y <= y_max; y++ )
	{

		int
			x;

		unsigned char
			*texture_ptr;

		x1 = lhs_x[y];

		x2 = rhs_x[y];

		if ( x1 > x2 )
		{

			x1 = rhs_x[y];
	
			x2 = lhs_x[y];

			u = rhs_u[y];

			v = rhs_v[y];

			du = lhs_u[y] - u;

			dv = lhs_v[y] - v;
		}
		else
		{

			x1 = lhs_x[y];
	
			x2 = rhs_x[y];

			u = lhs_u[y];

			v = lhs_v[y];

			du = rhs_u[y] - u;

			dv = rhs_v[y] - v;
		}

		dst = ( ( unsigned short int * ) ptr ) + x1;

		x = x2 - x1;

		du *= one_over_table[x];

		dv *= one_over_table[x];

		u *= ( texture_width * 65535 ) ;

		du *= ( texture_width * 65535 );

		v *= ( texture_height * 65535 );

		dv *= ( texture_height * 65535 );

		convert_float_to_int ( u, &iu );

		convert_float_to_int ( v, &iv );

		convert_float_to_int ( du, &idu );

		convert_float_to_int ( dv, &idv );

		iufraction = ( ( ( unsigned int ) iu ) << 16 );

		ivfraction = ( ( ( unsigned int ) iv ) << 16 );

		idufraction = ( ( ( unsigned int ) idu ) << 16 );

		idvfraction = ( ( ( unsigned int ) idv ) << 16 );

		texture_ptr = texture_data + ( ( iv >> 16 ) << 6 ) + ( iu >> 16 );

		uvstepvcarry[1] = ( ( idv >> 16 ) << 6 ) + ( idu >> 16 );

		uvstepvcarry[0] = ( ( ( idv >> 16 ) + 1 ) << 6 ) + ( idu >> 16 );

		shading_table = NULL;	//&texture_shading_inverse_table[31][0];

		fill_flat_shaded_textured_horizontal_line ( texture_ptr, dst, x, iufraction, ivfraction );

//		for ( ; x >= 0; x-- )
//		{
//
//			unsigned char
//				texel_value;
//
//			texel_value = *texture_ptr;
//
//			*dst++ = texture_shading_inverse_table[31][texel_value];
//
//			texture_ptr = update_texture_pointer ( texture_ptr, &application_shading_table[0][int_intensity] );
//		}

		ptr += pitch;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_flat_shaded_textured_polygon ( struct TEXTURE_MAP *texture, float intensity )
{

	int
		y,
		x1,
		x2,
		pitch,
		texture_width,
		texture_height,
		int_intensity;

	float
		u,
		v,
		du,
		dv;

	int
		iu,
		iv,
		idu,
		idv;

	unsigned char
		*texture_data,
		*ptr;

	unsigned short int
		*dst;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	if ( !texture )
	{

		texture = default_texture;
	}

	ptr = get_screen_data ( active_screen );

	pitch = get_screen_pitch ( active_screen );

	texture_width = get_texture_width ( texture );

	texture_height = get_texture_height ( texture );

	texture_data = get_texture_data ( texture );

	convert_float_to_int ( ( intensity * 31 ), &int_intensity );

	int_intensity = bound ( int_intensity, 0, 31 );

	ptr += y_min * pitch;

	for ( y = y_min; y <= y_max; y++ )
	{

		int
			x;

		unsigned char
			*texture_ptr;

		x1 = lhs_x[y];

		x2 = rhs_x[y];

		if ( x1 > x2 )
		{

			x1 = rhs_x[y];
	
			x2 = lhs_x[y];

			u = rhs_u[y];

			v = rhs_v[y];

			du = lhs_u[y] - u;

			dv = lhs_v[y] - v;
		}
		else
		{

			x1 = lhs_x[y];
	
			x2 = rhs_x[y];

			u = lhs_u[y];

			v = lhs_v[y];

			du = rhs_u[y] - u;

			dv = rhs_v[y] - v;
		}

		dst = ( ( unsigned short int * ) ptr ) + x1;

		x = x2 - x1;

		du *= one_over_table[x];

		dv *= one_over_table[x];

		u *= ( texture_width * 65535 ) ;

		du *= ( texture_width * 65535 );

		v *= ( texture_height * 65535 );

		dv *= ( texture_height * 65535 );

		convert_float_to_int ( u, &iu );

		convert_float_to_int ( v, &iv );

		convert_float_to_int ( du, &idu );

		convert_float_to_int ( dv, &idv );

		iufraction = ( ( ( unsigned int ) iu ) << 16 );

		ivfraction = ( ( ( unsigned int ) iv ) << 16 );

		idufraction = ( ( ( unsigned int ) idu ) << 16 );

		idvfraction = ( ( ( unsigned int ) idv ) << 16 );

		texture_ptr = texture_data + ( ( iv >> 16 ) << 6 ) + ( iu >> 16 );

		uvstepvcarry[1] = ( ( idv >> 16 ) << 6 ) + ( idu >> 16 );

		uvstepvcarry[0] = ( ( ( idv >> 16 ) + 1 ) << 6 ) + ( idu >> 16 );

		shading_table = NULL;	//&texture_shading_inverse_table[int_intensity][0];

		fill_flat_shaded_textured_horizontal_line ( texture_ptr, dst, x, iufraction, ivfraction );

//		for ( ; x >= 0; x-- )
//		{
//
//			unsigned char
//				texel_value;
//
//			texel_value = *texture_ptr;
//
//			*dst++ = application_shading_table[texel_value][int_intensity];
//
//			texture_ptr = update_texture_pointer ( texture_ptr, &application_shading_table[0][int_intensity] );
//		}

		ptr += pitch;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fill_flat_shaded_wrapped_textured_horizontal_line ( unsigned char *texture,
																			unsigned short int *screen,
																			int length,
																			int iu,
																			int iv );

#pragma aux fill_flat_shaded_wrapped_textured_horizontal_line =	\
	"push	ebp"															\
	"mov	edx, ebx"													\
"loop1:"																	\
	"shr	edx, 10"														\
	"mov	ebp, eax"													\
	"shr	ebp, 16"														\
	"and	edx, 0xfc0"													\
	"and	ebp, 0x3f"													\
	"add	ebx, idv"													\
	"add	ebp, edx"													\
	"xor	edx, edx"													\
	"mov	dl, [ esi + ebp ]"										\
	"mov	ebp, shading_table"										\
	"add	eax, idu"													\
	"lea	edi, [ edi + 2 ]"											\
	"mov	dx, [ ebp + edx * 4 ]"									\
	"dec	ecx"															\
	"mov	[ edi -2 ], dx"											\
	"mov	edx, ebx"													\
	"jge	loop1"														\
	"pop	ebp"															\
parm [ esi ] [ edi ] [ ecx ] [ eax ] [ ebx ]					\
modify exact [ eax ebx ecx edx esi edi ];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_flat_shaded_wrapped_textured_polygon ( struct TEXTURE_MAP *texture, float intensity )
{

	int
		y,
		x1,
		x2,
		pitch,
		texture_width,
		texture_height,
		int_intensity;

	float
		u,
		v,
		du,
		dv;

	unsigned char
		*texture_data,
		*ptr;

	unsigned short int
		*dst;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	if ( !texture )
	{

		texture = default_texture;
	}

	ptr = get_screen_data ( active_screen );

	pitch = get_screen_pitch ( active_screen );

	texture_width = get_texture_width ( texture );

	texture_height = get_texture_height ( texture );

	texture_data = get_texture_data ( texture );

	ptr += y_min * pitch;

	convert_float_to_int ( ( intensity * 31 ), &int_intensity );

	int_intensity = bound ( int_intensity, 0, 31 );

	for ( y=y_min; y<=y_max; y++ )
	{

		int
			x,
			texel_u,
			texel_v;

		x1 = lhs_x[y];

		x2 = rhs_x[y];

		if ( x1 > x2 )
		{

			x1 = rhs_x[y];
	
			x2 = lhs_x[y];

			u = rhs_u[y];

			v = rhs_v[y];

			du = lhs_u[y] - u;

			dv = lhs_v[y] - v;
		}
		else
		{

			x1 = lhs_x[y];
	
			x2 = rhs_x[y];

			u = lhs_u[y];

			v = lhs_v[y];

			du = rhs_u[y] - u;

			dv = rhs_v[y] - v;
		}

		dst = ( ( unsigned short int * ) ptr ) + x1;

		x = x2 - x1;

		du *= one_over_table[x];

		dv *= one_over_table[x];

		u *= texture_width;

		v *= texture_height;

		du *= texture_width;

		dv *= texture_height;

		convert_float_to_int ( ( du * 65535 ), &idu );

		convert_float_to_int ( ( dv * 65535 ), &idv );

		convert_float_to_int ( ( u * 65535 ), &texel_u );

		convert_float_to_int ( ( v * 65535 ), &texel_v );

		shading_table = NULL;	//&texture_shading_inverse_table[int_intensity][0];

		fill_flat_shaded_wrapped_textured_horizontal_line ( texture_data, dst, x, texel_u, texel_v );

//		for ( ; x >= 0; x-- )
//		{
//
//			unsigned char
//				texel_value;
//
//			convert_float_to_int ( u, &texel_u );
//
//			convert_float_to_int ( v, &texel_v );
//
//			texel_u &= 63;
//
//			texel_v &= 63;
//
//			texel_value = texture_data[ ( texel_v << 6 ) + texel_u ];
//
//			*dst++ = texture_shading_inverse_table[int_intensity][texel_value];
//
//			u += du;
//
//			v += dv;
//		}
//
		ptr += pitch;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fill_gouraud_shaded_textured_horizontal_line ( unsigned char *ptr, unsigned short int *screen, int length, unsigned int iufraction, unsigned int ivfraction, int ii );

#pragma aux fill_gouraud_shaded_textured_horizontal_line =	\
	"push	ebp"																			\
	"shr	ebx, 16"																		\
	"and	eax, 0xffff0000"															\
	"or	eax, ebx"																	\
	"mov	ebx, edx"																	\
	"mov	ebp, ebx"																	\
	"xor	edx, edx"																	\
"loop1:"																					\
	"shr	ebp, 6"																		\
	"mov	dl, [ esi ]"																\
	"and	ebp, 0x7c00"																\
	"add	ebx, idintensity"															\
	"lea	edi, [ edi + 2 ]"															\
	"add	eax, dword ptr idvfraction"											\
	"mov	edx, [ edx*4 + ebp ]"			\
	"sbb	ebp, ebp"																	\
	"rol	eax, 16"																		\
	"mov	[ edi - 2 ], dx"															\
	"add	eax, idufraction"															\
	"adc	esi, [ uvstepvcarry + ebp*4 + 4 ]"									\
	"xor	edx, edx"																	\
	"ror	eax, 16"																		\
	"mov	ebp, ebx"																	\
	"dec	ecx"																			\
	"jge	loop1"																		\
	"pop	ebp"																			\
parm [ esi ] [ edi ] [ ecx ] [ ebx ] [ eax ] [ edx ]						\
modify exact [ eax ebx ecx edx esi edi ];
//	"mov	edx, [ edx*4 + ebp ]"
//	"mov	edx, texture_shading_inverse_table [ edx*4 + ebp ]"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_gouraud_shaded_textured_polygon ( struct TEXTURE_MAP *texture )
{

	int
		y,
		x1,
		x2,
		pitch,
		texture_width,
		texture_height;

	float
		u,
		v,
		i,
		du,
		dv,
		di;

	int
		iu,
		iv,
		int_intensity,
		idu,
		idv;

	unsigned char
		*texture_data,
		*ptr;

	unsigned short int
		*dst;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	if ( !texture )
	{

		texture = default_texture;
	}

	ptr = get_screen_data ( active_screen );

	pitch = get_screen_pitch ( active_screen );

	texture_width = get_texture_width ( texture );

	texture_height = get_texture_height ( texture );

	texture_data = get_texture_data ( texture );

	ptr += y_min * pitch;

	for ( y=y_min; y<=y_max; y++ )
	{

		int
			x;

		unsigned char
			*texture_ptr;

		x1 = lhs_x[y];

		x2 = rhs_x[y];

		if ( x1 > x2 )
		{

			x1 = rhs_x[y];
	
			x2 = lhs_x[y];

			u = rhs_u[y];

			v = rhs_v[y];

			i = rhs_i[y];

			du = lhs_u[y] - u;

			dv = lhs_v[y] - v;

			di = lhs_i[y] - i;
		}
		else
		{

			x1 = lhs_x[y];
	
			x2 = rhs_x[y];

			u = lhs_u[y];

			v = lhs_v[y];

			i = lhs_i[y];

			du = rhs_u[y] - u;

			dv = rhs_v[y] - v;

			di = rhs_i[y] - i;
		}

		dst = ( ( unsigned short int * ) ptr ) + x1;

		x = x2 - x1;

		du *= one_over_table[x];

		dv *= one_over_table[x];

		di *= one_over_table[x];

		u *= ( texture_width * 65535 ) ;

		du *= ( texture_width * 65535 );

		v *= ( texture_height * 65535 );

		dv *= ( texture_height * 65535 );

		i *= 31 * 65535;

		di *= 31 * 65535;

		convert_float_to_int ( u, &iu );

		convert_float_to_int ( v, &iv );

		convert_float_to_int ( i, &int_intensity );

		convert_float_to_int ( du, &idu );

		convert_float_to_int ( dv, &idv );

		convert_float_to_int ( di, &idintensity );

		iufraction = ( ( ( unsigned int ) iu ) << 16 );

		ivfraction = ( ( ( unsigned int ) iv ) << 16 );

		idufraction = ( ( ( unsigned int ) idu ) << 16 );

		idvfraction = ( ( ( unsigned int ) idv ) << 16 );

		texture_ptr = texture_data + ( ( iv >> 16 ) << 6 ) + ( iu >> 16 );

		uvstepvcarry[1] = ( ( idv >> 16 ) << 6 ) + ( idu >> 16 );

		uvstepvcarry[0] = ( ( ( idv >> 16 ) + 1 ) << 6 ) + ( idu >> 16 );

		fill_gouraud_shaded_textured_horizontal_line ( texture_ptr, dst, x, iufraction, ivfraction, int_intensity );

		ptr += pitch;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fill_gouraud_shaded_wrapped_textured_horizontal_line ( unsigned short int *screen,
																			int length,
																			int iu,
																			int iv,
																			int intensity );

#pragma aux fill_gouraud_shaded_wrapped_textured_horizontal_line =	\
	"push	ebp"																	\
	"mov	edx, ebx"															\
"loop1:"																			\
	"shr	edx, 10"																\
	"mov	ebp, eax"															\
	"shr	ebp, 16"																\
	"and	edx, 0xfc0"															\
	"and	ebp, 0x3f"															\
	"add	ebx, idv"															\
	"add	ebp, edx"															\
	"xor	edx, edx"															\
	"add	ebp, texture_data_ptr"											\
	"mov	dl, [ ebp ]"														\
	"mov	ebp, esi"															\
	"shr	ebp, 6"																\
	"add	eax, idu"															\
	"and	ebp, 0x7c00"														\
	"lea	edi, [ edi + 2 ]"													\
	"add	esi, idintensity"													\
	"dec	ecx"																	\
	"mov	edx, [ ebp + edx * 4 ]"	\
	"mov	[ edi -2 ], dx"													\
	"mov	edx, ebx"															\
	"jge	loop1"																\
	"pop	ebp"																	\
parm [ edi ] [ ecx ] [ eax ] [ ebx ] [ esi ]							\
modify exact [ eax ebx ecx edx esi edi ];

//	"mov	edx, [ ebp + edx * 4 ]"	
//	"mov	edx, texture_shading_inverse_table [ ebp + edx * 4 ]"	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_gouraud_shaded_wrapped_textured_polygon ( struct TEXTURE_MAP *texture )
{

	int
		y,
		x1,
		x2,
		pitch,
		texture_width,
		texture_height,
		int_intensity;

	float
		i,
		u,
		v,
		di,
		du,
		dv;

	unsigned char
		*texture_data,
		*ptr;

	unsigned short int
		*dst;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	if ( !texture )
	{

		texture = default_texture;
	}

	ptr = get_screen_data ( active_screen );

	pitch = get_screen_pitch ( active_screen );

	texture_width = get_texture_width ( texture );

	texture_height = get_texture_height ( texture );

	texture_data_ptr = get_texture_data ( texture );

	texture_data = get_texture_data ( texture );

	ptr += y_min * pitch;

	for ( y=y_min; y<=y_max; y++ )
	{

		int
			x,
			texel_u,
			texel_v;

		x1 = lhs_x[y];

		x2 = rhs_x[y];

		if ( x1 > x2 )
		{

			x1 = rhs_x[y];
	
			x2 = lhs_x[y];

			i = rhs_i[y];

			u = rhs_u[y];

			v = rhs_v[y];

			di = lhs_i[y] - i;

			du = lhs_u[y] - u;

			dv = lhs_v[y] - v;
		}
		else
		{

			x1 = lhs_x[y];
	
			x2 = rhs_x[y];

			i = lhs_i[y];

			u = lhs_u[y];

			v = lhs_v[y];

			di = rhs_i[y] - i;

			du = rhs_u[y] - u;

			dv = rhs_v[y] - v;
		}

		dst = ( ( unsigned short int * ) ptr ) + x1;

		x = x2 - x1;

		di *= one_over_table[x];

		du *= one_over_table[x];

		dv *= one_over_table[x];

		i *= 31.9999;

		u *= texture_width;

		v *= texture_height;

		di *= 31.9999;

		du *= texture_width;

		dv *= texture_height;
/*
		convert_float_to_int ( ( du * 65535 ), &idu );

		convert_float_to_int ( ( dv * 65535 ), &idv );

		convert_float_to_int ( ( u * 65535 ), &texel_u );

		convert_float_to_int ( ( v * 65535 ), &texel_v );

		convert_float_to_int ( ( i * 65535 ), &int_intensity );

		convert_float_to_int ( ( di * 65535 ), &idintensity );


		fill_gouraud_shaded_wrapped_textured_horizontal_line ( dst, x, texel_u, texel_v, int_intensity );
*/
		for ( ; x>=0; x-- )
		{

			unsigned char
				texel_value;

			convert_float_to_int ( u, &texel_u );

			convert_float_to_int ( v, &texel_v );

			convert_float_to_int ( i, &int_intensity );

			texel_u &= 63;

			texel_v &= 63;

			int_intensity &= 31;
//			int_intensity = bound ( int_intensity, 0, 31 );

			texel_value = texture_data[ ( texel_v << 6 ) + texel_u ];

//			*dst++ = texture_shading_inverse_table[int_intensity][texel_value];

			i += di;

			u += du;

			v += dv;
		}

		ptr += pitch;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

