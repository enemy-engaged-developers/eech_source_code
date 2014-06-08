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

#if 0
struct RGB_DATA;

extern void (*fn_set_ui_object_graphic [NUM_UI_TYPES]) (ui_object *obj, struct RGB_DATA *graphic);

extern struct RGB_DATA *(*fn_get_ui_object_graphic [NUM_UI_TYPES]) (ui_object *obj);
#endif

extern void (*fn_set_ui_object_texture_graphic [NUM_UI_TYPES]) (ui_object *obj, struct TEXTURE_GRAPHIC *);

extern struct TEXTURE_GRAPHIC *(*fn_get_ui_object_texture_graphic [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_highlighted_texture_graphic [NUM_UI_TYPES]) (ui_object *obj, struct TEXTURE_GRAPHIC *);

extern struct TEXTURE_GRAPHIC *(*fn_get_ui_object_highlighted_texture_graphic [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_selected_texture_graphic [NUM_UI_TYPES]) (ui_object *obj, struct TEXTURE_GRAPHIC *);

extern struct TEXTURE_GRAPHIC *(*fn_get_ui_object_selected_texture_graphic [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_active_screen [NUM_UI_TYPES]) (ui_object *obj, struct SCREEN *active_screen);

extern struct SCREEN *(*fn_get_ui_object_active_screen [NUM_UI_TYPES]) (ui_object *obj);

#if 0
extern void (*fn_set_ui_object_memory_graphic [NUM_UI_TYPES]) (ui_object *obj, struct SCREEN *memory_graphic);

extern struct SCREEN *(*fn_get_ui_object_memory_graphic [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_zoomable_palette_graphic [NUM_UI_TYPES]) (ui_object *obj, struct ZOOMABLE_GRAPHIC *graphic);

extern struct ZOOMABLE_GRAPHIC *(*fn_get_ui_object_zoomable_palette_graphic [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_graphic_type [NUM_UI_TYPES]) (ui_object *obj, int flag);

extern int (*fn_get_ui_object_graphic_type [NUM_UI_TYPES]) (ui_object *obj);

extern void (*fn_set_ui_object_graphic_zoom [NUM_UI_TYPES]) (ui_object *obj, int zoom);

extern int (*fn_get_ui_object_graphic_zoom [NUM_UI_TYPES]) (ui_object *obj);
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
extern void default_set_ui_object_graphic (ui_object *obj, rgb_data *graphic);

extern rgb_data *default_get_ui_object_graphic (ui_object *obj);
#endif

extern void default_set_ui_object_texture_graphic (ui_object *obj, struct TEXTURE_GRAPHIC *graphic);

extern struct TEXTURE_GRAPHIC *default_get_ui_object_texture_graphic (ui_object *obj);

extern void default_set_ui_object_highlighted_texture_graphic (ui_object *obj, struct TEXTURE_GRAPHIC *graphic);

extern struct TEXTURE_GRAPHIC *default_get_ui_object_highlighted_texture_graphic (ui_object *obj);

extern void default_set_ui_object_selected_texture_graphic (ui_object *obj, struct TEXTURE_GRAPHIC *graphic);

extern struct TEXTURE_GRAPHIC *default_get_ui_object_selected_texture_graphic (ui_object *obj);

#if 0
extern void default_set_ui_object_memory_graphic (ui_object *obj, struct SCREEN *memory_graphic);

extern struct SCREEN *default_get_ui_object_memory_graphic (ui_object *obj);

extern void default_set_ui_object_zoomable_palette_graphic (ui_object *obj, struct ZOOMABLE_GRAPHIC *graphic);

extern struct ZOOMABLE_GRAPHIC *default_get_ui_object_zoomable_palette_graphic (ui_object *obj);

extern void default_set_ui_object_graphic_type (ui_object *obj, int flag);

extern int default_get_ui_object_graphic_type (ui_object *obj);

extern void default_set_ui_object_graphic_zoom (ui_object *obj, int zoom);

extern int default_get_ui_object_graphic_zoom (ui_object *obj);
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_ui_object_graphic_default_functions (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
#define set_ui_object_graphic(OBJ,GRAPHIC) (fn_set_ui_object_graphic [(OBJ)->type] ((OBJ), (GRAPHIC)))

#define get_ui_object_graphic(OBJ) (fn_get_ui_object_graphic [(OBJ)->type] ((OBJ)))
#endif

#define set_ui_object_texture_graphic(OBJ,GRAPHIC) (fn_set_ui_object_texture_graphic [(OBJ)->type] ((OBJ), (GRAPHIC)))

#define get_ui_object_texture_graphic(OBJ) (fn_get_ui_object_texture_graphic [(OBJ)->type] ((OBJ)))

#define set_ui_object_highlighted_texture_graphic(OBJ,GRAPHIC) (fn_set_ui_object_highlighted_texture_graphic [(OBJ)->type] ((OBJ), (GRAPHIC)))

#define get_ui_object_highlighted_texture_graphic(OBJ) (fn_get_ui_object_highlighted_texture_graphic [(OBJ)->type] ((OBJ)))

#define set_ui_object_selected_texture_graphic(OBJ,GRAPHIC) (fn_set_ui_object_selected_texture_graphic [(OBJ)->type] ((OBJ), (GRAPHIC)))

#define get_ui_object_selected_texture_graphic(OBJ) (fn_get_ui_object_selected_texture_graphic [(OBJ)->type] ((OBJ)))

#if 0
#define set_ui_object_memory_graphic(OBJ,MEMORY_GRAPHIC) (fn_set_ui_object_memory_graphic [(OBJ)->type] ((OBJ), (MEMORY_GRAPHIC)))

#define get_ui_object_memory_graphic(OBJ) (fn_get_ui_object_memory_graphic [(OBJ)->type] ((OBJ)))
#endif

#define set_ui_object_active_screen(OBJ,ACTIVE_SCREEN) (fn_set_ui_object_active_screen [(OBJ)->type] ((OBJ), (ACTIVE_SCREEN)))

#define get_ui_object_active_screen(OBJ) (fn_get_ui_object_active_screen [(OBJ)->type] ((OBJ)))

#if 0
#define set_ui_object_zoomable_palette_graphic(OBJ,GRAPHIC) (fn_set_ui_object_zoomable_palette_graphic [(OBJ)->type] ((OBJ), (GRAPHIC)))

#define get_ui_object_zoomable_palette_graphic(OBJ) (fn_get_ui_object_zoomable_palette_graphic [(OBJ)->type] ((OBJ)))

#define set_ui_object_graphic_type(OBJ,FLAG) (fn_set_ui_object_graphic_type [(OBJ)->type] ((OBJ), (FLAG)))

#define get_ui_object_graphic_type(OBJ) (fn_get_ui_object_graphic_type [(OBJ)->type] ((OBJ)))

#define set_ui_object_graphic_zoom(OBJ,ZOOM) (fn_set_ui_object_graphic_zoom [(OBJ)->type] ((OBJ), (ZOOM)))

#define get_ui_object_graphic_zoom(OBJ) (fn_get_ui_object_graphic_zoom [(OBJ)->type] ((OBJ)))
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
