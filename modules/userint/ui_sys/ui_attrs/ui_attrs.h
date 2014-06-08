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

enum UI_OBJECT_ATTRIBUTES
{

	ui_attr_position,
	ui_attr_size,
	ui_attr_origin,
	ui_attr_drawable,
	ui_attr_autosize,
	ui_attr_redraw,
	ui_attr_moveable,
	ui_attr_resizeable,
	ui_attr_association,
	ui_attr_parent,
	ui_attr_child,
	ui_attr_next,
	ui_attr_prev,
	ui_attr_function,
	ui_attr_right_function,
	ui_attr_draw_function,
	ui_attr_notify_on,
	ui_attr_clear,
	ui_attr_text,
	ui_attr_add_text,
	ui_attr_text_justify,
	ui_attr_graphic,
	ui_attr_active_screen,
	ui_attr_alpha_graphic,
	ui_attr_memory_graphic,
	ui_attr_zoomable_palette_graphic,
	ui_attr_graphic_zoom,
	ui_attr_graphic_cposition,
	ui_attr_add_list_item,
	ui_attr_list_item,
	ui_attr_item_number,
	ui_attr_item_number2,
	ui_attr_vslider,
	ui_attr_slider_min,
	ui_attr_slider_max,
	ui_attr_slider_inc,
	ui_attr_hslider,
	ui_attr_hvslider,
	ui_attr_mslider,
	ui_attr_close_box,
	ui_attr_state,
	ui_attr_colour,
	ui_attr_global,
	ui_attr_user_flag1,
	ui_attr_user_flag2,
	ui_attr_user_flag3,
	ui_attr_user_flag4,
	ui_attr_font,
	ui_attr_hilight_font,
	ui_attr_list_box_y_space,
	ui_attr_end,
	NUM_UI_ATTRIBUTES
};

typedef enum UI_OBJECT_ATTRIBUTES ui_object_attributes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WARNING: FLOATS ARE PROMOTED TO DOUBLES ON THE VARIABLE ARGUMENT LIST (SO USE DOUBLES NOT FLOATS)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UI_ATTR_END ui_attr_end

#define UI_ATTR_POSITION(X,Y) ui_attr_position, ((double)(X)), ((double)(Y))

#define UI_ATTR_SIZE(X_SIZE,Y_SIZE) ui_attr_size, ((double)(X_SIZE)), ((double)(Y_SIZE))

#define UI_ATTR_ORIGIN(X_ORIGIN,Y_ORIGIN) ui_attr_origin, ((double)(X_ORIGIN)), ((double)(Y_ORIGIN))

#define UI_ATTR_DRAWABLE(FLAG) ui_attr_drawable, ((int)(FLAG))

#define UI_ATTR_AUTOSIZE(FLAG) ui_attr_autosize, ((int)(FLAG))

#define UI_ATTR_REDRAW(FLAG) ui_attr_redraw, ((int)(FLAG))

#define UI_ATTR_MOVEABLE(FLAG) ui_attr_moveable, ((int)(FLAG))

#define UI_ATTR_RESIZEABLE(FLAG) ui_attr_resizeable, ((int)(FLAG))

#define UI_ATTR_ASSOCIATION(ASSOCIATION) ui_attr_association, ((ui_object *)(ASSOCIATION))

#define UI_ATTR_PARENT(PARENT) ui_attr_parent, ((ui_object *)(PARENT))

#define UI_ATTR_CHILD(CHILD) ui_attr_child, ((ui_object *)(CHILD))

#define UI_ATTR_NEXT(NEXT) ui_attr_next, ((ui_object *)(NEXT))

#define UI_ATTR_PREV(PREV) ui_attr_prev, ((ui_object *)(PREV))

#define UI_ATTR_FUNCTION(FUNCTION) ui_attr_function, ((void *)(FUNCTION))

#define UI_ATTR_RIGHT_FUNCTION(FUNCTION) ui_attr_right_function, ((void *)(FUNCTION))

#define UI_ATTR_DRAW_FUNCTION(FUNCTION) ui_attr_draw_function, ((void *)(FUNCTION))

#define UI_ATTR_NOTIFY_ON(EVENT) ui_attr_notify_on, ((int)(EVENT))

#define UI_ATTR_CLEAR(FLAG) ui_attr_clear, ((int)FLAG)

#define UI_ATTR_TEXT(TEXT) ui_attr_text, ((char *)(TEXT))

#define UI_ATTR_ADD_TEXT(TEXT) ui_attr_add_text, ((char *)(TEXT))

#define UI_ATTR_TEXT_JUSTIFY(JUSTIFY) ui_attr_text_justify, ((text_justify_types)(JUSTIFY))

#define UI_ATTR_GRAPHIC(GRAPHIC) ui_attr_graphic, ((struct RGB_DATA *)(GRAPHIC))

#define UI_ATTR_ALPHA_GRAPHIC(GRAPHIC) ui_attr_alpha_graphic, ((char *)(GRAPHIC))

#define UI_ATTR_ACTIVE_SCREEN(ACTIVE_SCREEN) ui_attr_active_screen, ((struct SCREEN *)(ACTIVE_SCREEN))

#define UI_ATTR_MEMORY_GRAPHIC(X_SIZE,Y_SIZE) ui_attr_memory_graphic, ((int)(X_SIZE)), ((int)(Y_SIZE))

#define UI_ATTR_ZOOMABLE_PALETTE_GRAPHIC(GRAPHIC) ui_attr_zoomable_palette_graphic, ((struct ZOOMABLE_GRAPHIC *)(GRAPHIC))

#define UI_ATTR_GRAPHIC_ZOOM(ZOOM) ui_attr_graphic_zoom, ((int)(ZOOM))

#define UI_ATTR_GRAPHIC_CPOSITION(CX,CY) ui_attr_graphic_cposition, ((double)(CX)), ((double)(CY))

#define UI_ATTR_ADD_LIST_ITEM(TYPE,TEXT) ui_attr_add_list_item, ((ui_object_types)(TYPE)), ((char *)(TEXT))

#define UI_ATTR_ITEM_NUMBER(NUMBER) ui_attr_item_number, ((int)(NUMBER))

#define UI_ATTR_ITEM_NUMBER2(NUMBER) ui_attr_item_number2, ((int)(NUMBER))

#define UI_ATTR_LIST_ITEM ui_attr_list_item

#define UI_ATTR_SLIDER_MIN(MIN) ui_attr_slider_min, ((float) (MIN))

#define UI_ATTR_SLIDER_MAX(MAX) ui_attr_slider_max, ((float) (MAX))

#define UI_ATTR_SLIDER_INC(INC) ui_attr_slider_inc, ((float) (INC))

#define UI_ATTR_VSLIDER(MIN,MAX,INC) ui_attr_vslider, ((float) (MIN)), ((float) (MAX)), ((float) (INC))

#define UI_ATTR_HSLIDER(MIN,MAX,INC) ui_attr_hslider, ((float) (MIN)), ((float) (MAX)), ((float) (INC))

#define UI_ATTR_HVSLIDER(MIN,MAX,INC) ui_attr_hvslider, ((float) (MIN)), ((float) (MAX)), ((float) (INC))

#define UI_ATTR_MSLIDER(MIN,MAX,INC) ui_attr_mslider, ((float) (MIN)), ((float) (MAX)), ((float) (INC))

#define UI_ATTR_CLOSE_BOX ui_attr_close_box

#define UI_ATTR_STATE(STATE) ui_attr_state, ((int)(STATE))

#define UI_ATTR_COLOUR(COLOUR_R,COLOUR_G,COLOUR_B) ui_attr_colour, ((int)(COLOUR_R)), ((int)(COLOUR_G)), ((int)(COLOUR_B))

#define UI_ATTR_GLOBAL(FLAG) ui_attr_global, ((int)(FLAG))

#define UI_ATTR_USER_FLAG1(FLAG) ui_attr_user_flag1, ((int)(FLAG))

#define UI_ATTR_USER_FLAG2(FLAG) ui_attr_user_flag2, ((int)(FLAG))

#define UI_ATTR_USER_FLAG3(FLAG) ui_attr_user_flag3, ((int)(FLAG))

#define UI_ATTR_USER_FLAG4(FLAG) ui_attr_user_flag4, ((int)(FLAG))

#define UI_ATTR_FONT(FONT_ID) ui_attr_font, ((int)(FONT_ID))

#define UI_ATTR_HILIGHT_FONT(HILIGHT_FONT_ID) ui_attr_hilight_font, ((int)(HILIGHT_FONT_ID))

#define UI_ATTR_LIST_BOX_Y_SPACE(SPACE) ui_attr_list_box_y_space, ((int)(SPACE))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_object_attributes (ui_object *obj, va_list pargs);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
