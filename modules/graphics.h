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

#ifndef _GRAPHICS_INCLUDED_

#define _GRAPHICS_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

#include "maths.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef NO_INTERNAL_MODULES

typedef struct tagPALETTEENTRY {
    unsigned char        peRed;
    unsigned char        peGreen;
    unsigned char        peBlue;
    unsigned char        peFlags;
} PALETTEENTRY, *LPPALETTEENTRY;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics/external/dirdraw.h"

#include "graphics/external/d3d.h"

#include "graphics/external/scrnstr.h"

#include "graphics/external/colour.h"

#include "graphics/external/vertex.h"

#include "graphics/external/viewport.h"

#include "graphics/external/clip.h"

#include "graphics/external/dither.h"

#include "graphics/external/dassess.h"

#include "graphics/external/dresol.h"

#include "graphics/external/screens.h"

#include "graphics/external/palette.h"

#include "graphics/external/lbm.h"

#include "graphics/external/heckfill.h"

#include "graphics/external/line.h"

#include "graphics/external/block.h"

#include "graphics/external/circle.h"

#include "graphics/external/mouseptr.h"

#include "graphics/external/pixel.h"

#include "graphics/external/shadfill.h"

#include "graphics/external/pixeltxt.h"

#include "graphics/external/polyfill.h"

#include "graphics/external/polyline.h"

#include "graphics/external/polyscan.h"

#include "graphics/external/polysoft.h"

#include "graphics/external/d3dfog.h"

#include "graphics/external/d3dpoly.h"

#include "graphics/external/d3dstate.h"

#include "graphics/external/d3dvert.h"

#include "graphics/external/gfxzoom.h"

#include "graphics/external/polyd3d.h"

#include "graphics/external/tranbuf.h"

#include "graphics/external/tempbuf.h"

#include "graphics/external/render.h"

#include "graphics/external/bin.h"

#include "graphics/external/tga.h"

#include "graphics/external/psdread.h"

#include "graphics/external/psdwrite.h"

#include "graphics/external/textsys.h"

#include "graphics/external/textuser.h"

#include "graphics/external/textures.h"

#include "graphics/external/textscrn.h"

#include "graphics/external/mipmap.h"

#include "graphics/external/rle.h"

#include "graphics/external/rgb.h"

#include "graphics/external/monofont.h"

#include "graphics/external/monosprt.h"

#include "graphics/external/vcache.h"

#include "graphics/external/zbuffer.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#elif USE_SDL

#include "graphics/SDL/SDL_draw.h"

/* Not yet implemented */

//#include "graphics/scrnstr.h"
//#include "graphics/colour.h"
//#include "graphics/vertex.h"
//#include "graphics/viewport.h"
//#include "graphics/clip.h"
//#include "graphics/dither.h"
//#include "graphics/dassess.h"
//#include "graphics/dresol.h"
//#include "graphics/screens.h"
//#include "graphics/palette.h"
//#include "graphics/lbm.h"
//#include "graphics/heckfill.h"
//#include "graphics/line.h"
//#include "graphics/block.h"
//#include "graphics/circle.h"
//#include "graphics/mouseptr.h"
//#include "graphics/pixel.h"
//#include "graphics/shadfill.h"
//#include "graphics/pixeltxt.h"
//#include "graphics/polyfill.h"
//#include "graphics/polyline.h"
//#include "graphics/polyscan.h"
//#include "graphics/polysoft.h"

//#include "graphics/gfxzoom.h"
//#include "graphics/polyd3d.h"
//#include "graphics/tranbuf.h"
//#include "graphics/tempbuf.h"
//#include "graphics/render.h"
//#include "graphics/bin.h"
//#include "graphics/tga.h"
//#include "graphics/psdread.h"
//#include "graphics/psdwrite.h"
//#include "graphics/textsys.h"
//#include "graphics/textuser.h"
//#include "graphics/textures.h"
//#include "graphics/textscrn.h"
//#include "graphics/mipmap.h"
//#include "graphics/rle.h"
//#include "graphics/rgb.h"
//#include "graphics/monofont.h"
//#include "graphics/monosprt.h"
//#include "graphics/vcache.h"
//#include "graphics/zbuffer.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#else /* NO_INTERNAL_MODULES */

#pragma pack (8)

#include <ddraw.h>
#include <d3d.h>
#include <d3dcaps.h>
#include <d3dtypes.h>

#pragma pack (4)

#include "graphics/dirdraw.h"

#include "graphics/d3d.h"

#include "graphics/scrnstr.h"

#include "graphics/colour.h"

#include "graphics/vertex.h"

#include "graphics/viewport.h"

#include "graphics/clip.h"

#include "graphics/dither.h"

#include "graphics/dassess.h"

#include "graphics/dresol.h"

#include "graphics/screens.h"

#include "graphics/palette.h"

#include "graphics/lbm.h"

#include "graphics/heckfill.h"

#include "graphics/line.h"

#include "graphics/block.h"

#include "graphics/circle.h"

#include "graphics/mouseptr.h"

#include "graphics/pixel.h"

#include "graphics/shadfill.h"

#include "graphics/pixeltxt.h"

#include "graphics/polyfill.h"

#include "graphics/polyline.h"

#include "graphics/polyscan.h"

#include "graphics/polysoft.h"

#include "graphics/d3dfog.h"

#include "graphics/d3dpoly.h"

#include "graphics/d3dstate.h"

#include "graphics/d3dvert.h"

#include "graphics/gfxzoom.h"

#include "graphics/polyd3d.h"

#include "graphics/tranbuf.h"

#include "graphics/tempbuf.h"

#include "graphics/render.h"

#include "graphics/bin.h"

#include "graphics/tga.h"

#include "graphics/psdread.h"

#include "graphics/psdwrite.h"

#include "graphics/textsys.h"

#include "graphics/textuser.h"

#include "graphics/textures.h"

#include "graphics/textscrn.h"

#include "graphics/mipmap.h"

#include "graphics/rle.h"

#include "graphics/rgb.h"

#include "graphics/monofont.h"

#include "graphics/monosprt.h"

#include "graphics/vcache.h"

#include "graphics/zbuffer.h"

#endif /*NO_INTERNAL_MODULES */

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

