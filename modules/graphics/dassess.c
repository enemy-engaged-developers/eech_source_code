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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ASSESSMENT_STRUCT
{

	DWORD
		flag;

	int
		positive,
		negative;
};

typedef struct ASSESSMENT_STRUCT assessment_struct;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

assessment_struct
	shading_assessment_flags[] =
	{

		{ D3DPSHADECAPS_ALPHAFLATBLEND,		10, -10 },
		{ D3DPSHADECAPS_ALPHAGOURAUDBLEND,	10, -10 },
		{ D3DPSHADECAPS_COLORFLATRGB,			10, -10 },
		{ D3DPSHADECAPS_COLORGOURAUDRGB,		10, -10000 },
		{ D3DPSHADECAPS_FOGFLAT,				10, -10 },
		{ D3DPSHADECAPS_FOGGOURAUD,			10, -10 },
	},

	texture_assessment_flags[] =
	{

		{ D3DPTEXTURECAPS_ALPHA,				10, -10 },
		{ D3DPTEXTURECAPS_PERSPECTIVE,		10, -10 },
		{ D3DPTEXTURECAPS_POW2,					0, -10 },
		{ D3DPTEXTURECAPS_SQUAREONLY,			0, -10 },
		{ D3DPTEXTURECAPS_TRANSPARENCY,		10, -10 },
	},

	texture_filter_assessment_flags[] =
	{

		{ D3DPTFILTERCAPS_LINEAR,				10, -10 },
		{ D3DPTFILTERCAPS_LINEARMIPLINEAR,	10, -10 },
		{ D3DPTFILTERCAPS_LINEARMIPNEAREST,	10, -10 },
		{ D3DPTFILTERCAPS_MIPLINEAR,			10, -10 },
		{ D3DPTFILTERCAPS_MIPNEAREST,			10, -10 },
		{ D3DPTFILTERCAPS_NEAREST,				10, -10 },
	},

	texture_blend_assessment_flags[] =
	{

		{ D3DPTBLENDCAPS_COPY, 					10, -10 },
		{ D3DPTBLENDCAPS_DECAL, 				10, -10 },
		{ D3DPTBLENDCAPS_DECALALPHA, 			10, -10 },
		{ D3DPTBLENDCAPS_DECALMASK, 			10, -10 },
		{ D3DPTBLENDCAPS_MODULATE, 			10, -10 },
		{ D3DPTBLENDCAPS_MODULATEALPHA, 		10, -10 },
		{ D3DPTBLENDCAPS_MODULATEMASK, 		10, -10 },
	},

	texture_address_assessment_flags[] =
	{

		{ D3DPTADDRESSCAPS_CLAMP,				10, -10 },
		{ D3DPTADDRESSCAPS_MIRROR,				10, -10 },
		{ D3DPTADDRESSCAPS_WRAP,				10, -10000 },
	},

	zbuffer_assessment_flags[] =
	{

		{ 0,											100, -10000 },
	};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT CALLBACK ddraw_assess_enum_3d_devices (
  LPSTR lpDeviceDescription,           
  LPSTR lpDeviceName,                  
  LPD3DDEVICEDESC7 lpD3DHWDeviceDesc,  
  LPVOID lpContext                     
);

//static HRESULT WINAPI ddraw_assess_enum_3d_devices (LPGUID lpGuid, LPSTR DevDesc, LPSTR DevName, LPD3DDEVICEDESC7 lpHWDesc, LPD3DDEVICEDESC7 lpHELDesc, LPVOID lpContext);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ddraw_internal_assess_3d_capabilities ( LPDIRECTDRAWX lpDD )
{

	HRESULT
		d3drval;

	LPDIRECT3DX
		lpD3D;

	int
		assessment;

	//
	// Create the direct3d device from this direct draw object
	//

	d3drval = IDirectDraw7_QueryInterface ( lpDD, GUID_PREFIX IID_IDirect3D7, ( LPVOID FAR * ) &lpD3D );

#if ( DEBUG_MODULE )
	debug_log ( "Created Direct3D: %08x", lpD3D );
#endif

	//
	// If we can't then we don't have 3D capability. Assessment is 0.
	//

	if ( d3drval != DD_OK )
	{

		return ( -10000 );
	}

	//
	// Default assessment is 0.
	//

	assessment = 0;

	//
	// Enumerate the devices from this 3d object, assessing them, and setting the assessment to the best
	//

	IDirect3D7_EnumDevices ( lpD3D, ddraw_assess_enum_3d_devices, &assessment );

	//
	// Release the D3D interface.
	//

	IDirect3D7_Release ( lpD3D );

	return ( assessment );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT CALLBACK ddraw_assess_enum_3d_devices (
  LPSTR DevDesc,
  LPSTR DevName,
  LPD3DDEVICEDESC7 lpHWDesc,
  LPVOID lpContext                     
)
//static HRESULT WINAPI ddraw_assess_enum_3d_devices (LPGUID lpGuid, LPSTR DevDesc, LPSTR DevName, LPD3DDEVICEDESC7 lpHWDesc, LPD3DDEVICEDESC7 lpHELDesc, LPVOID lpContext)
{

	int
		assessment,
		*best_yet_assessment;

	best_yet_assessment = ( int * ) lpContext;

	assessment = 0;

	//
	// Is this driver hardware ?
	//

	{

		if ( lpHWDesc->dwDevCaps & D3DDD_TRICAPS )
		{

			int
				count;

			//
			// Assess the rendering primitives available
			//

			//
			// First, the shading capabilities
			//

			for ( count = 0; count < ( sizeof ( shading_assessment_flags ) / sizeof ( assessment_struct ) ); count ++ )
			{

				if ( lpHWDesc->dpcTriCaps.dwShadeCaps & shading_assessment_flags[count].flag )
				{

					assessment += shading_assessment_flags[count].positive;
				}
				else
				{

					assessment += shading_assessment_flags[count].negative;
				}
			}

			//
			// Next, the texturing capabilities
			//

			for ( count = 0; count < ( sizeof ( texture_assessment_flags ) / sizeof ( assessment_struct ) ); count ++ )
			{

				if ( lpHWDesc->dpcTriCaps.dwTextureCaps & texture_assessment_flags[count].flag )
				{

					assessment += texture_assessment_flags[count].positive;
				}
				else
				{

					assessment += texture_assessment_flags[count].negative;
				}
			}

			//
			// Next, the texture filtering capabilities
			//

			for ( count = 0; count < ( sizeof ( texture_filter_assessment_flags ) / sizeof ( assessment_struct ) ); count ++ )
			{

				if ( lpHWDesc->dpcTriCaps.dwTextureFilterCaps & texture_filter_assessment_flags[count].flag )
				{

					assessment += texture_filter_assessment_flags[count].positive;
				}
				else
				{

					assessment += texture_filter_assessment_flags[count].negative;
				}
			}

			//
			// Next, the texture blending capabilities
			//

			for ( count = 0; count < ( sizeof ( texture_blend_assessment_flags ) / sizeof ( assessment_struct ) ); count ++ )
			{

				if ( lpHWDesc->dpcTriCaps.dwTextureBlendCaps & texture_blend_assessment_flags[count].flag )
				{

					assessment += texture_blend_assessment_flags[count].positive;
				}
				else
				{

					assessment += texture_blend_assessment_flags[count].negative;
				}
			}

			//
			// Next, the texture addressing capabilities
			//

			for ( count = 0; count < ( sizeof ( texture_address_assessment_flags ) / sizeof ( assessment_struct ) ); count ++ )
			{

				if ( lpHWDesc->dpcTriCaps.dwTextureAddressCaps & texture_address_assessment_flags[count].flag )
				{

					assessment += texture_address_assessment_flags[count].positive;
				}
				else
				{

					assessment += texture_address_assessment_flags[count].negative;
				}
			}

			//
			// Next, the zbuffering capabilities
			//

			if ( lpHWDesc->dwDeviceZBufferBitDepth )
			{

				assessment += zbuffer_assessment_flags[0].positive;
			}
			else
			{

				assessment += zbuffer_assessment_flags[0].negative;
			}
		}
	}

	if ( assessment > *best_yet_assessment )
	{

		*best_yet_assessment = assessment;
	}

	return ( D3DENUMRET_OK );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

