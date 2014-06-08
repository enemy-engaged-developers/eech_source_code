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

#ifndef _3D_INCLUDED_

#define _3D_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

#include "maths.h"

#include "graphics.h"

#include "3d/3dmodels.h"

#include "3d/textname.h"

#include "3d/textanim.h"

#include "3d/dispanim.h"

#include "3d/displace.h"

#include "3d/3danim.h"

#include "3d/3denv.h"

#include "3d/3dview.h"

#include "3d/objects.h"

#include "3d/3dobjdb.h"

#include "3d/3dobjid.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef NO_INTERNAL_MODULES

#include "3d/external/3dobjbuf.h"

#include "3d/external/3dexplos.h"

#include "3d/external/3ddisp.h"

#include "3d/external/3dclip.h"

#include "3d/external/3dfclip.h"

#include "3d/external/3dconfig.h"

#include "3d/external/3dconstr.h"

#include "3d/external/3dscon.h"

#include "3d/external/3dfaces.h"

#include "3d/external/3dwfaces.h"

#include "3d/external/3dline.h"

#include "3d/external/3dhoriz.h"

#include "3d/external/3dkeyfr.h"

#include "3d/external/3dsun.h"

#include "3d/external/3dmoon.h"

#include "3d/external/3dstrail.h"

#include "3d/external/3dsprite.h"

#include "3d/external/3dstrike.h"

#include "3d/external/3dscene.h"

#include "3d/external/3dlight.h"

#include "3d/external/3dobjvb.h"

#include "3d/external/3dsubobj.h"

#include "3d/external/3dobject.h"

#include "3d/external/3dobjdrh.h"

#include "3d/external/3dobjdrw.h"

#include "3d/external/3dobjdrz.h"

#include "3d/external/3dobjzdr.h"

#include "3d/external/3dobjvis.h"

#include "3d/external/3dobjzdr.h"

#include "3d/external/3dshadow.h"

#include "3d/external/3dpixel.h"

#include "3d/external/3dtemp.h"

#include "3d/external/3dtrans.h"

#include "3d/external/3drain.h"

#include "3d/external/3dstars.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#else /* NO_INTERNAL_MODULES */

#include "3d/3dobjbuf.h"

#include "3d/3dexplos.h"

#include "3d/3ddisp.h"

#include "3d/3dclip.h"

#include "3d/3dfclip.h"

#include "3d/3dconfig.h"

#include "3d/3dconstr.h"

#include "3d/3dscon.h"

#include "3d/3dfaces.h"

#include "3d/3dwfaces.h"

#include "3d/3dline.h"

#include "3d/3dhoriz.h"

#include "3d/3dkeyfr.h"

#include "3d/3dsun.h"

#include "3d/3dmoon.h"

#include "3d/3dstrail.h"

#include "3d/3dsprite.h"

#include "3d/3dstrike.h"

#include "3d/3dscene.h"

#include "3d/3dlight.h"

#include "3d/3dobjvb.h"

#include "3d/3dsubobj.h"

#include "3d/3dobject.h"

#include "3d/3dobjdrh.h"

#include "3d/3dobjdrw.h"

#include "3d/3dobjdrz.h"

#include "3d/3dobjzdr.h"

#include "3d/3dobjvis.h"

#include "3d/3dobjzdr.h"

#include "3d/3dshadow.h"

#include "3d/3dpixel.h"

#include "3d/3dtemp.h"

#include "3d/3dtrans.h"

#include "3d/3drain.h"

#include "3d/3dstars.h"

#endif /* NO_INTERNAL_MODULES */

#include "3d/clouds/clouds.h"

#include "3d/terrain/terrain.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
