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

extern void (*fn_set_ui_object_text [NUM_UI_TYPES]) (ui_object *obj, const char *text);

extern const char *(*fn_get_ui_object_text [NUM_UI_TYPES]) (ui_object *obj);


extern void (*fn_set_ui_object_add_text [NUM_UI_TYPES]) (ui_object *obj, const char *text);


extern void (*fn_set_ui_object_text_justify [NUM_UI_TYPES]) (ui_object *obj, text_justify_types justify);

extern text_justify_types (*fn_get_ui_object_text_justify [NUM_UI_TYPES]) (ui_object *obj);


extern void (*fn_set_ui_object_font_type [NUM_UI_TYPES]) (ui_object *obj, int font_id);

extern int (*fn_get_ui_object_font_type [NUM_UI_TYPES]) (ui_object *obj);


extern void (*fn_set_ui_object_font_colour [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
extern void (*fn_set_ui_object_font_colour_end [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
extern void (*fn_set_ui_object_font_colour_start [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);

extern rgb_colour (*fn_get_ui_object_font_colour [NUM_UI_TYPES]) (ui_object *obj);
extern rgb_colour (*fn_get_ui_object_font_colour_end [NUM_UI_TYPES]) (ui_object *obj);
extern rgb_colour (*fn_get_ui_object_font_colour_start [NUM_UI_TYPES]) (ui_object *obj);


extern void (*fn_set_ui_object_highlighted_font_type [NUM_UI_TYPES]) (ui_object *obj, int font_id);

extern int (*fn_get_ui_object_highlighted_font_type [NUM_UI_TYPES]) (ui_object *obj);


extern void (*fn_set_ui_object_highlighted_font_colour [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
extern void (*fn_set_ui_object_highlighted_font_colour_end [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
extern void (*fn_set_ui_object_highlighted_font_colour_start [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);

extern rgb_colour (*fn_get_ui_object_highlighted_font_colour [NUM_UI_TYPES]) (ui_object *obj);
extern rgb_colour (*fn_get_ui_object_highlighted_font_colour_end [NUM_UI_TYPES]) (ui_object *obj);
extern rgb_colour (*fn_get_ui_object_highlighted_font_colour_start [NUM_UI_TYPES]) (ui_object *obj);


extern void (*fn_set_ui_object_selected_font_type [NUM_UI_TYPES]) (ui_object *obj, int font_id);

extern int (*fn_get_ui_object_selected_font_type [NUM_UI_TYPES]) (ui_object *obj);


extern void (*fn_set_ui_object_selected_font_colour [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
extern void (*fn_set_ui_object_selected_font_colour_end [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);
extern void (*fn_set_ui_object_selected_font_colour_start [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, char alpha);

extern rgb_colour (*fn_get_ui_object_selected_font_colour [NUM_UI_TYPES]) (ui_object *obj);
extern rgb_colour (*fn_get_ui_object_selected_font_colour_end [NUM_UI_TYPES]) (ui_object *obj);
extern rgb_colour (*fn_get_ui_object_selected_font_colour_start [NUM_UI_TYPES]) (ui_object *obj);


extern void (*fn_set_ui_object_tool_tips [NUM_UI_TYPES]) (ui_object *obj, const char *tool_tips);

extern const char *(*fn_get_ui_object_tool_tips [NUM_UI_TYPES]) (ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void default_set_ui_object_text (ui_object *obj, const char *text);

extern const char *default_get_ui_object_text (ui_object *obj);


extern void default_set_ui_object_add_text (ui_object *obj, const char *text);


extern void default_set_ui_object_text_justify (ui_object *obj, text_justify_types justify);

extern text_justify_types default_get_ui_object_text_justify (ui_object *obj);


extern void default_set_ui_object_font_type (ui_object *obj, int font_id);

extern int default_get_ui_object_font_type (ui_object *obj);


extern void default_set_ui_object_font_colour (ui_object *obj, char red, char green, char blue, char alpha);
extern void default_set_ui_object_font_colour_end (ui_object *obj, char red, char green, char blue, char alpha);
extern void default_set_ui_object_font_colour_start (ui_object *obj, char red, char green, char blue, char alpha);

extern rgb_colour default_get_ui_object_font_colour (ui_object *obj);
extern rgb_colour default_get_ui_object_font_colour_end (ui_object *obj);
extern rgb_colour default_get_ui_object_font_colour_start (ui_object *obj);


extern void default_set_ui_object_highlighted_font_type (ui_object *obj, int font_id);

extern int default_get_ui_object_highlighted_font_type (ui_object *obj);

extern void default_set_ui_object_highlighted_font_colour (ui_object *obj, char red, char green, char blue, char alpha);
extern void default_set_ui_object_highlighted_font_colour_end (ui_object *obj, char red, char green, char blue, char alpha);
extern void default_set_ui_object_highlighted_font_colour_start (ui_object *obj, char red, char green, char blue, char alpha);

extern rgb_colour default_get_ui_object_highlighted_font_colour (ui_object *obj);
extern rgb_colour default_get_ui_object_highlighted_font_colour_end (ui_object *obj);
extern rgb_colour default_get_ui_object_highlighted_font_colour_start (ui_object *obj);


extern void default_set_ui_object_selected_font_type (ui_object *obj, int font_id);

extern int default_get_ui_object_selected_font_type (ui_object *obj);

extern void default_set_ui_object_selected_font_colour (ui_object *obj, char red, char green, char blue, char alpha);
extern void default_set_ui_object_selected_font_colour_end (ui_object *obj, char red, char green, char blue, char alpha);
extern void default_set_ui_object_selected_font_colour_start (ui_object *obj, char red, char green, char blue, char alpha);

extern rgb_colour default_get_ui_object_selected_font_colour (ui_object *obj);
extern rgb_colour default_get_ui_object_selected_font_colour_end (ui_object *obj);
extern rgb_colour default_get_ui_object_selected_font_colour_start (ui_object *obj);


extern void default_set_ui_object_tool_tips (ui_object *obj, char *tool_tips);

extern const char *default_get_ui_object_tool_tips (ui_object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_ui_object_text_default_functions (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define set_ui_object_text(OBJ,TEXT) (fn_set_ui_object_text [(OBJ)->type] ((OBJ), (TEXT)))

#define get_ui_object_text(OBJ) (fn_get_ui_object_text [(OBJ)->type] ((OBJ)))


#define set_ui_object_add_text(OBJ,TEXT) (fn_set_ui_object_add_text [(OBJ)->type] ((OBJ), (TEXT)))


#define set_ui_object_text_justify(OBJ,JUSTIFY) (fn_set_ui_object_text_justify [(OBJ)->type] ((OBJ), (JUSTIFY)))

#define get_ui_object_text_justify(OBJ) (fn_get_ui_object_text_justify [(OBJ)->type] ((OBJ)))


#define set_ui_object_font_type(OBJ,FONT_ID) (fn_set_ui_object_font_type [(OBJ)->type] ((OBJ), (FONT_ID)))

#define get_ui_object_font_type(OBJ) (fn_get_ui_object_font_type [(OBJ)->type] ((OBJ)))


#define set_ui_object_font_colour(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_font_colour [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))
#define set_ui_object_font_colour_end(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_font_colour_end [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))
#define set_ui_object_font_colour_start(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_font_colour_start [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))

#define get_ui_object_font_colour(OBJ) (fn_get_ui_object_font_colour [(OBJ)->type] ((OBJ)))
#define get_ui_object_font_colour_end(OBJ) (fn_get_ui_object_font_colour_end [(OBJ)->type] ((OBJ)))
#define get_ui_object_font_colour_start(OBJ) (fn_get_ui_object_font_colour_start [(OBJ)->type] ((OBJ)))


#define set_ui_object_highlighted_font_type(OBJ,FONT_ID) (fn_set_ui_object_highlighted_font_type [(OBJ)->type] ((OBJ), (FONT_ID)))

#define get_ui_object_highlighted_font_type(OBJ) (fn_get_ui_object_highlighted_font_type [(OBJ)->type] ((OBJ)))


#define set_ui_object_highlighted_font_colour(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_highlighted_font_colour [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))
#define set_ui_object_highlighted_font_colour_end(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_highlighted_font_colour_end [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))
#define set_ui_object_highlighted_font_colour_start(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_highlighted_font_colour_start [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))

#define get_ui_object_highlighted_font_colour(OBJ) (fn_get_ui_object_highlighted_font_colour [(OBJ)->type] ((OBJ)))
#define get_ui_object_highlighted_font_colour_end(OBJ) (fn_get_ui_object_highlighted_font_colour_end [(OBJ)->type] ((OBJ)))
#define get_ui_object_highlighted_font_colour_start(OBJ) (fn_get_ui_object_highlighted_font_colour_start [(OBJ)->type] ((OBJ)))


#define set_ui_object_selected_font_type(OBJ,FONT_ID) (fn_set_ui_object_selected_font_type [(OBJ)->type] ((OBJ), (FONT_ID)))

#define get_ui_object_selected_font_type(OBJ) (fn_get_ui_object_selected_font_type [(OBJ)->type] ((OBJ)))


#define set_ui_object_selected_font_colour(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_selected_font_colour [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))
#define set_ui_object_selected_font_colour_end(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_selected_font_colour_end [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))
#define set_ui_object_selected_font_colour_start(OBJ,RED,GREEN,BLUE,ALPHA) (fn_set_ui_object_selected_font_colour_start [(OBJ)->type] ((OBJ), (RED), (GREEN), (BLUE), (ALPHA)))

#define get_ui_object_selected_font_colour(OBJ) (fn_get_ui_object_selected_font_colour [(OBJ)->type] ((OBJ)))
#define get_ui_object_selected_font_colour_end(OBJ) (fn_get_ui_object_selected_font_colour_end [(OBJ)->type] ((OBJ)))
#define get_ui_object_selected_font_colour_start(OBJ) (fn_get_ui_object_selected_font_colour_start [(OBJ)->type] ((OBJ)))


#define set_ui_object_tool_tips(OBJ,TOOL_TIPS) (fn_set_ui_object_tool_tips [(OBJ)->type] ((OBJ), (TOOL_TIPS)))

#define get_ui_object_tool_tips(OBJ) (fn_get_ui_object_tool_tips [(OBJ)->type] ((OBJ)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
