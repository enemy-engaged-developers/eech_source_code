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

#include	"graphics.h"
#include	"3d/3dfunc.h"

#include "cmndline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

D3DCMPFUNC
	zbuffer_default_comparison = D3DCMP_LESSEQUAL,
	zbuffer_shadow_comparison = D3DCMP_LESS;

double
	zbuffer_factor,
	zbuffer_constant,
	zbuffer_constant_elevated_bias,
	zbuffer_constant_normal_bias,
	zbuffer_constant_lowered_bias,
	zbuffer_constant_lowered_bias2,
	zbuffer_constant_shadow_bias,
	zbuffer_constant_shadow_bias_decrement;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_zbuffer_parameters ( float zmin, float zmax, float scaled_zmin, float scaled_zmax )
{

	//
	// The Z buffer is based on 1/Z
	//

	if ( !d3d_using_hardware_tnl )
	{

		if ( scaled_zmin == 1.0 )
		{

			scaled_zmin = 0.9999f;
		}

		if ( scaled_zmax == 1.0 )
		{

			scaled_zmax = 0.9999f;
		}
	}

	zbuffer_factor = ( zmax * zmin * ( scaled_zmax - scaled_zmin ) ) / ( zmax - zmin );
	zbuffer_constant = scaled_zmax + ( zmax * ( scaled_zmin - scaled_zmax ) ) / ( zmax - zmin );

//VJ 051003 based on a tip by Tamlin: trying to solve flickering of shadow and runway.
// used in terrgeom.c line 4420
	zbuffer_constant_elevated_bias = zbuffer_constant + ( ( ( scaled_zmax - scaled_zmin ) * 4 ) / 65535.0 );
	zbuffer_constant_normal_bias = zbuffer_constant + ( ( ( scaled_zmax - scaled_zmin ) * 0 ) / 65535.0 );
	zbuffer_constant_lowered_bias = zbuffer_constant - ( ( ( scaled_zmax - scaled_zmin ) * 4 ) / 65535.0 );
	zbuffer_constant_lowered_bias2 = zbuffer_constant - ( ( ( scaled_zmax - scaled_zmin ) * 18 ) / 65535.0 );
	zbuffer_constant_shadow_bias = zbuffer_constant + ( ( ( scaled_zmax - scaled_zmin ) * 12 /*6*/ ) / 65535.0 );

	//example values:zbuf:1.000125 -1.000125 0.000000 1.000000 1.000064 1.000125 1.000186 1.000308 1.000033

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_zbuffer_screen_using_viewport ( void )
{

//	ASSERT ( !d3d_in_3d_scene );

	if ( d3d_initialised )
	{
		f3d_zbuffer_clear(1.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_zbuffer_screen ( void )
{
	// DirectDraw calls are emulated in DX9, since it's not supported any more.  But modern
	// graphics drivers have buggy support for it.  So rather use clear_zbuffer_screen_using_viewport
	// for clearing zbuffer.  Fix by Bodhammer.
	if (!command_line_no_dx9zbuffer_fix)
	{
		clear_zbuffer_screen_using_viewport();
		return;
	}

	f3d_clear_zbuffer ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
