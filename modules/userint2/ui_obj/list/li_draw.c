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

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_list_ui_object (ui_object *obj)
{

	float
		x1,
		y1,
		x2,
		y2,
		x_size,
		y_size;

	ui_object
		*current_list_item;

#if 0
	rgb_data
		*graphic;
#endif

	struct SCREEN
		*old_active_screen;

	list_ui_object
		*list;

	list = (list_ui_object *) obj->data;

	old_active_screen = get_active_screen ();

	x1 = get_ui_object_x (obj);

	y1 = get_ui_object_y (obj);

	x_size = get_ui_object_x_size (obj);

	y_size = get_ui_object_y_size (obj);

	if ((y_size) && (x_size))
	{

		if (get_ui_object_redraw (obj))
		{

			x2 = x1 + x_size;

			y2 = y1 + y_size;

			if (get_ui_object_active_screen (obj))
			{

				set_active_screen (get_ui_object_active_screen (obj));
			}
			else
			{

				set_active_screen (video_screen);
			}

			//if (lock_screen (active_screen))
			{

#if 0
				graphic = get_ui_object_graphic (obj);
#endif

				if (!get_ui_object_clear (obj))
				{

#if 0
					if (graphic)
					{

						ui_draw_graphic (x1, y1, x2, y2, graphic);
					}
					else
#endif
					{

						int
							state;

						if (get_ui_object_highlighted (obj))
						{

							state = UI_OBJECT_STATE_HIGHLIGHTED;
						}
						else
						{

							state = get_ui_object_state (obj);
						}

						ui_draw_area (x1, y1, x2, y2, obj);
					}
				}

				//unlock_screen (active_screen);
			}

			set_ui_repaint_area (x1, y1, x2, y2);

			list->area.redraw --;
		}

		current_list_item = get_ui_object_child (obj);

		// setup the viewport for this list box

		x1 = get_ui_object_x (obj);

		y1 = get_ui_object_y (obj);

		x2 = x1 + get_ui_object_x_size (obj);

		y2 = y1 + get_ui_object_y_size (obj);

		ui_clip_area (&x1, &y1, &x2, &y2);

		//set_viewport (x1, y1 + LIST_ITEM_SPACING, x2 - LIST_ITEM_SPACING, y2 - LIST_ITEM_SPACING);

		set_viewport (x1, y1, x2, y2);

		ui_set_origin (get_ui_object_x_origin (obj), get_ui_object_y_origin (obj));

		while (current_list_item)
		{

			if (get_ui_object_redraw (current_list_item))
			{

				if (get_ui_object_list_item (current_list_item))
				{

					// only list actual list_items

					if (get_ui_object_drawable (current_list_item ))
					{

						if (get_ui_object_redraw (current_list_item))
						{

							draw_ui_object (current_list_item);
						}
					}
				}
				else
				{

					// update non-list_item

					update_ui_object (current_list_item);
				}
			}

			current_list_item = get_ui_object_next (current_list_item);
		}

		set_active_screen (old_active_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_list_ui_object_draw_functions (ui_object_types type)
{

	fn_draw_ui_object [type] = draw_list_ui_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
