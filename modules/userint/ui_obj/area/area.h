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

struct AREA_UI_OBJECT
{

	float
		x,							// in screen coordinates
		y,							// in screen coordinates
		x_size,					// in screen coordinates
		y_size;					// in screen coordinates

	float
		cx, 						//	for zoomable graphic
		cy; 						//	cx, cy in graphic coords

	int
		zoom;						//	graphic zoom integer.

	float
		x_origin,				// relative to parent
		y_origin;				// relative to parent

	ui_object
		*association,			// used to link objects
		*parent,					// parent pointer
		*child,					// child pointer
		*next,					// next pointer
		*prev;					// previous pointer

	unsigned int
		state				: 2, 	// button on or off
		drawable			: 1, 	// actually drawable at all
		autosize			: 1, 	// autosize each time redrawn 
		redraw			: 8, 	// currently needs a redraw
		moveable			: 1, 	// not used
		resizeable		: 1, 	// not used
		clear				: 1, 	// clear or not. memory_graphic will be masked
		list_item		: 1, 	// if member of a list
		global			: 1, 	// to be transmitted or not
		graphic_type	: 3, 	// whether its a graphic, memory graphic or zoomable palette graphic
		notify_on		: 4, 	// obvious
		text_justify	: 4, 	// position of text within object
		user_flag1		: 1,	// user flags
		user_flag2		: 1,
		user_flag3		: 1,
		user_flag4		: 1;

	int
		item_number,			// user data
		item_number2;			// user data

	int
		hilight_font_id,		// enum font id
		font_id;					// enum font id

	char
		*text;					// object's text

	union							// object's graphic pointer.
	{

		unsigned short int	
			*graphic;
	
		struct SCREEN
			*memory_graphic;

		struct ZOOMABLE_GRAPHIC
			*zoomable_palette_graphic;
	};

	void
		((*function) (ui_object *obj, void *arg)),
		((*right_function) (ui_object *obj, void *arg)),
		((*draw_function) (ui_object *obj, void *arg));

	struct SCREEN
		*active_screen;
};

typedef struct AREA_UI_OBJECT area_ui_object;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ar_links.h"

#include "ar_org.h"

#include "ar_slid.h"

#include "ar_txt.h"

#include "ar_size.h"

#include "ar_creat.h"

#include "ar_flags.h"

#include "ar_draw.h"

#include "ar_fns.h"

#include "ar_graph.h"

#include "ar_notif.h"

#include "ar_pos.h"

#include "ar_updt.h"

#include "ar_funcs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void ui_object_autosize (ui_object *obj);

extern void get_text_position (float *x, float *y, float x1, float y1, float x2, float y2,ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
