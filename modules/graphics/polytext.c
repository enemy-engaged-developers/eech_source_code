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

void	fill_textured_polygon ( void *texture )
{
	/*
	int					y;
	int					x1,x2;
	int					u1, u2, v1, v2;
	int					du, dv;

	int					row, length;

	unsigned	char		*	dst;
	unsigned	char		*	ptr;
	unsigned	char		*	texture_data;
	unsigned	char	*	*	addresses;

	texture_data = texture->data;

	addresses = texture->row_address;

	for ( y=y_min; y<=y_max; y++ )
	{
		row = active_screen->width * y;

		ptr = (unsigned char *) &active_screen->pixels[row];

		x1 = lhs_x[y];
		x2 = rhs_x[y];

		u1 = lhs_u[y];
		v1 = lhs_v[y];

		u2 = rhs_u[y];
		v2 = rhs_v[y];

		if ( x1 > x2 )
		{
			exchange ( x1, x2 );
			exchange ( u1, u2 );
			exchange ( v1, v2 );
		}

		du = u2 - u1;
		dv = v2 - v1;

		dst = ptr + x1;

		length = x2 - x1;
		if ( length == 0 )
		{
			length = 1;
		}

		du /= length;
		dv /= length;

		while ( x1 <= x2 )
		{
			*dst++ = * ( addresses[ (v1>>16) ] + (u1>>16) );

			u1 += du;
			v1 += dv;
			x1 ++;
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	fill_textured_shaded_polygon ( void *texture, int intensity )
{
	/*

	int					y;
	int					x1,x2;
	int					u1, u2, v1, v2;
	int					du, dv;

	int					row, length;

	unsigned	char		*	dst;
	unsigned	char		*	ptr;
	unsigned	char		*	texture_data;
	unsigned	char	*	*	addresses;

	texture_data = texture->data;

	addresses = texture->row_address;

	for ( y=y_min; y<=y_max; y++ )
	{
		row = active_screen->width * y;

		ptr = (unsigned char *) &active_screen->pixels[row];

		x1 = lhs_x[y];
		x2 = rhs_x[y];

		u1 = lhs_u[y];
		v1 = lhs_v[y];

		u2 = rhs_u[y];
		v2 = rhs_v[y];

		if ( x1 > x2 )
		{
			exchange ( x1, x2 );
			exchange ( u1, u2 );
			exchange ( v1, v2 );
		}

		du = u2 - u1;
		dv = v2 - v1;

		dst = ptr + x1;

		length = x2 - x1;
		if ( length == 0 )
		{
			length = 1;
		}

		du /= length;
		dv /= length;

		while ( x1 <= x2 )
		{
			*dst++ = shading_palette[ * ( addresses[ (v1>>16) ] + ( u1>>16 ) )][intensity];	//texture_data[ ( ( v1>>16 )*texture->width ) + ( u1>>16 ) ] ];

			u1 += du;
			v1 += dv;
			x1 ++;
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

