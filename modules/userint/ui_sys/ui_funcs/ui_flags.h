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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void (*fn_set_ui_object_state [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_state [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_drawable [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_drawable [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_autosize [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_autosize [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_redraw [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_redraw [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_redraw_all [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern void (*fn_set_ui_object_moveable [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_moveable [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_resizeable [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_resizeable [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_list_item [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_list_item [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_item_number [NUM_UI_TYPES]) (ui_object *obj, int number);

extern int (*fn_get_ui_object_item_number [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_item_number2 [NUM_UI_TYPES]) (ui_object *obj, int number);

extern int (*fn_get_ui_object_item_number2 [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_clear [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_clear [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_global [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_global [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_user_flag1 [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_user_flag1 [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_user_flag2 [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_user_flag2 [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_user_flag3 [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_user_flag3 [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_user_flag4 [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_user_flag4 [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_list_box_y_space [NUM_UI_TYPES]) (ui_object *obj, int y_space);

extern int (*fn_get_ui_object_list_box_y_space [NUM_UI_TYPES]) (ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void default_set_ui_object_flag (ui_object *obj, int flag);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_ui_object_flags_default_functions (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define set_ui_object_state(OBJ,STATE) (fn_set_ui_object_state [(OBJ)->type] ((OBJ), (STATE)))

#define get_ui_object_state(OBJ) (fn_get_ui_object_state [(OBJ)->type] ((OBJ)))

#define set_ui_object_drawable(OBJ,DRAWABLE) (fn_set_ui_object_drawable [(OBJ)->type] ((OBJ), (DRAWABLE)))

#define get_ui_object_drawable(OBJ) (fn_get_ui_object_drawable [(OBJ)->type] ((OBJ)))

#define set_ui_object_autosize(OBJ,AUTOSIZE) (fn_set_ui_object_autosize [(OBJ)->type] ((OBJ), (AUTOSIZE)))

#define get_ui_object_autosize(OBJ) (fn_get_ui_object_autosize [(OBJ)->type] ((OBJ)))

#define set_ui_object_redraw(OBJ,REDRAW) (fn_set_ui_object_redraw [(OBJ)->type] ((OBJ), (REDRAW)))

#define get_ui_object_redraw(OBJ) (fn_get_ui_object_redraw [(OBJ)->type] ((OBJ)))

#define set_ui_object_redraw_all(OBJ,REDRAW) (fn_set_ui_object_redraw_all [(OBJ)->type] ((OBJ), (REDRAW)))

#define set_ui_object_moveable(OBJ,MOVEABLE) (fn_set_ui_object_moveable [(OBJ)->type] ((OBJ), (MOVEABLE)))

#define get_ui_object_moveable(OBJ) (fn_get_ui_object_moveable [(OBJ)->type] ((OBJ)))

#define set_ui_object_resizeable(OBJ,RESIZEABLE) (fn_set_ui_object_resizeable [(OBJ)->type] ((OBJ), (RESIZEABLE)))

#define get_ui_object_resizeable(OBJ) (fn_get_ui_object_resizeable [(OBJ)->type] ((OBJ)))

#define set_ui_object_list_item(OBJ,LIST_ITEM) (fn_set_ui_object_list_item [(OBJ)->type] ((OBJ), (LIST_ITEM)))

#define get_ui_object_list_item(OBJ) (fn_get_ui_object_list_item [(OBJ)->type] ((OBJ)))

#define set_ui_object_item_number(OBJ,NUMBER) (fn_set_ui_object_item_number[(OBJ)->type] ((OBJ), (NUMBER)))

#define get_ui_object_item_number(OBJ) (fn_get_ui_object_item_number [(OBJ)->type] ((OBJ)))

#define set_ui_object_item_number2(OBJ,NUMBER) (fn_set_ui_object_item_number2 [(OBJ)->type] ((OBJ), (NUMBER)))

#define get_ui_object_item_number2(OBJ) (fn_get_ui_object_item_number2 [(OBJ)->type] ((OBJ)))

#define set_ui_object_clear(OBJ,CLEAR) (fn_set_ui_object_clear [(OBJ)->type] ((OBJ), (CLEAR)))

#define get_ui_object_clear(OBJ) (fn_get_ui_object_clear [(OBJ)->type] ((OBJ)))

#define set_ui_object_global(OBJ,FLAG) (fn_set_ui_object_global [(OBJ)->type] ((OBJ), (FLAG)))

#define get_ui_object_global(OBJ) (fn_get_ui_object_global [(OBJ)->type] ((OBJ)))

#define set_ui_object_user_flag1(OBJ,FLAG) (fn_set_ui_object_user_flag1 [(OBJ)->type] ((OBJ), (FLAG)))

#define get_ui_object_user_flag1(OBJ) (fn_get_ui_object_user_flag1 [(OBJ)->type] ((OBJ)))

#define set_ui_object_user_flag2(OBJ,FLAG) (fn_set_ui_object_user_flag2 [(OBJ)->type] ((OBJ), (FLAG)))

#define get_ui_object_user_flag2(OBJ) (fn_get_ui_object_user_flag2 [(OBJ)->type] ((OBJ)))

#define set_ui_object_user_flag3(OBJ,FLAG) (fn_set_ui_object_user_flag3 [(OBJ)->type] ((OBJ), (FLAG)))

#define get_ui_object_user_flag3(OBJ) (fn_get_ui_object_user_flag3 [(OBJ)->type] ((OBJ)))

#define set_ui_object_user_flag4(OBJ,FLAG) (fn_set_ui_object_user_flag4 [(OBJ)->type] ((OBJ), (FLAG)))

#define get_ui_object_user_flag4(OBJ) (fn_get_ui_object_user_flag4 [(OBJ)->type] ((OBJ)))

#define set_ui_object_list_box_y_space(OBJ,Y_SPACE) (fn_set_ui_object_list_box_y_space [(OBJ)->type] ((OBJ), (Y_SPACE)))

#define get_ui_object_list_box_y_space(OBJ) (fn_get_ui_object_list_box_y_space [(OBJ)->type] ((OBJ)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
