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

#include "maths.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WARNING! FLOATS ARE PROMOTED TO DOUBLES ON THE VARIABLE ARGUMENT LIST (SO USE DOUBLES NOT FLOATS)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_object_attributes (ui_object *obj, va_list pargs)
{

   ui_object_attributes
      attr;

   ASSERT (obj);

   while (TRUE)
   {

      attr = va_arg (pargs, ui_object_attributes);

      switch (attr)
      {

         ////////////////////////////////////////
         case ui_attr_active_screen:
         ////////////////////////////////////////
         {

				struct SCREEN
					*active_screen;

            active_screen = va_arg (pargs, struct SCREEN *);

            set_ui_object_active_screen (obj, (struct SCREEN *) active_screen);

            break;
         }

			////////////////////////////////////////
         case ui_attr_add_text:
         ////////////////////////////////////////
         {

            const char
               *text;

            text = va_arg (pargs, const char *);

            set_ui_object_add_text (obj, text);

            break;
         }

			////////////////////////////////////////
			case ui_attr_add_list_item:
			////////////////////////////////////////
			{

				notify_types
					notify;

				float
					x_size,
					y_size,
					new_position;

				ui_object_types
					type;

				const char
					*text;

				type = va_arg (pargs, ui_object_types);

				text = va_arg (pargs, const char *);

				x_size = get_ui_object_x_size (obj);

				y_size = ui_get_font_height () + LIST_ITEM_SPACING;

				new_position = get_next_list_position (obj);

				notify = (type == UI_TYPE_TEXT) ? NOTIFY_TYPE_BUTTON_EITHER : NOTIFY_TYPE_BUTTON_UP;

				create_ui_object
					(
						type,
						UI_ATTR_PARENT (obj),
						UI_ATTR_SIZE (x_size, y_size),
						UI_ATTR_TEXT (text),
						UI_ATTR_LIST_ITEM,
						UI_ATTR_NOTIFY_ON (notify),
						UI_ATTR_POSITION (LIST_ITEM_SPACING * 3, new_position),
						UI_ATTR_FUNCTION (ui_object_list_item_function),
						UI_ATTR_RIGHT_FUNCTION (ui_object_list_item_right_function),
						UI_ATTR_END
					);

				break;
			}

			////////////////////////////////////////
         case ui_attr_alpha_graphic:
         ////////////////////////////////////////
         {

				int 
					graphic;

            graphic = va_arg (pargs, int);

            set_ui_object_graphic (obj, (unsigned short int *) graphic);

				set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);

            break;
         }
			////////////////////////////////////////
         case ui_attr_association:
         ////////////////////////////////////////
         {

	         ui_object
               *association;

            association = (ui_object *) va_arg (pargs, int);

            set_ui_object_association (obj, association);

            break;
         }

			////////////////////////////////////////
         case ui_attr_autosize:
         ////////////////////////////////////////
         {

            int
               autosize;

            autosize = va_arg (pargs, int);

            set_ui_object_autosize (obj, autosize);

            break;
         }

			////////////////////////////////////////
         case ui_attr_child:
         ////////////////////////////////////////
         {

		      ui_object
               *child;

            child = (ui_object *) va_arg (pargs, int);

            set_ui_object_child (obj, child);

            break;
         }

			////////////////////////////////////////
         case ui_attr_clear:
         ////////////////////////////////////////
         {

            int
               flag;

            flag = va_arg (pargs, int);

            set_ui_object_clear (obj, flag);

            break;
         }

			////////////////////////////////////////
         case ui_attr_close_box:
         ////////////////////////////////////////
         {

            create_ui_object
					(
						UI_TYPE_CLOSE_BOX,
						UI_ATTR_PARENT (obj),
						UI_ATTR_FUNCTION (ui_object_close_box_function),
						UI_ATTR_END
					);

            break;
         }

			////////////////////////////////////////
			case ui_attr_colour:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);
				set_ui_object_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_colour_end:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}
			
			////////////////////////////////////////
			case ui_attr_colour_start:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_colour_gradient:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_colour_gradient_end (obj, rc.red, rc.green, rc.blue, rc.alpha);
				set_ui_object_colour_gradient_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_colour_gradient_end:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_colour_gradient_end (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_colour_gradient_start:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_colour_gradient_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
         case ui_attr_draw_function:
         ////////////////////////////////////////
         {

            void
               *function;

            function = va_arg (pargs, void *);

            set_ui_object_draw_function (obj, function);

            break;
         }

			////////////////////////////////////////
         case ui_attr_drawable:
         ////////////////////////////////////////
         {

            int
               flag;

            flag = va_arg (pargs, int);

            set_ui_object_drawable (obj, flag);

            break;
         }

			////////////////////////////////////////
         case ui_attr_end:
         ////////////////////////////////////////
         {

            return;
         }

			////////////////////////////////////////
			case ui_attr_font_type:
			////////////////////////////////////////
			{

				int
					font_id;

				font_id = va_arg (pargs, int);

				set_ui_object_font_type (obj, font_id);

				break;
			}

			////////////////////////////////////////
			case ui_attr_font_colour:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);
				set_ui_object_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_font_colour_end:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}
			
			////////////////////////////////////////
			case ui_attr_font_colour_start:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
         case ui_attr_function:
         ////////////////////////////////////////
         {

            void
               *function;

            function = va_arg (pargs, void *);

            set_ui_object_function (obj, function);

            break;
         }

			////////////////////////////////////////
			case ui_attr_global:
			////////////////////////////////////////
			{

				int
					flag;

				flag = va_arg (pargs, int);

				set_ui_object_global (obj, flag);

				break;
			}

			////////////////////////////////////////
         case ui_attr_graphic:
         ////////////////////////////////////////
         {

				int 
					graphic;

            graphic = va_arg (pargs, int);

            set_ui_object_graphic (obj, (unsigned short int *) graphic);

            break;
         }

			////////////////////////////////////////
         case ui_attr_graphic_cposition:
         ////////////////////////////////////////
         {

				double
					cx,
					cy;

            cx = va_arg (pargs, double);

            cy = va_arg (pargs, double);

            set_ui_object_cx (obj, cx);

            set_ui_object_cy (obj, cy);

            break;
         }

			////////////////////////////////////////
         case ui_attr_graphic_zoom:
         ////////////////////////////////////////
         {

				int 
					zoom;

            zoom = va_arg (pargs, int);

            set_ui_object_graphic_zoom (obj, zoom);

            break;
         }

			////////////////////////////////////////
         case ui_attr_highlightable:
         ////////////////////////////////////////
         {

            int
               highlightable;

            highlightable = va_arg (pargs, int);

            set_ui_object_highlightable (obj, highlightable);

            break;
         }

			////////////////////////////////////////
         case ui_attr_highlighted:
         ////////////////////////////////////////
         {

            int
               highlighted;

            highlighted = va_arg (pargs, int);

            set_ui_object_highlighted (obj, highlighted);

            break;
         }

			////////////////////////////////////////
         case ui_attr_highlighted_colour:
         ////////////////////////////////////////
         {

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_highlighted_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);
				set_ui_object_highlighted_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

            break;
         }

			////////////////////////////////////////
         case ui_attr_highlighted_colour_end:
         ////////////////////////////////////////
         {

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_highlighted_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);

            break;
         }

			////////////////////////////////////////
         case ui_attr_highlighted_colour_start:
         ////////////////////////////////////////
         {

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_highlighted_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

            break;
         }

			////////////////////////////////////////
			case ui_attr_highlighted_font_type:
			////////////////////////////////////////
			{

				int
					font_id;

				font_id = va_arg (pargs, int);

				set_ui_object_highlighted_font_type (obj, font_id);

				break;
			}

			////////////////////////////////////////
			case ui_attr_highlighted_font_colour:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_highlighted_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);
				set_ui_object_highlighted_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_highlighted_font_colour_end:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_highlighted_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_highlighted_font_colour_start:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_highlighted_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
         case ui_attr_highlighted_function:
         ////////////////////////////////////////
         {

            void
               *function;

            function = va_arg (pargs, void *);

            set_ui_object_highlighted_function (obj, function);

            break;
         }

			////////////////////////////////////////
         case ui_attr_highlighted_notify_on:
         ////////////////////////////////////////
         {

            int
               event;

            event = va_arg (pargs, int);

            set_ui_object_highlighted_notify_on (obj, event);

            break;
         }

			////////////////////////////////////////
         case ui_attr_highlighted_texture_graphic:
         ////////////////////////////////////////
         {

				int
					graphic;

            graphic = va_arg (pargs, int);

            set_ui_object_highlighted_texture_graphic (obj, (struct TEXTURE_GRAPHIC *) graphic);

            break;
         }

			////////////////////////////////////////
         case ui_attr_list_box_y_space:
         ////////////////////////////////////////
			{

				double
					y_space;

				y_space = va_arg (pargs, double);

				set_ui_object_list_box_y_space (obj, y_space);

				break;
			}

			////////////////////////////////////////
         case ui_attr_list_item:
         ////////////////////////////////////////
         {

            set_ui_object_list_item (obj, TRUE);

            break;
         }

			////////////////////////////////////////
			case ui_attr_item_number:
			////////////////////////////////////////
			{

				int
					number;

				number = va_arg (pargs, int);

				set_ui_object_item_number (obj, number);

				break;
			}

			////////////////////////////////////////
			case ui_attr_item_number2:
			////////////////////////////////////////
			{

				int
					number;

				number = va_arg (pargs, int);

				set_ui_object_item_number2 (obj, number);

				break;
			}

			////////////////////////////////////////
         case ui_attr_memory_graphic:
         ////////////////////////////////////////
         {

				int
					width,
					height;

				area_ui_object
					*area;

				struct SCREEN
					*sc;

				area = (area_ui_object *) obj->data;

				if (area->memory_graphic)
				{

					destroy_screen (area->memory_graphic);
				}

				width = va_arg (pargs, int);

				height = va_arg (pargs, int);

				sc = create_screen (width, height, FALSE);

				set_ui_object_memory_graphic (obj, sc);

            break;
         }

			////////////////////////////////////////
         case ui_attr_moveable:
         ////////////////////////////////////////
         {

		      int
               flag;

            flag = va_arg (pargs, int);

            set_ui_object_moveable (obj, flag);

            break;
         }

			////////////////////////////////////////
         case ui_attr_mslider:
         ////////////////////////////////////////
         {

				float
					x,
					y,
					x_size,
					y_size,
					min,
					max,
					inc;

            min = va_arg (pargs, double);

            max = va_arg (pargs, double);

            inc = va_arg (pargs, double);

				x = get_ui_object_x (obj);

				y = get_ui_object_y (obj);

				x_size = get_ui_object_x_size (obj);

				y_size = get_ui_object_y_size (obj);

            create_ui_object
					(
						UI_TYPE_MSLIDER,
						UI_ATTR_PARENT (obj),
						UI_ATTR_POSITION (x, y),
						UI_ATTR_SIZE (x_size, y_size),
						UI_ATTR_SLIDER_MIN (min),
						UI_ATTR_SLIDER_MAX (max),
						UI_ATTR_SLIDER_INC (inc),
						UI_ATTR_END
					);

            break;
			}

			////////////////////////////////////////
         case ui_attr_next:
         ////////////////////////////////////////
         {

		      ui_object
               *next;

            next = (ui_object *) va_arg (pargs, int);

            set_ui_object_next (obj, next);

            break;
         }

			////////////////////////////////////////
         case ui_attr_notify_on:
         ////////////////////////////////////////
         {

            int
               event;

            event = va_arg (pargs, int);

            set_ui_object_notify_on (obj, event);

            break;
         }

			////////////////////////////////////////
         case ui_attr_offset_time:
         ////////////////////////////////////////
			{

				int
					offset_time;

				offset_time = va_arg (pargs, int);

				set_ui_object_offset_time (obj, offset_time);

				break;
			}

			////////////////////////////////////////
         case ui_attr_origin:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);

		      pos.y = va_arg (pargs, double);

            set_ui_object_x_origin (obj, pos.x);

		      set_ui_object_y_origin (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_parent:
         ////////////////////////////////////////
         {

			   ui_object
               *parent;

            parent = (ui_object *) va_arg (pargs, int);

            set_ui_object_parent (obj, parent);

            break;
         }

			////////////////////////////////////////
         case ui_attr_prev:
         ////////////////////////////////////////
         {

		      ui_object
               *prev;

            prev = (ui_object *) va_arg (pargs, int);

            set_ui_object_prev (obj, prev);

            break;
         }

			////////////////////////////////////////
         case ui_attr_position:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);
				
            pos.y = va_arg (pargs, double);

            set_ui_object_x_end (obj, pos.x);
				set_ui_object_y_end (obj, pos.y);

            set_ui_object_x_start (obj, pos.x);
				set_ui_object_y_start (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_position_end:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);
				
            pos.y = va_arg (pargs, double);

            set_ui_object_x_end (obj, pos.x);
				set_ui_object_y_end (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_position_start:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);
				
            pos.y = va_arg (pargs, double);

            set_ui_object_x_start (obj, pos.x);
				set_ui_object_y_start (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_redraw:
         ////////////////////////////////////////
         {

            int
               flag;

            flag = va_arg (pargs, int);

            set_ui_object_redraw (obj, flag);

            break;
         }

			////////////////////////////////////////
         case ui_attr_resizeable:
         ////////////////////////////////////////
         {

		      int
               flag;

            flag = va_arg (pargs, int);

            set_ui_object_resizeable (obj, flag);

            break;
         }

			////////////////////////////////////////
         case ui_attr_right_function:
         ////////////////////////////////////////
         {

            void
               *function;

            function = va_arg (pargs, void *);

            set_ui_object_right_function (obj, function);

            break;
         }

			////////////////////////////////////////
         case ui_attr_selected_colour:
         ////////////////////////////////////////
         {

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_selected_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);
				set_ui_object_selected_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

            break;
         }

			////////////////////////////////////////
         case ui_attr_selected_colour_end:
         ////////////////////////////////////////
         {

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_selected_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);

            break;
         }

			////////////////////////////////////////
         case ui_attr_selected_colour_start:
         ////////////////////////////////////////
         {

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_selected_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

            break;
         }

			////////////////////////////////////////
			case ui_attr_selected_font_colour:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_selected_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);
				set_ui_object_selected_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_selected_font_colour_end:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_selected_font_colour_end (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_selected_font_colour_start:
			////////////////////////////////////////
			{

				real_colour
					rc;

				rc.red = va_arg (pargs, int);
				rc.green = va_arg (pargs, int);
				rc.blue = va_arg (pargs, int);
				rc.alpha = va_arg (pargs, int);

				set_ui_object_selected_font_colour_start (obj, rc.red, rc.green, rc.blue, rc.alpha);

				break;
			}

			////////////////////////////////////////
			case ui_attr_selected_font_type:
			////////////////////////////////////////
			{

				int
					font_id;

				font_id = va_arg (pargs, int);

				set_ui_object_selected_font_type (obj, font_id);

				break;
			}

			////////////////////////////////////////
         case ui_attr_selected_texture_graphic:
         ////////////////////////////////////////
         {

				int
					graphic;

            graphic = va_arg (pargs, int);

            set_ui_object_selected_texture_graphic (obj, (struct TEXTURE_GRAPHIC *) graphic);

            break;
         }

			////////////////////////////////////////
         case ui_attr_size:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);

			   pos.y = va_arg (pargs, double);

            set_ui_object_x_size_end (obj, pos.x);
		      set_ui_object_y_size_end (obj, pos.y);

            set_ui_object_x_size_start (obj, pos.x);
		      set_ui_object_y_size_start (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_size_end:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);

			   pos.y = va_arg (pargs, double);

            set_ui_object_x_size_end (obj, pos.x);
		      set_ui_object_y_size_end (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_size_start:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);

			   pos.y = va_arg (pargs, double);

            set_ui_object_x_size_start (obj, pos.x);
		      set_ui_object_y_size_start (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_slider_min:
         ////////////////////////////////////////
         {

				float
					min;

            min = va_arg (pargs, double);

				set_ui_object_slider_min (obj, min);

				break;
			}

			////////////////////////////////////////
         case ui_attr_slider_max:
         ////////////////////////////////////////
         {

				float
					max;

            max = va_arg (pargs, double);

				set_ui_object_slider_max (obj, max);

				break;
			}

			////////////////////////////////////////
         case ui_attr_slider_inc:
         ////////////////////////////////////////
         {

				float
					inc;

            inc = va_arg (pargs, double);

				set_ui_object_slider_inc (obj, inc);

				break;
			}

			////////////////////////////////////////
         case ui_attr_start_time:
         ////////////////////////////////////////
			{

				int
					start_time;

				start_time = va_arg (pargs, int);

				set_ui_object_start_time (obj, start_time);

				break;
			}

			////////////////////////////////////////
			case ui_attr_state:
			////////////////////////////////////////
			{

				int
					state;

				state = va_arg (pargs, int);

				set_ui_object_state (obj, state);

				break;
			}

			////////////////////////////////////////
         case ui_attr_text:
         ////////////////////////////////////////
         {

            const char
               *text;

            text = va_arg (pargs, const char *);

            set_ui_object_text (obj, text);

            break;
         }

			////////////////////////////////////////
         case ui_attr_text_justify:
         ////////////////////////////////////////
         {

            text_justify_types
               justify;

            justify = va_arg (pargs, text_justify_types);

            set_ui_object_text_justify (obj, justify);

            break;
         }

			////////////////////////////////////////
         case ui_attr_texture_graphic:
         ////////////////////////////////////////
         {

				int
					graphic;

            graphic = va_arg (pargs, int);

            set_ui_object_texture_graphic (obj, (struct TEXTURE_GRAPHIC *) graphic);

            break;
         }

			////////////////////////////////////////
         case ui_attr_time_line:
         ////////////////////////////////////////
			{

				int
					time_length,
					time_offset;

				time_length = va_arg (pargs, int);
				time_offset = va_arg (pargs, int);

				set_ui_object_time_length (obj, time_length);
				set_ui_object_t_value (obj, time_length);

				break;
			}
         ////////////////////////////////////////
         case ui_attr_time_length:
         ////////////////////////////////////////
			{

				int
					time_length;

				time_length = va_arg (pargs, int);

				set_ui_object_time_length (obj, time_length);

				break;
			}

			////////////////////////////////////////
         case ui_attr_tool_tips:
         ////////////////////////////////////////
         {

            const char
               *tool_tips;

            tool_tips = va_arg (pargs, const char *);

            set_ui_object_tool_tips (obj, tool_tips);

            break;
         }

			////////////////////////////////////////
         case ui_attr_tool_tips_timer:
         ////////////////////////////////////////
         {

            int
               tool_tips_timer;

            tool_tips_timer = va_arg (pargs, int);

            set_ui_object_tool_tips_timer (obj, tool_tips_timer);

            break;
         }

			////////////////////////////////////////
         case ui_attr_t_value:
         ////////////////////////////////////////
			{

				float
					t_value;

				t_value = va_arg (pargs, double);

				set_ui_object_t_value (obj, t_value);

				break;
			}

			////////////////////////////////////////
			case ui_attr_user_flag1:
			////////////////////////////////////////
			{

				int
					flag;

				flag = va_arg (pargs, int);

				set_ui_object_user_flag1 (obj, flag);

				break;
			}

			////////////////////////////////////////
			case ui_attr_user_flag2:
			////////////////////////////////////////
			{

				int
					flag;

				flag = va_arg (pargs, int);

				set_ui_object_user_flag2 (obj, flag);

				break;
			}

			////////////////////////////////////////
			case ui_attr_user_flag3:
			////////////////////////////////////////
			{

				int
					flag;

				flag = va_arg (pargs, int);

				set_ui_object_user_flag3 (obj, flag);

				break;
			}

			////////////////////////////////////////
			case ui_attr_user_flag4:
			////////////////////////////////////////
			{

				int
					flag;

				flag = va_arg (pargs, int);

				set_ui_object_user_flag4 (obj, flag);

				break;
			}

			////////////////////////////////////////
			case ui_attr_user_ptr:
			////////////////////////////////////////
			{

				void *
					ptr;

				ptr = va_arg (pargs, void *);

				set_ui_object_user_ptr (obj, ptr);

				break;
			}

			////////////////////////////////////////
         case ui_attr_virtual_coords:
         ////////////////////////////////////////
			{

				int
					flag;

				flag = va_arg (pargs, int);

				set_ui_object_virtual_coords (obj, flag);

				break;
			}

			////////////////////////////////////////
         case ui_attr_virtual_position:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);
				
            pos.y = va_arg (pargs, double);

            set_ui_object_virtual_x (obj, pos.x);

				set_ui_object_virtual_y (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_virtual_size:
         ////////////////////////////////////////
         {

            vec2d
               pos;

            pos.x = va_arg (pargs, double);

			   pos.y = va_arg (pargs, double);

            set_ui_object_virtual_x_size (obj, pos.x);

		      set_ui_object_virtual_y_size (obj, pos.y);

            break;
         }

			////////////////////////////////////////
         case ui_attr_vslider:
         ////////////////////////////////////////
         {

				ui_object
					*vslider;

				float
					min,
					max,
					inc,
					px_size,
					py_size;

            min = va_arg (pargs, double);

            max = va_arg (pargs, double);

            inc = va_arg (pargs, double);

				px_size = get_screen_width (video_screen) / get_ui_object_x_size (obj);
				py_size = get_screen_height (video_screen) / get_ui_object_y_size (obj);

            vslider = create_ui_object
					(
						UI_TYPE_VSLIDER,
						UI_ATTR_PARENT (obj),
						UI_ATTR_VIRTUAL_POSITION (1.0 - (UI_SLIDER_VIRTUAL_WIDTH * px_size), 0.0),
						UI_ATTR_VIRTUAL_SIZE (UI_SLIDER_VIRTUAL_WIDTH * px_size, 1.0),
						UI_ATTR_SLIDER_MIN (min),
						UI_ATTR_SLIDER_MAX (max),
						UI_ATTR_SLIDER_INC (inc),
						UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
						UI_ATTR_END
					);

				set_ui_object_association (obj, vslider);

            break;
			}

			////////////////////////////////////////
         case ui_attr_zoomable_palette_graphic:
         ////////////////////////////////////////
         {

				int 
					graphic;

            graphic = va_arg (pargs, int);

            set_ui_object_zoomable_palette_graphic (obj, (struct ZOOMABLE_GRAPHIC *) graphic);

				set_ui_object_graphic_type (obj, UI_OBJECT_ZOOMABLE_PALETTE_GRAPHIC);

            break;
         }

         ////////////////////////////////////////
         default:
         ////////////////////////////////////////
         {

            debug_fatal ("Invalid ui_object attribute = %d", attr);

            break;
         }
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
