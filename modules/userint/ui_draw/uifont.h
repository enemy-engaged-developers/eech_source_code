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

enum    FONT_TYPES
{

        UI_FONT_ARIAL_22,
        UI_FONT_ARIAL_22_BLACK,
        UI_FONT_ARIAL_22_DARK_GREY,
        UI_FONT_ARIAL_22_BLUE,
        UI_FONT_ARIAL_22_GREEN,
        UI_FONT_ARIAL_22_ORANGE,
        UI_FONT_ARIAL_22_RED,
        UI_FONT_ARIAL_22_YELLOW,
        UI_FONT_ARIAL_15_RED,
        UI_FONT_ARIAL_15_BLUE,
        UI_FONT_ARIAL_15_WHITE,
        UI_FONT_ARIAL_15_YELLOW,
        UI_FONT_ARIAL_15_GREY,
        UI_FONT_ARIAL_15_ORANGE,
        UI_FONT_ARIAL_15_GREEN,
        UI_FONT_ARIAL_11,
        UI_FONT_ARIAL_11_BLACK,
        UI_FONT_ARIAL_11_DARK_GREY,
        UI_FONT_ARIAL_11_BLUE,
        UI_FONT_ARIAL_11_GREEN,
        UI_FONT_ARIAL_11_GREY,
        UI_FONT_ARIAL_11_ORANGE,
        UI_FONT_ARIAL_11_RED,
        UI_FONT_ARIAL_11_YELLOW,
        UI_FONT_ADS_11_WHITE,
        UI_FONT_ADS_11_YELLOW,
        UI_FONT_ADS_11_GREY,
        UI_FONT_ADS_11_BLUE,
        UI_FONT_ADS_11_ORANGE,
        UI_FONT_ADS_15_WHITE,
        UI_FONT_ADS_15_YELLOW,
        UI_FONT_ADS_15_BLUE,
        UI_FONT_ADS_15_ORANGE,
        UI_FONT_ADS_22_WHITE,
        UI_FONT_ADS_22_YELLOW,
        UI_FONT_ADS_22_BLUE,
        UI_FONT_ADS_22_ORANGE,
        UI_FONT_MONO_7,
        UI_FONT_ARIAL_8_WHITE,
        UI_FONT_ARIAL_8_YELLOW,
};

typedef enum FONT_TYPES font_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern struct UI_FONT_TYPE
        *current_font;

extern rgb_colour
        ui_default_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_ui_font (void);

extern void load_ui_font (unsigned char *font_data, int font_id);

extern void deinitialise_ui_font (void);

extern float ui_display_text (const char *text, float x, float y);

extern float ui_get_string_length (const char *string);

extern int ui_display_centred_text (const char *text, float x1, float x2, float y1, float y2);

//extern float ui_display_highlighted_text (const char *text, float x, float y);

extern void set_ui_font (int font_id);

extern int get_ui_font (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ui_get_font_height() (current_font->font_height)

#define ui_get_font_width() (current_font->font_width)

#define ui_get_font_baseline() (current_font->baseline)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
