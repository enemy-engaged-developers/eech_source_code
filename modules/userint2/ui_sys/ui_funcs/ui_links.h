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

extern void (*fn_set_ui_object_association [NUM_UI_TYPES]) (ui_object *obj, ui_object *association);

extern ui_object *(*fn_get_ui_object_association [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_parent [NUM_UI_TYPES]) (ui_object *obj, ui_object *parent);

extern ui_object *(*fn_get_ui_object_parent [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_child [NUM_UI_TYPES]) (ui_object *obj, ui_object *child);

extern ui_object *(*fn_get_ui_object_child [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_next [NUM_UI_TYPES]) (ui_object *obj, ui_object *next);

extern ui_object *(*fn_get_ui_object_next [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_prev [NUM_UI_TYPES]) (ui_object *obj, ui_object *prev);

extern ui_object *(*fn_get_ui_object_prev [NUM_UI_TYPES]) (ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void default_set_ui_object_link (ui_object *obj, ui_object *association);

extern ui_object *default_get_ui_object_link (ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_ui_object_links_default_functions (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define set_ui_object_association(OBJ,ASSOCIATION) (fn_set_ui_object_association [(OBJ)->type] ((OBJ), (ASSOCIATION)))

#define get_ui_object_association(OBJ) (fn_get_ui_object_association [(OBJ)->type] ((OBJ)))

#define set_ui_object_parent(OBJ,PARENT) (fn_set_ui_object_parent [(OBJ)->type] ((OBJ), (PARENT)))

#define get_ui_object_parent(OBJ) (fn_get_ui_object_parent [(OBJ)->type] ((OBJ)))

#define set_ui_object_child(OBJ,CHILD) (fn_set_ui_object_child [(OBJ)->type] ((OBJ), (CHILD)))

#define get_ui_object_child(OBJ) (fn_get_ui_object_child [(OBJ)->type] ((OBJ)))

#define set_ui_object_next(OBJ,NEXT) (fn_set_ui_object_next [(OBJ)->type] ((OBJ), (NEXT)))

#define get_ui_object_next(OBJ) (fn_get_ui_object_next [(OBJ)->type] ((OBJ)))

#define set_ui_object_prev(OBJ,PREV) (fn_set_ui_object_prev [(OBJ)->type] ((OBJ), (PREV)))

#define get_ui_object_prev(OBJ) (fn_get_ui_object_prev [(OBJ)->type] ((OBJ)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
