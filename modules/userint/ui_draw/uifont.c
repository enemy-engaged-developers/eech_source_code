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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "userint.h"

#include "graphics.h"

#include "misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define FONT_ROW			5

#define FONT_COLUMN		26

#define LETTER_SPACING	2

#define UNDEFINED_CHAR	255

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char
	font_index_table [] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', ',', ':', ';', '\\','/', '_', '-', '+', '*', '%', '!', '(', ')', '\'', '?',
		'Ä', 'Ö', 'Ü', 'ß', 'ä', 'ö', 'ü', '>', '<', ' ', '¿', 'À', 'Á', 'Â', 'Ã', 'Ç', 'È', 'É', 'Ê', 'Ì', 'Í', 'Î', 'Ñ', 'Ò', 'Ó', 'Ô',
		'Õ', 'Ù', 'Ú', 'Û', 'Ý', 'à', 'á', 'â', 'ã', 'ç', 'è', 'é', 'ê', 'ë', 'ì', 'í', 'î', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ù', 'ú', 'û', 'ý'
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_font_type
	*current_font = NULL,
	**font_list_table = NULL,
	*font_list = NULL;

int
	font_list_table_size;

rgb_colour
	ui_default_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char
	font_lookup_array [256];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void setup_font_index (void);

static int blank_column (unsigned char *this_column, int pitch, int height);

static int blank_row (unsigned char *this_row, int pitch);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ui_font (void)
{

	font_list = NULL;

	font_list_table_size = 10;

	font_list_table = (ui_font_type **) safe_malloc (sizeof (ui_font_type *) * font_list_table_size);

	memset (font_list_table, 0, sizeof (ui_font_type *) * font_list_table_size);

	setup_font_index ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_ui_font (unsigned char *font_data, int font_id)
{

	int
		scan,
		loop,
		loop_row,
		loop_column,
		font_loop,
		last_non_blank_row,
		last_non_blank_column;

	unsigned char
		*current_alpha = nullptr;

	unsigned short int
		*current_char = nullptr;

	ui_font_type
		*new_font = nullptr;

	font_loop = 0;

	last_non_blank_row = 0;

	last_non_blank_column = 0;

	//
	// malloc font array and add to list.
	//

	new_font = (ui_font_type *) safe_malloc (sizeof (ui_font_type));

	new_font->letter_data = (ui_font_letter_type *) safe_malloc (sizeof (ui_font_letter_type) * FONT_ROW * FONT_COLUMN);

	new_font->font_id = font_id;

	new_font->next = font_list;

	font_list = new_font;

	//
	// add to font list table for quick searching
	//

	if (font_id > font_list_table_size)
	{

		ui_font_type
			**new_font_list_table;

		new_font_list_table = (ui_font_type **) safe_malloc (sizeof (ui_font_type *) * font_id * 2);

		memset (new_font_list_table, 0, sizeof (ui_font_type *) * font_id * 2);

		memcpy (new_font_list_table, font_list_table, font_list_table_size);

		font_list_table_size = font_id * 2;

		safe_free (font_list_table);

		font_list_table = new_font_list_table;
	}

	font_list_table [font_id] = new_font;

	//
	// calculate letter size
	//

	new_font->font_pitch = get_list_item (font_data, unsigned short int);

	new_font->font_width = new_font->font_pitch / FONT_COLUMN;

	new_font->font_height = get_list_item (font_data, unsigned short int) / FONT_ROW;

	//
	// loop for all letters
	//

	for (loop_row = 0; loop_row < FONT_ROW; loop_row ++)
	{

		//
		// set letter pointers
		//

		current_char = (unsigned short int *) font_data + (loop_row * new_font->font_height * new_font->font_pitch);

		current_alpha = (unsigned char *) font_data + ((FONT_ROW * new_font->font_height * (new_font->font_pitch * 2)) + (loop_row * new_font->font_height * new_font->font_pitch));

		for (loop_column = 0; loop_column < FONT_COLUMN; loop_column ++)
		{
		
	  		//
			// work out actual letter width for spacing
			//

			last_non_blank_column = 0;
		
			for (scan = 0; scan < new_font->font_width; scan ++)
			{
		
				if (!blank_column (current_alpha + scan, new_font->font_pitch, new_font->font_height))
				{
		
					last_non_blank_column = scan;
				}
			}

			//
			// assign letter pointers with width and height
			//
		
			new_font->letter_data [font_loop].letter_ptr = current_char;

			new_font->letter_data [font_loop].alpha_ptr = current_alpha;
		
			new_font->letter_data [font_loop].width = last_non_blank_column + LETTER_SPACING;

			font_loop ++;

			current_char += new_font->font_width;

			current_alpha += new_font->font_width;
		}
	}

	//
	// Work out baseline
	//

	current_alpha = (unsigned char *) font_data + (FONT_ROW * new_font->font_height * (new_font->font_pitch * 2));

	for (scan = 0; scan < new_font->font_height; scan ++)
	{
		
		if (!blank_row (current_alpha + (scan * new_font->font_pitch), new_font->font_pitch))
		{

			last_non_blank_row = scan;
		}
	}

	new_font->baseline = last_non_blank_row;

	//
	// correct width for special chars
	//

	// space

	for (loop = 0; loop < sizeof (font_index_table); loop ++)
	{

		if (font_index_table [loop] == ' ')
		{

			new_font->letter_data [loop].width = new_font->font_width / 3;
		}
	}

	current_font = new_font;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ui_font (void)
{

	ui_font_type
		*destroy_font = nullptr;

	while (font_list)
	{

		destroy_font = font_list;

		font_list = font_list->next;

		safe_free (destroy_font->letter_data);

		safe_free (destroy_font);
	}

	safe_free (font_list_table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_font_index (void)
{

	int
		loop;

	//
	// set whole array to undefined
	//

	for (loop = 0; loop < 256; loop ++)
	{

		font_lookup_array [loop] = UNDEFINED_CHAR;
	}

	//
	// over write any chars we have graphics for
	//

	for (loop = 0; loop < sizeof (font_index_table); loop ++)
	{

		font_lookup_array [font_index_table[loop]] = loop;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blank_column (unsigned char *this_column, int pitch, int height)
{

	int
		loop,
		blank_flag = TRUE;

	//
	// check vertical stripe for any pixels
	//

	for (loop = 0; loop < height; loop ++)
	{

		if (*(this_column + (pitch * loop)) != 255)
		{

			blank_flag = FALSE;
		}
	}

	return blank_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int blank_row (unsigned char *this_row, int pitch)
{

	int
		loop,
		blank_flag = TRUE;

	//
	// check horizontal stripe for any pixels
	//

	for (loop = 0; loop < pitch; loop ++)
	{

		if (*(this_row + loop) != 255)
		{

			blank_flag = FALSE;
		}
	}

	return blank_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float ui_display_text (char *text, float x, float y)
{

	int
		int_x,
		int_y,
		int_width,
		int_height;

	float
		ox,
		oy,
		float_font_width;

	int
		index,
		loop_string,
		loop_height,
		font_pitch,
		pitch;

	float
		char_end_x,
		char_end_y,
		char_start_x,
		char_start_y,
		original_x_position;

	float
		char_width,
		char_height;

	unsigned char
		*this_alpha_ptr = nullptr,
		*text_ptr = nullptr;

	unsigned short int
		*this_char_ptr = nullptr,
		*screen_ptr = nullptr;

	if (!text)
	{

		return 0;
	}

	ASSERT ( active_screen->pixel_length <= 16 );

	//
	// setup stuff
	//

	x += ui_x_origin;

	y += ui_y_origin;

	original_x_position = x;

	text_ptr = text;

	//
	// loop the whole string
	//
	
	for (loop_string = strlen (text); loop_string > 0; loop_string --)
	{

		//
		// work out what char
		//

		index = font_lookup_array [*text_ptr];

		if (index == UNDEFINED_CHAR)
		{

			if (*text_ptr == 10)
			{

				y += ui_get_font_height ();

				x = original_x_position;
			}

			text_ptr ++;

			continue;
		}

		//
		// starting position for char in viewport coords
		//

		char_start_x = x;
	
		char_start_y = y;
	
  		//
  		// calculate end of char in viewport coords
		//

		char_end_x = char_start_x + current_font->letter_data [index].width;

		char_end_y = char_start_y + current_font->font_height;

		//
		// check if char is even on the screen
		//

		if ((char_end_x < active_viewport.x_min) || (x > active_viewport.x_max))
		{

			x += current_font->letter_data [index].width;

			text_ptr ++;

			continue;
		}

		if ((char_end_y < active_viewport.y_min) || (char_start_y > active_viewport.y_max))
		{

			continue;
		}

		//
		// clip char area wrt ui viewport
		//

		ox = ui_x_origin;

		oy = ui_y_origin;

		ui_set_origin (0, 0);

		ui_clip_area (&char_start_x, &char_start_y, &char_end_x, &char_end_y);

		ui_set_origin (ox, oy);

		//
		// calculate dimensions of new char
		//

		char_width = char_end_x - char_start_x;

		char_height = char_end_y - char_start_y;

		//
		// store some variables in alternative types for speed
		//

		convert_float_to_int (char_width, &int_width);

		convert_float_to_int (char_height, &int_height);

		float_font_width = (float) current_font->letter_data [index].width;

		convert_float_to_int (char_start_y - y, &int_y);

		convert_float_to_int (char_start_x - x, &int_x);

		//
		// get pointer for clipped char area
		//

		font_pitch = current_font->font_pitch;

		this_char_ptr = current_font->letter_data [index].letter_ptr + (font_pitch * int_y) + int_x;

		this_alpha_ptr = current_font->letter_data [index].alpha_ptr + (font_pitch * int_y) + int_x;

		//
		// loop new sized char and draw it
		//

		pitch = get_screen_pitch (active_screen) / 2;

		screen_ptr = (unsigned short int *) get_screen_data (active_screen);

		convert_float_to_int (char_start_y, &int_y);

		screen_ptr += (int_y * pitch);

		convert_float_to_int (char_start_x, &int_x);

		for (loop_height = int_height; loop_height > 0; loop_height --)
		{

			int
				loop_width;

			unsigned short int
				*line_ptr = nullptr;

			line_ptr = (unsigned short int *) screen_ptr + int_x;

			for (loop_width = 0; loop_width < int_width; loop_width ++)
			{
	
  				//
  				// plot pixel according to 8bit alpha mask
				//

				if (*this_alpha_ptr < 248)
				{

					if (*this_alpha_ptr > 8 )
					{
	
						rgb_colour
							this_colour,
							text_colour,
							result_colour;
	
						float
							dr,
							dg,
							db,
							alpha_factor;
	
						int
							ir,
							ig,
							ib;
	
						this_colour = get_rgb_colour_value (*line_ptr);
						text_colour = get_rgb_colour_value (*this_char_ptr);
	
						alpha_factor = ((float) (*this_alpha_ptr)) / 255.0;
	
						dr = this_colour.r - text_colour.r;
						dg = this_colour.g - text_colour.g;
						db = this_colour.b - text_colour.b;
	
						dr = ( dr * alpha_factor ) + FLOAT_FLOAT_FACTOR;
						dg = ( dg * alpha_factor ) + FLOAT_FLOAT_FACTOR;
						db = ( db * alpha_factor ) + FLOAT_FLOAT_FACTOR;
	
						ir = ( *( ( int * ) &dr ) - INTEGER_FLOAT_FACTOR );
						ig = ( *( ( int * ) &dg ) - INTEGER_FLOAT_FACTOR );
						ib = ( *( ( int * ) &db ) - INTEGER_FLOAT_FACTOR );
	
						result_colour.r = text_colour.r + ir;	//(dr * alpha_factor);
						result_colour.g = text_colour.g + ig;	//(dg * alpha_factor);
						result_colour.b = text_colour.b + ib;	//(db * alpha_factor);
	
						*line_ptr = get_rgb_packed_value (result_colour);
					}
					else
					{

						*line_ptr = *this_char_ptr;
					}
				}

				line_ptr ++;

				this_char_ptr ++;

				this_alpha_ptr ++;
			}

			screen_ptr += pitch;

			this_char_ptr += (font_pitch - int_width);

			this_alpha_ptr += (font_pitch - int_width);
		}

		//
		// move cursor along width of last char and next char
		//

		x += float_font_width;

		text_ptr ++;
	}

	//
	// return the length in pixels of the text written to screen
	//

	return (x - original_x_position);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float ui_get_string_length (char *string)
{

	int
		length = 0,
		index;

	char
		*current_char = nullptr;

	if (!string)
	{

		return 0;
	}

	current_char = string;

	//
	// spin along string adding up length in pixels
	//

	while (*current_char)
	{

		index = font_lookup_array [*current_char];

		if (index == UNDEFINED_CHAR)
		{

			current_char ++;

			continue;
		}

		length += current_font->letter_data [index].width;

		current_char ++;
	}

	return length;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ui_display_centred_text (char *text, float x1, float x2, float y1, float y2)
{

	float
		length;

	int
		height,
		y_centre,
		x_start_int,
		x_end_int;

	length = ui_get_string_length (text);

	height = ui_get_font_height ();

	convert_float_to_int ((x2 - x1 - length), &x_start_int);

	x_start_int = x_start_int >> 1;

	convert_float_to_int ((x2 - x1 + length), &x_end_int);

	x_end_int = x_end_int >> 1;

	x_start_int += x1;

	x_end_int += x1;

	convert_float_to_int ((y2 - y1 - height), &y_centre);

	y_centre = y_centre >> 1;

	y_centre += y1;

	ui_display_text (text, x_start_int, y_centre);

	return (x_end_int);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0

float ui_display_highlighted_text (char *text, float x, float y)
{

	int
		int_x,
		int_y,
		int_width,
		int_height;

	float
		float_font_width;

	int
		index,
		loop_string,
		loop_height,
		font_pitch,
		pitch;

	float
		char_end_x,
		char_end_y,
		char_start_x,
		char_start_y,
		original_x_position;

	float
		char_width,
		char_height;

	char
		*text_ptr = nullptr;

	unsigned short int
		*this_char_ptr = nullptr;

	unsigned char
		*screen_ptr = nullptr;

	unsigned short int
		colour_value;

	// setup stuff

	original_x_position = x;

	text_ptr = text;

	// loop whole string

	for (loop_string = strlen (text); loop_string > 0; loop_string --)
	{

		// work out what char

		index = font_lookup_array [*text_ptr];

		if (index == UNDEFINED_CHAR)
		{

			text_ptr ++;

			continue;
		}

		// starting position for char in viewport coords

		char_start_x = x;
	
		char_start_y = y;
	
  		// calculate end of char in viewport coords

		char_end_x = char_start_x + current_font->letter_data [index].width;

		char_end_y = char_start_y + current_font->font_height;

		// check if char is even on the screen

		if ((char_end_x < active_viewport.x_min - ui_x_origin) || (x > active_viewport.x_max - ui_x_origin))
		{

			x += current_font->letter_data [index].width;

			text_ptr ++;

			continue;
		}

		if ((char_end_y < active_viewport.y_min - ui_y_origin) || (char_start_y > active_viewport.y_max - ui_y_origin))
		{

			continue;
		}

		// clip char area wrt ui viewport

		ui_clip_area (&char_start_x, &char_start_y, &char_end_x, &char_end_y);
	
		// calculate dimensions of new char

		char_width = char_end_x - char_start_x;

		char_height = char_end_y - char_start_y;

		// store some variables in alternative types for speed

		convert_float_to_int (char_width, &int_width);

		convert_float_to_int (char_height, &int_height);

		float_font_width = (float) current_font->letter_data [index].width;

		convert_float_to_int (char_start_y - y, &int_y);

		convert_float_to_int (char_start_x - x, &int_x);

		// get pointer for clipped char area
		font_pitch = current_font->font_pitch;

		this_char_ptr = current_font->letter_data [index].letter_ptr +
								(font_pitch * int_y) + int_x;

		// loop new sized char and draw it

		char_start_x += ui_x_origin;

		char_start_y += ui_y_origin;

		colour_value = get_rgb_packed_value (highlight_colour);

		pitch = get_screen_pitch (active_screen);

		screen_ptr = get_screen_data (active_screen);

		convert_float_to_int (char_start_y * pitch, &int_y);

		screen_ptr += int_y;

		convert_float_to_int (char_start_x, &int_x);

		set_block (char_start_x - 1, char_start_y - 1, char_end_x + 1, char_end_y + 1, font_colour);

		for (loop_height = int_height; loop_height > 0; loop_height --)
		{

			int
				loop_width;

			unsigned short int
				*line_ptr = nullptr;

			line_ptr = (unsigned short int *) screen_ptr + int_x;

			for (loop_width = 0; loop_width < int_width; loop_width ++)
			{
	
  				// plot pixel according to 8bit mask

				if (*this_char_ptr)
				{

					*line_ptr = colour_value;
				}

				line_ptr ++;

				this_char_ptr ++;
			}

			screen_ptr += pitch;

			this_char_ptr += (font_pitch - int_width);
		}

		// move cursor along width of last char

		x += float_font_width;

		// now next char

		text_ptr ++;
	}

	// return the length in pixels of the text written to screen

	return (x - original_x_position);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_font (int font_id)
{
/*
	ui_font_type
		*this_font = nullptr;

	this_font = font_list;

	while (this_font)
	{

		if (this_font->font_id == font_id)
		{

			current_font = this_font;

			return;
		}

		this_font = this_font->next;
	}

	debug_fatal ("UI_FONT: unknown font id %d", font_id);
*/
	current_font = font_list_table [font_id];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_ui_font (void)
{

	return current_font->font_id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
