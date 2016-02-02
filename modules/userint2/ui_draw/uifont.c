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

#include "userint2.h"

#ifndef OGRE_EE
#include "graphics.h"

#include "misc.h"

#include "3d.h"


#define UNICODE 1

//
// For the russian version (Remake and generate correct fonts if changed)
//
//if these are set to 1 then in combination with the language setting in the registry
//the font is set to cyrillic. If set to 1 and language in the registry is set to english the user
//may or may not get a "create font returned null [120]" error, depending on his list of fonts I guess
//050311 Lines above added by VJ
////050311 Next line modded by Moje. A space was added before 0
#define RUSSIAN_VERSION 0

#define POLISH_VERSION  0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UI_FONT_WINDOWS_TEXTURE_WIDTH_GAP 1

#define UI_FONT_WINDOWS_TEXTURE_HEIGHT_GAP 1

#define UI_FONT_HEADER_FILE "fonts\\fontbase.dat"

#define UI_FONT_DATA_FILE "fonts\\fontdata.dat"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FONT_DATABASE_HEADER
{

	char
		type_name[128];

	int
		font_character_maximum_width,
		font_character_maximum_height,
		font_source_height,
		font_source_width,
		font_italics,
		number_of_kerning_pairs;

	float
		font_source_weight;

	int
		kerning_data_offset,
		graphic_data_offset;
};

typedef struct FONT_DATABASE_HEADER font_database_header;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// The source file is in Latin-1 encoding. Here it is the same as UTF-8.

#if ( POLISH_VERSION )

unsigned char
	font_character_table [] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', ',', ':', ';', '\\','/', '_', '-', '+', '*', '%', '!', '(', ')', '\'', '?',
		'Ä', 'Ö', 'Ü', 'ß', 'ä', 'ö', 'ü', '>', '<', ' ', '¿', 'À', 'Á', 'Â', 'Ã', 'Ç', 'È', 'É', 'Ê', 'Ì', 'Í', 'Î', 'Ñ', 'Ò', 'Ó', 'Ô',
		'Õ', 'Ù', 'Ú', 'Û', 'Ý', 'à', 'á', 'â', 'ã', 'ç', 'è', 'é', 'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ù', 'ú', 'û',
		'ý', '#', '[', ']', '=', 'œ', '\"', '£', '$', '^', '&', '{', '}', '©',
		126, 127, 128, 129, 130, 131, 132, 133,
		134, 135, 136, 137, 138, 139, 140, 141,
	};

unsigned int
	unicode_character_table[] =
	{
		0x00000179, 0x00000106, 0x00000143, 0x00000141, 0x0000017b, 0x00000118, 0x00002026, 0x0000017c,
		0x00000144, 0x0000017a, 0x00000107, 0x00000119, 0x0000015a, 0x00000142, 0x00000105, 0x0000015b
	};

#else

unsigned char
	font_character_table [] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', ',', ':', ';', '\\','/', '_', '-', '+', '*', '%', '!', '(', ')', '\'', '?',
		'Ä', 'Ö', 'Ü', 'ß', 'ä', 'ö', 'ü', '>', '<', ' ', '¿', 'À', 'Á', 'Â', 'Ã', 'Ç', 'È', 'É', 'Ê', 'Ì', 'Í', 'Î', 'Ñ', 'Ò', 'Ó', 'Ô',
		'Õ', 'Ù', 'Ú', 'Û', 'Ý', 'à', 'á', 'â', 'ã', 'ç', 'è', 'é', 'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ù', 'ú', 'û', 'ý',
		'#', '[', ']', '=', 'œ', '\"', '£', '$', '^', '&', '{', '}', 222,
		255,
		126, 127, 128, 129, 130, 131, 132, 133,
		134, 135, 136, 137, 138, 139, 140, 141,
		142, 143, 144, 145, 146, 147, 148, 149,
		150, 151, 152, 153, 154, 155, 156, 157,
		158, 159, 160, 161, 162, 163, 164, 165,
		166, 167, 168, 169, 170, 171, 172, 173,
		174, 175, 176, 177, 178, 179, 180, 181,
		182, 183, 184, 185, 186, 187, 188, 189,
		190,
	};

unsigned int
	unicode_character_table[] =
	{
		0x00000425, 0x00000427, 0x0000044a, 0x00000426, 0x00000428, 0x00000424, 0x0000042d, 0x00000419,
		0x0000042b, 0x0000042f, 0x00000416, 0x0000044d, 0x00000449, 0x00000448, 0x00000445, 0x00000423,
		0x00000420, 0x00000415, 0x0000042c, 0x00000422, 0x00000410, 0x0000041b, 0x0000041a, 0x0000041c,
		0x0000041f, 0x00000411, 0x0000044e, 0x00000446, 0x00000418, 0x0000043c, 0x00000421, 0x00000431,
		0x0000041e, 0x00000439, 0x00000436, 0x00000414, 0x0000044b, 0x00000413, 0x00000444, 0x00000432,
		0x00000442, 0x00000434, 0x0000043e, 0x0000043f, 0x0000043d, 0x0000044c, 0x0000043b, 0x00000447,
		0x0000041d, 0x0000044f, 0x00000438, 0x00000441, 0x00000435, 0x00000412, 0x0000043a, 0x00000437,
		0x00000443, 0x00000440, 0x00000433, 0x00000430, 0x00000417, 0x00002026, 0x0000feff, 0x0000042e,
		0x00000451
	};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

ui_font_type
	ui_fonts[NUM_FONT_TYPES];

ui_font_type
	*current_font = NULL;

static font_types
	store_font,
	current_font_type = NUM_FONT_TYPES;

static rgb_colour
	store_colour,
	current_font_colour;

rgb_colour
	ui_default_colour;

#ifndef OGRE_EE
rgb_colour
	ui_white_colour,
	ui_black_colour,
	ui_grey_colour,
	ui_blue_colour,
	ui_green_colour,
	ui_orange_colour,
	ui_red_colour,
	ui_yellow_colour;

static int
	current_font_resolution_width = 640,
	current_font_resolution_height = 480;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef UNICODE
static char
	unicode_table[256][2];
static int
	unicode_table_filled;

char* string_to_utf8(const char* str)
{
	if (!unicode_table_filled)
	{
		unsigned
			count;

		wchar_t
			ch, rp;

		for (count = 0; count < 256; count++)
		{
			unicode_table[count][0] = '~';
			unicode_table[count][1] = '\0';
		}
		for (count = 0; count < ARRAYSIZE(font_character_table); count++)
		{
			ch = font_character_table[count];
			rp = ch >= 126 && ch <= 190 ? unicode_character_table[ch - 126] : ch == 255 ? 0xA9 : ch;
			if (rp >= FONT_CHARACTERS)
				rp = ' ';
			if (rp < 0x80)
			{
				unicode_table[ch][0] = (char) rp;
				unicode_table[ch][1] = 0;
			}
			else
			{
				unicode_table[ch][0] = (char) (0xC0 | (rp >> 6));
				unicode_table[ch][1] = (char) (0x80 | (rp & 0x3F));
			}
		}
		unicode_table_filled = 1;
	}

	{
		size_t
			len;

		const char
			*src;

		char
			*dst,
			*ptr;

		len = 0;
		for (src = str; *src; src++)
		{
			len += unicode_table[(unsigned char) *src][1] ? 2 : 1;
		}

		dst = safe_malloc(len + 1);

		for (ptr = dst; *str; str++)
		{
			src = unicode_table[(unsigned char) *str];
			*ptr++ = *src;
			if (src[1])
			{
				*ptr++ = src[1];
			}
		}
		*ptr = '\0';

		return dst;
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void load_windows_ui_font ( font_types font, const char *type_name, int height, int width, float thickness, int italics, int dropshadow );

static int get_kerning_offset ( wchar_t first, wchar_t second );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_font_resolution (int width, int height)
{

	current_font_resolution_width = width;

	current_font_resolution_height = height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reinitialise_ui_fonts (void)
{
		deinitialise_ui_font ();

		initialise_ui_font ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ui_font (void)
{
	int
		x_size,
		y_size;

	float
		arial_factor_x,
		arial_factor_y,
		impact_factor_y,
		res_factor_x,
		res_factor_y,
		unscalable_factor;

	#if DEBUG_MODULE
		debug_log ("UI_FONT: %d %d", current_font_resolution_width, current_font_resolution_height );
	#endif

	unlink ( UI_FONT_HEADER_FILE );
	unlink ( UI_FONT_DATA_FILE );

	memset ( ui_fonts, 0, sizeof ( ui_fonts ) );

	//
	// Initialise the standard font colours
	//

	ui_white_colour.r = 255;
	ui_white_colour.g = 255;
	ui_white_colour.b = 255;
	ui_white_colour.a = 255;

	ui_black_colour.r = 0;
	ui_black_colour.g = 0;
	ui_black_colour.b = 0;
	ui_black_colour.a = 255;

	ui_grey_colour.r = 148;
	ui_grey_colour.g = 148;
	ui_grey_colour.b = 148;
	ui_grey_colour.a = 255;

	ui_blue_colour.r = 0;
	ui_blue_colour.g = 0;
	ui_blue_colour.b = 255;
	ui_blue_colour.a = 255;

	ui_green_colour.r = 0;
	ui_green_colour.g = 255;
	ui_green_colour.b = 0;
	ui_green_colour.a = 255;

	ui_orange_colour.r = 255;
	ui_orange_colour.g = 128;
	ui_orange_colour.b = 0;
	ui_orange_colour.a = 255;

	ui_red_colour.r = 255;
	ui_red_colour.g = 0;
	ui_red_colour.b = 0;
	ui_red_colour.a = 255;

	ui_yellow_colour.r = 255;
	ui_yellow_colour.g = 255;
	ui_yellow_colour.b = 0;
	ui_yellow_colour.a = 255;

	// Load the arial fonts

// size = p * rf / af

// size = size request to pass to windows
// p = pixel size of font at 640 x 480 resolution
// rf = res factor = new_res width / 640
// af = arial factors are constants for arial typeface - I presume

// to improve:
// find pixel resolution required at high resolution & use to get most accurate size request

// original font scale factors

	arial_factor_x = 0.4;

	arial_factor_y = 0.6;

	impact_factor_y = 0.6;

// resolution factor

	res_factor_x = ((float) current_font_resolution_width) / 640.0;

	res_factor_y = ((float) current_font_resolution_height) / 480.0;

	arial_factor_x = res_factor_x / arial_factor_x;

	arial_factor_y = res_factor_y / arial_factor_y;

	impact_factor_y = res_factor_y / impact_factor_y;

	unscalable_factor = 1.0 / 0.6;

	y_size = (int) round (7 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_ARIAL_10, "Arial", 0, y_size, 0.4, FALSE, TRUE );

	y_size = (int) round (8 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_ARIAL_14, "Arial", 0, y_size, 0.4, FALSE, TRUE );

	y_size = (int) round (8 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_ITALIC_ARIAL_14, "Arial", 0, y_size, 0.4, TRUE, TRUE );

	y_size = (int) round (8.5 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_ARIAL_16, "Arial", 0, y_size, 0.4, FALSE, TRUE );

	y_size = (int) round (8.5 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_ITALIC_ARIAL_16, "Arial", 0, y_size, 0.4, TRUE, TRUE );

	y_size = (int) round (11 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_ARIAL_18, "Arial", 0, y_size, 0.6, FALSE, TRUE );

	y_size = (int) round (11 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_THICK_ARIAL_18, "Arial", 0, y_size, 1.0, FALSE, TRUE );

	y_size = (int) round (11 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_ITALIC_ARIAL_18, "Arial", 0, y_size, UI_FONT_DEFAULT_WEIGHT, TRUE, TRUE );

	y_size = (int) round (11 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_THICK_ITALIC_ARIAL_18, "Arial", 0.0, y_size, 1.0, TRUE, TRUE );

	x_size = (int) round (6 * arial_factor_x);

	y_size = (int) round (11 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_STRETCH_ITALIC_ARIAL_18, "Arial", x_size, y_size, 1.0, TRUE, TRUE );

	y_size = (int) round (14 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_ARIAL_22, "Arial", 0, y_size, UI_FONT_DEFAULT_WEIGHT, FALSE, TRUE );

	x_size = (int) round (7 * arial_factor_x);

	y_size = (int) round (14 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_THICK_ARIAL_22, "Arial", x_size, y_size, 1.0, TRUE, TRUE );

	y_size = (int) round (21 * arial_factor_y);

	load_windows_ui_font ( UI_FONT_IMPACT_22, "Impact", 0.0, y_size, 0.9, TRUE, TRUE );

	y_size = (int) round (8.2 * unscalable_factor);

	load_windows_ui_font ( UI_FONT_UNSCALABLE_10, "Arial", 0, y_size, 0.4, FALSE, TRUE );

	//
	// Set the current font to default
	//

	set_ui_font_type ( UI_FONT_ARIAL_10 );

	set_ui_font_colour ( ui_white_colour );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_windows_ui_font ( font_types font, const char *type_name, int width, int height, float weight, int italics, int dropshadow )
{

	HFONT
		my_font;

	screen
		*old_active_screen;

	int
		screen_index,
		character_count,
		x,
		y;

	unsigned char
		aliased_character[128 * 128],
		glyph_character[128 * 128];

	int
		ithickness,
		count,
		found,
		font_offset,
		number_of_screens,
		finished,
		texture_width,
		texture_height,
		characters_wide,
		characters_high,
		character_x,
		character_y;

	RECT
		rect;

	rgb_colour
		colour;

	ui_font_type
		*new_font;

	screen
		**font_screens;

	GLYPHMETRICS
		metrics;

	MAT2
		mat2;

	HDC
		hdc;

	FILE
		*fp;

	ASSERT ((font >= 0) && (font < NUM_FONT_TYPES));

	new_font = &ui_fonts[font];

	ASSERT ( !new_font->loaded );

	memset ( new_font, 0, sizeof ( ui_font_type ) );

	new_font->loaded = TRUE;

	new_font->type_name = ( char * ) safe_malloc ( strlen ( type_name ) + 1 );

	strcpy ( new_font->type_name, type_name );

	new_font->font_source_height = height;
	new_font->font_source_width = width;
	new_font->font_source_weight = weight;
	new_font->font_italics = italics;
	new_font->font_dropshadow = dropshadow;

	ithickness = ( int ) ( weight * 1000.0 );

	//
	// Attempt to load font from disk
	//

	found = FALSE;

	font_offset = -1;

	if ( file_exist ( UI_FONT_HEADER_FILE ) )
	{

		int
			count,
			number_of_fonts;

		font_database_header
			*font_headers;

		number_of_fonts = file_size ( UI_FONT_HEADER_FILE );

		number_of_fonts /= sizeof ( font_database_header );

		font_headers = ( font_database_header * ) safe_mopen ( UI_FONT_HEADER_FILE );

		for ( count = 0; count < number_of_fonts; count++ )
		{

			if ( stricmp ( font_headers[count].type_name, type_name ) == 0 )
			{

				if (	( font_headers[count].font_source_height == height ) &&
						( font_headers[count].font_source_width == width ) &&
						( font_headers[count].font_source_weight == weight ) &&
						( font_headers[count].font_italics == italics ) )
				{

					found = TRUE;

					font_offset = count;

					break;
				}
			}
		}

		safe_mclose ( font_headers );

		font_headers = NULL;
	}

	if ( !found )
	{

		int
			number_of_kerning_pairs,
			font_character_maximum_width,
			font_character_maximum_height;

		FILE
			*fonts_header_file,
			*fonts_data_file;

		font_database_header
			font_header;

		wchar_t
			buf[32];

		char
			real_type_name[32];

		unsigned
			count;

		for ( count = 0; count <= strlen ( type_name ); count++ )
		{

			buf[count] = type_name[count];
		}

		buf[count] = 0;

		strcpy ( font_header.type_name, type_name );
		font_header.font_source_width = width;
		font_header.font_source_height = height;
		font_header.font_source_weight = weight;
		font_header.font_italics = italics;

		if ( file_exist ( UI_FONT_HEADER_FILE ) )
		{

			font_offset = file_size ( UI_FONT_HEADER_FILE ) / sizeof ( font_database_header );
			font_header.kerning_data_offset = file_size ( UI_FONT_DATA_FILE );
			fonts_header_file = safe_fopen ( UI_FONT_HEADER_FILE, "ab") ;
			fonts_data_file = safe_fopen ( UI_FONT_DATA_FILE, "ab" );
		}
		else
		{

			font_offset = 0;
			font_header.kerning_data_offset = 0;
			fonts_header_file = safe_fopen ( UI_FONT_HEADER_FILE, "wb") ;
			fonts_data_file = safe_fopen ( UI_FONT_DATA_FILE, "wb" );
		}

		old_active_screen = get_active_screen ();

		rect.top = 0;
		rect.left = 0;
		rect.right = 128;
		rect.bottom = 128;

		my_font = CreateFontW ( 	height, 							// Height
											width,							// Width ( 0 = don't care )
											0,									// Escapement
											0,									// Orientation
											ithickness,						// FW_HEAVY,	//FW_DONTCARE,	// Weight ( [thin] 0->1000 [bold )
											italics,								// Italics
											FALSE,							// Underline
											FALSE,							// Strikeout
											DEFAULT_CHARSET,					// Character set
											OUT_TT_PRECIS,					// How to choose the font?
											CLIP_DEFAULT_PRECIS,			// How to clip the font!!!!
											DEFAULT_QUALITY,				// ANTIALIASED_QUALITY,	//DEFAULT_QUALITY,		// quality
											VARIABLE_PITCH | FF_SCRIPT,
											buf );	//type_name );


		if ( !my_font )
		{

			debug_fatal  ( "Create Font returned NULL ( %d )", GetLastError () );
		}

		//
		// Get Kerning information
		//

		debug_log ( "Creating font %s ( %d )", type_name, height );

		hdc = GetDC ( application_window );

		SelectObject ( hdc, my_font );

		GetTextFaceW ( hdc, 32, buf );

		SelectObject ( hdc, GetStockObject ( DEFAULT_GUI_FONT ) );

		ReleaseDC ( application_window, hdc );

		for ( count = 0; count <= strlen ( type_name ); count++ )
		{

			real_type_name[count] = type_name[count];
		}

		debug_log ( "Using font: %s", real_type_name );

		number_of_kerning_pairs = GetKerningPairs ( hdc, 0, 0 );

		font_header.number_of_kerning_pairs = number_of_kerning_pairs;

		if ( number_of_kerning_pairs )
		{

			KERNINGPAIR
				*pairs;

			pairs = ( KERNINGPAIR * ) safe_malloc ( number_of_kerning_pairs * sizeof ( KERNINGPAIR ) );

			GetKerningPairs ( hdc, number_of_kerning_pairs, pairs );

			fwrite ( pairs, sizeof ( KERNINGPAIR ), number_of_kerning_pairs, fonts_data_file );

			safe_free ( pairs );
		}

		font_character_maximum_width = 0;
		font_character_maximum_height = 0;

#ifdef UNICODE
		for ( character_count = 32; character_count < FONT_CHARACTERS; character_count++ )
#else
		for ( character_count = 0; character_count < sizeof ( font_character_table ); character_count++ )
#endif
		{

			int
				finished,
				character_width,
				character_height;

			TEXTMETRIC
				metric;

			unsigned char
				*ptr;

			int
				x_adjust,
				y_adjust,
				size;

			ABC
				widths;

			memset ( aliased_character, 0, 128*128 );

#ifdef UNICODE
			if ( character_count != ' ' )
#else
			if ( font_character_table[character_count] != ' ' )
#endif
			{

				unsigned int
					actual_character;

#ifdef UNICODE
				actual_character = character_count;
#else
				actual_character = font_character_table[character_count];

				if ( ( actual_character >= 126 ) && ( actual_character <= 190 ) )
				{

					actual_character = unicode_character_table[actual_character-126];
				}
				else if ( actual_character == 255 )
				{

					actual_character = '©';
				}
#endif

				hdc = GetDC ( application_window );

				SelectObject ( hdc, my_font );

				GetTextMetrics ( hdc, &metric );

				if ( !GetCharABCWidthsW ( hdc, actual_character, actual_character, &widths ) )
				{

					debug_log ( "Failed to get widths" );
				}

				mat2.eM11.fract = 0; mat2.eM11.value = 1; mat2.eM12.fract = 0; mat2.eM12.value = 0;
				mat2.eM21.fract = 0; mat2.eM21.value = 0; mat2.eM22.fract = 0; mat2.eM22.value = 1;

				memset ( &metrics, 0, sizeof ( metrics ) );

				size = sizeof ( glyph_character );

				GetGlyphOutlineW ( hdc, actual_character, GGO_GRAY8_BITMAP, &metrics, size, glyph_character, &mat2 );

				SelectObject ( hdc, GetStockObject ( DEFAULT_GUI_FONT ) );

				ReleaseDC ( application_window, hdc );

				character_width = metrics.gmBlackBoxX;
				character_height = metrics.gmBlackBoxY;

				if ( character_width & 3 )
				{

					character_width &= 0xfffffffc;
					character_width += 4;
				}

				ptr = glyph_character;

				y_adjust = metric.tmAscent - metrics.gmptGlyphOrigin.y;

				if ( y_adjust < 0 )
				{

					y_adjust = 0;
				}

				finished = FALSE;

				for ( x_adjust = 0; !finished; x_adjust++ )
				{

					for ( y = 0; y < character_height; y++ )
					{

						if ( glyph_character[ (y*character_width)+x_adjust ] != 0 )
						{

							finished = TRUE;

							break;
						}
					}

					if ( x_adjust >= character_width )
					{

						x_adjust = 1;

						finished = TRUE;

						break;
					}
				}

				x_adjust -= 1;

				x_adjust = -x_adjust;	//metrics.gmptGlyphOrigin.x;

				for ( y = 0; y < character_height; y++ )
				{

					for ( x = 0; x < character_width; x++ )
					{

						float
							fval;

						int
							ival;

						fval = *ptr++;

						fval *= 255.0 / 65.0;

						convert_float_to_int ( fval, &ival );

						aliased_character[((y+y_adjust)*128)+(x+x_adjust)] = ival;
					}
				}

				//
				// Re-assess character width, as we want the proper width, not dword aligned width! :)
				//

//				character_width = metrics.gmBlackBoxX + x_adjust + UI_FONT_WINDOWS_TEXTURE_WIDTH_GAP;
				character_width = metrics.gmBlackBoxX;

				character_height += y_adjust + UI_FONT_WINDOWS_TEXTURE_HEIGHT_GAP;

				fwrite ( &character_width, sizeof ( int ), 1, fonts_data_file );
				fwrite ( &character_height, sizeof ( int ), 1, fonts_data_file );

				{

					int
						abcA,
						abcB,
						abcC;

					abcA = widths.abcA;
					abcB = widths.abcB;
					abcC = widths.abcC;

					fwrite ( &abcA, sizeof ( int ), 1, fonts_data_file );
					fwrite ( &abcB, sizeof ( int ), 1, fonts_data_file );
					fwrite ( &abcC, sizeof ( int ), 1, fonts_data_file );
				}

				font_character_maximum_width = max ( font_character_maximum_width, character_width );
				font_character_maximum_height = max ( font_character_maximum_height, character_height );

				for ( y = 0; y < character_height; y++ )
				{

					for ( x = 0; x < character_width; x++ )
					{

						fwrite ( &aliased_character[y*128+x], 1, 1, fonts_data_file );
					}
				}
			}
			else
			{

				//
				// Special case the space character
				//

				hdc = GetDC ( application_window );

				SelectObject ( hdc, my_font );

				GetTextMetrics ( hdc, &metric );

				if ( !GetCharABCWidths ( hdc, ' ', ' ', &widths ) )
				{

					debug_log ( "Failed to get widths" );
				}

				mat2.eM11.fract = 0;
				mat2.eM11.value = 1;

				mat2.eM12.fract = 0;
				mat2.eM12.value = 0;

				mat2.eM21.fract = 0;
				mat2.eM21.value = 0;

				mat2.eM22.fract = 0;
				mat2.eM22.value = 1;

				memset ( &metrics, 0, sizeof ( metrics ) );

				size = sizeof ( glyph_character );

				GetGlyphOutlineW ( hdc, 'o', GGO_METRICS, &metrics, size, glyph_character, &mat2 );

				SelectObject ( hdc, GetStockObject ( DEFAULT_GUI_FONT ) );

				ReleaseDC ( application_window, hdc );

				character_width = metrics.gmBlackBoxX;
				character_height = metrics.gmBlackBoxY;

				fwrite ( &character_width, sizeof ( int ), 1, fonts_data_file );
				fwrite ( &character_height, sizeof ( int ), 1, fonts_data_file );

				{

					int
						abcA,
						abcB,
						abcC;

					abcA = widths.abcA;
					abcB = widths.abcB;
					abcC = widths.abcC;

					fwrite ( &abcA, sizeof ( int ), 1, fonts_data_file );
					fwrite ( &abcB, sizeof ( int ), 1, fonts_data_file );
					fwrite ( &abcC, sizeof ( int ), 1, fonts_data_file );
				}

				font_character_maximum_width = max ( font_character_maximum_width, character_width );
				font_character_maximum_height = max ( font_character_maximum_height, character_height );
			}
		}

		//
		// Put a 2 pixel surround for each character
		//

//		font_character_maximum_width += UI_FONT_WINDOWS_TEXTURE_WIDTH_GAP;
//		font_character_maximum_height += UI_FONT_WINDOWS_TEXTURE_HEIGHT_GAP;

		font_header.font_character_maximum_width = font_character_maximum_width + 1;
		font_header.font_character_maximum_height = font_character_maximum_height + 1;

		font_header.graphic_data_offset = font_header.kerning_data_offset + ( number_of_kerning_pairs * sizeof ( KERNINGPAIR ) );

		fwrite ( &font_header, sizeof ( font_database_header ), 1, fonts_header_file );


		fflush ( fonts_header_file );

		fflush ( fonts_data_file );

		safe_fclose ( fonts_header_file );

		safe_fclose ( fonts_data_file );

		set_active_screen ( old_active_screen );

		hdc = GetDC ( application_window );

		SelectObject ( hdc, GetStockObject ( DEFAULT_GUI_FONT ) );

		ReleaseDC ( application_window, hdc );

		DeleteObject ( my_font );
	}

	//
	// Now load the font
	//

	{

		font_database_header
			*font_headers;

		font_headers = ( font_database_header * ) safe_mopen ( UI_FONT_HEADER_FILE );

		fp = safe_fopen ( UI_FONT_DATA_FILE, "rb" );

		old_active_screen = get_active_screen ();

		//
		// Detect font maximum extents
		//

		new_font->font_width = font_headers[font_offset].font_character_maximum_width;
		new_font->font_height = font_headers[font_offset].font_character_maximum_height;

		//
		// Get Kerning information
		//

		new_font->number_of_kerning_pairs = font_headers[font_offset].number_of_kerning_pairs;

		new_font->kerning_pairs = NULL;

		if ( new_font->number_of_kerning_pairs )
		{

			new_font->kerning_pairs = ( KERNINGPAIR * ) safe_malloc ( sizeof ( KERNINGPAIR ) * new_font->number_of_kerning_pairs );

			fseek ( fp, font_headers[font_offset].kerning_data_offset, SEEK_SET );

			safe_fread ( new_font->kerning_pairs, sizeof ( KERNINGPAIR ), new_font->number_of_kerning_pairs, fp );
		}

		//
		// Start off at 16x16 texture, working upwards
		//

		texture_width = 16;
		texture_height = 16;
		finished = FALSE;

		while ( !finished )
		{

			characters_wide = texture_width / new_font->font_width;
			characters_high = texture_height / new_font->font_height;

#ifdef UNICODE
			if ( ( characters_wide * characters_high ) >= FONT_CHARACTERS )
#else
			if ( ( characters_wide * characters_high ) >= sizeof ( font_character_table ) )
#endif
			{

				finished = TRUE;
			}
			else
			{

				if ( texture_width > texture_height )
				{

					texture_height *= 2;
				}
				else
				{

					texture_width *= 2;
				}
			}
		}

		//
		// Check maximum texture sizes
		//

		finished = FALSE;
		number_of_screens = 1;
		font_screens = NULL;

		if ( ( texture_width > d3d_maximum_texture_width ) || ( texture_height > d3d_maximum_texture_height ) )
		{

			texture_width = bound ( texture_width, 0, d3d_maximum_texture_width );
			texture_height = bound ( texture_height, 0, d3d_maximum_texture_height );

			//
			// Recalculate the number of screens
			//

			characters_wide = texture_width / new_font->font_width;
			characters_high = texture_height / new_font->font_height;
#ifdef UNICODE
			number_of_screens = ( FONT_CHARACTERS / ( characters_wide * characters_high ) ) + 1;
#else
			number_of_screens = ( sizeof ( font_character_table ) / ( characters_wide * characters_high ) ) + 1;
#endif
		}

		new_font->number_of_screens = number_of_screens;

		new_font->screens = ( screen * * ) safe_malloc ( sizeof ( screen * ) * number_of_screens );

		memset ( new_font->screens, 0, sizeof ( screen * ) * number_of_screens );

		colour.r = 255;
		colour.g = 255;
		colour.b = 255;
		colour.a = 0;

		for ( count = 0; count < number_of_screens; count++ )
		{

			new_font->screens[count] = create_user_texture_screen ( texture_width, texture_height, TEXTURE_TYPE_MULTIPLEALPHA, 1 );

			set_active_screen ( new_font->screens[count] );

			lock_screen ( active_screen );

			set_block ( 0, 0, texture_width - 1, texture_height - 1, colour );

			unlock_screen ( active_screen );
		}

		character_x = 0;
		character_y = 0;
		screen_index = 0;

		fseek ( fp, font_headers[font_offset].graphic_data_offset, SEEK_SET );

#ifdef UNICODE
		for ( character_count = 32; character_count < FONT_CHARACTERS; character_count++ )
#else
		for ( character_count = 0; character_count < sizeof ( font_character_table ); character_count++ )
#endif
		{

			int
				index,
				character_width,
				character_height;

			float
				u,
				v;

#ifdef UNICODE
			index = character_count;
#else
			index = font_character_table[character_count];
#endif

			safe_fread ( &character_width, sizeof ( int ), 1, fp );
			safe_fread ( &character_height, sizeof ( int ), 1, fp );

			safe_fread ( &new_font->characters[index].abcA, sizeof ( int ), 1, fp );
			safe_fread ( &new_font->characters[index].abcB, sizeof ( int ), 1, fp );
			safe_fread ( &new_font->characters[index].abcC, sizeof ( int ), 1, fp );

			//
			// Put a pointer to the kerning pairs for this character
			//

			new_font->characters[index].kerning_pairs = NULL;

			{

				int
					found,
					kerning_count;

				found = FALSE;

				for ( kerning_count = 0; kerning_count < new_font->number_of_kerning_pairs; kerning_count++ )
				{

					if ( new_font->kerning_pairs[kerning_count].wFirst == index )
					{

						new_font->characters[index].kerning_pairs = &new_font->kerning_pairs[kerning_count];

						found = TRUE;

						break;
					}
				}

				if ( found )
				{

					for ( ; kerning_count < new_font->number_of_kerning_pairs; kerning_count++ )
					{

						if ( new_font->kerning_pairs[kerning_count].wFirst != index )
						{

							break;
						}
					}

					for ( ; kerning_count < new_font->number_of_kerning_pairs; kerning_count++ )
					{

						ASSERT ( new_font->kerning_pairs[kerning_count].wFirst != index );
					}
				}
			}

			if ( index != ' ' )
			{

				//
				// Figure out the coordinates in the texture to put the character
				//

				set_active_screen ( new_font->screens[screen_index] );

#if 1
				lock_screen ( active_screen );

				for ( y = 0; y < character_height; y++ )
				{

					for ( x = 0; x < character_width; x++ )
					{

						colour.r = 255;
						colour.g = 255;
						colour.b = 255;
						fread ( &colour.a, 1, 1, fp );

						set_pixel ( character_x + x, character_y + y, colour );
					}
				}

				unlock_screen ( active_screen );
#endif
			}

			//
			// Now put the information into the character itself
			//

			u = ( float ) character_x / ( float ) texture_width;
			v = ( float ) character_y / ( float ) texture_height;

			u -= ( 1.0 / ( texture_width * 2 ) );
			v -= ( 1.0 / ( texture_width * 2 ) );

			new_font->characters[index].width = character_width;
			new_font->characters[index].height = character_height;
			new_font->characters[index].screen_index = screen_index;
			new_font->characters[index].valid = TRUE;
			new_font->characters[index].u1 = u;
			new_font->characters[index].v1 = v;

			/*if ( d3d_using_permedia2_chipset )
			{

				new_font->characters[index].u2 = u + ( ( ( float ) character_width + 0.0 ) / ( float ) texture_width );
				new_font->characters[index].v2 = v + ( ( ( float ) character_height + 0.0 ) / ( float ) texture_height );
			}
			else*/
			{

				new_font->characters[index].u2 = u + ( ( ( float ) character_width + 1.0 ) / ( float ) texture_width );
				new_font->characters[index].v2 = v + ( ( ( float ) character_height + 0.0 ) / ( float ) texture_height );
			}

			character_x += new_font->font_width;

			if ( ( character_x + new_font->font_width ) > texture_width )
			{

				character_x = 0;

				character_y += new_font->font_height;

				if ( ( character_y + new_font->font_height ) > texture_height )
				{

					character_y = 0;

					screen_index++;
				}
			}
		}

		set_active_screen ( old_active_screen );

		safe_mclose ( font_headers );

		safe_fclose ( fp );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ui_font (void)
{

	int
		count;

	for ( count = 0; count < NUM_FONT_TYPES; count++ )
	{

		if (ui_fonts [count].loaded)
		{

			int
				screen_index;

			//
			// Free up the screens etc
			//

			for ( screen_index = 0; screen_index < ui_fonts[count].number_of_screens; screen_index++ )
			{

				destroy_screen ( ui_fonts[count].screens[screen_index] );
			}

			safe_free ( ui_fonts[count].screens );

			ui_fonts[count].screens = NULL;

			safe_free ( ui_fonts[count].type_name );

			ui_fonts[count].type_name = NULL;
		}
	}

	memset ( ui_fonts, 0, sizeof ( ui_fonts ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

static wchar_t fetch_character ( const char **ptr )
{
	wchar_t
		ch;

#ifdef UNICODE
	if ((unsigned char) **ptr < 0x80)
	{
		ch = **ptr;
		(*ptr)++;
	}
	else
	{
		ch = (((unsigned) ((*ptr)[0] & 0x1F)) << 6) | ((*ptr)[1] & 0x3F);
		(*ptr) += 2;
	}

	return ch;
#else
	ch = (unsigned char) **ptr;
	(*ptr)++;
	return ch >= 126 && ch <= 190 ? unicode_character_table[ch - 126] : ch == 255 ? 0xA9 : ch;
#endif
}

float ui_display_text (const char *text, float x, float y)
{
#ifndef OGRE_EE

	if ( d3d_in_3d_scene )
	{

		float
			ox,
			oy;

		int
			ix,
			iy;

		font_character
			*character;

		float
			char_end_x,
			char_end_y,
			char_start_x,
			char_start_y,
			original_x_position;

		const char
			*text_ptr;

		viewport
			old_active_viewport,
			new_viewport;

		int_viewport
			old_active_int_viewport;

		real_colour
			colour,
			shadow_colour,
			specular;

		screen
			*texture;

		wchar_t
			cur,
			next;

		//
		// Always have to render text to the video screen
		//

		ASSERT ( active_screen == video_screen );

	//	if ( begin_3d_scene () )
		{

			if (!text)
			{

				return 0;
			}

			//
			// setup stuff
			//

			x += ui_x_origin;

			y += ui_y_origin;

			convert_float_to_int ( x, &ix );
			convert_float_to_int ( y, &iy );

			x = ix;
			y = iy;

			original_x_position = x;

			text_ptr = text;

			colour.red = current_font_colour.r;
			colour.green = current_font_colour.g;
			colour.blue = current_font_colour.b;
			colour.alpha = current_font_colour.a;

			shadow_colour.red = 0;
			shadow_colour.green = 0;
			shadow_colour.blue = 0;
			shadow_colour.alpha = current_font_colour.a / 2;

			specular.red = 0;
			specular.green = 0;
			specular.blue = 0;
			specular.alpha = 255;

			//
			// Save old viewport values
			//

			old_active_viewport = active_viewport;

			old_active_int_viewport = active_int_viewport;

			//
			// Calculate new viewport settings
			//

			ox = ui_x_origin;

			oy = ui_y_origin;

			ui_set_origin (0, 0);

			ui_get_clip_area ( &new_viewport.x_min, &new_viewport.y_min, &new_viewport.x_max, &new_viewport.y_max );

			set_viewport ( new_viewport.x_min, new_viewport.y_min, new_viewport.x_max, new_viewport.y_max );

			ui_set_origin (ox, oy);

			//
			// Set renderstates
			//

			texture = current_font->screens[0];

			set_d3d_gouraud_shaded_textured_renderstate ( texture );

			set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, FALSE, FALSE );

			set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

			set_d3d_int_state ( D3DRS_ZFUNC, D3DCMP_ALWAYS );

			set_d3d_sampler_state_immediate ( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
			set_d3d_sampler_state_immediate ( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

			set_d3d_sampler_state_immediate ( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
			set_d3d_sampler_state_immediate ( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
			set_d3d_sampler_state_immediate ( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

			//
			// loop the whole string
			//

			cur = fetch_character (&text_ptr);

			while ( cur )
			{

				vertex
					quad[4];

				int
					outcode,
					outcode2;

				//
				// work out what char
				//

				character = &current_font->characters[cur];

				if ( !character->valid )
				{

					break;
	/*
					if (*text_ptr == 10)
					{

						y += ui_get_font_height ();

						x = original_x_position;
					}

					text_ptr ++;

					continue;
					*/
				}

				//
				// starting position for char in viewport coords
				//

				char_start_x = x + character->abcA;

				char_start_y = y;

				//
				// calculate end of char in viewport coords
				//

				char_end_x = char_start_x + character->width+1;	//current_font->letter_data [index].width;
//				char_end_x = char_start_x + character->width;	//current_font->letter_data [index].width;

				char_end_y = char_start_y + character->height;	//current_font->font_height;

				memset ( quad, 0, sizeof ( quad ) );

				quad[0].u = character->u1;
				quad[0].v = character->v1;
				quad[0].q = 0.1;
				quad[0].z = 100;

				quad[1].u = character->u2;
				quad[1].v = character->v1;
				quad[1].q = 0.1;
				quad[1].z = 100;

				quad[2].u = character->u2;
				quad[2].v = character->v2;
				quad[2].q = 0.1;
				quad[2].z = 100;

				quad[3].u = character->u1;
				quad[3].v = character->v2;
				quad[3].q = 0.1;
				quad[3].z = 100;

				if ( current_font->font_dropshadow )
				{

					quad[0].i = char_start_x + 1;
					quad[0].j = char_start_y + 1;
					quad[0].next_vertex = &quad[1];

					quad[1].i = char_end_x + 1;
					quad[1].j = char_start_y + 1;
					quad[1].next_vertex = &quad[2];

					quad[2].i = char_end_x + 1;
					quad[2].j = char_end_y + 1;
					quad[2].next_vertex = &quad[3];

					quad[3].i = char_start_x + 1;
					quad[3].j = char_end_y + 1;
					quad[3].next_vertex = NULL;

					quad[0].outcode = generate_outcode ( quad[0].i, quad[0].j );
					quad[1].outcode = generate_outcode ( quad[1].i, quad[1].j );
					quad[2].outcode = generate_outcode ( quad[2].i, quad[2].j );
					quad[3].outcode = generate_outcode ( quad[3].i, quad[3].j );

					//
					// Draw the character
					//

					outcode = quad[0].outcode;
					outcode2 = quad[0].outcode;

					outcode |= quad[1].outcode;
					outcode2 &= quad[1].outcode;

					outcode |= quad[2].outcode;
					outcode2 &= quad[2].outcode;

					outcode |= quad[3].outcode;
					outcode2 &= quad[3].outcode;

					if ( outcode2 == 0 )
					{

						vertex
							*poly;

						clip_3d_coord = 0;

						poly = quad;

						if ( outcode )
						{

							poly = clip_3d_polygon ( poly, outcode );
						}

						if ( poly )
						{

							set_d3d_gouraud_shaded_textured_renderstate ( current_font->screens[character->screen_index] );

							draw_wbuffered_flat_shaded_textured_polygon ( poly, shadow_colour, specular );	//, colour, specular );
						}
					}
				}
				//
				// Set up quad vertices
				//

				quad[0].i = char_start_x;
				quad[0].j = char_start_y;
				quad[0].next_vertex = &quad[1];

				quad[1].i = char_end_x;
				quad[1].j = char_start_y;
				quad[1].next_vertex = &quad[2];

				quad[2].i = char_end_x;
				quad[2].j = char_end_y;
				quad[2].next_vertex = &quad[3];

				quad[3].i = char_start_x;
				quad[3].j = char_end_y;
				quad[3].next_vertex = NULL;

				quad[0].outcode = generate_outcode ( quad[0].i, quad[0].j );
				quad[1].outcode = generate_outcode ( quad[1].i, quad[1].j );
				quad[2].outcode = generate_outcode ( quad[2].i, quad[2].j );
				quad[3].outcode = generate_outcode ( quad[3].i, quad[3].j );

				//
				// Draw the character
				//

				outcode = quad[0].outcode;
				outcode2 = quad[0].outcode;

				outcode |= quad[1].outcode;
				outcode2 &= quad[1].outcode;

				outcode |= quad[2].outcode;
				outcode2 &= quad[2].outcode;

				outcode |= quad[3].outcode;
				outcode2 &= quad[3].outcode;

				if ( outcode2 == 0 )
				{

					vertex
						*poly;

					clip_3d_coord = 0;

					poly = quad;

					if ( outcode )
					{

						poly = clip_3d_polygon ( poly, outcode );
					}

					if ( poly )
					{

						set_d3d_gouraud_shaded_textured_renderstate ( current_font->screens[character->screen_index] );

						draw_wbuffered_flat_shaded_textured_polygon ( poly, colour, specular );	//, colour, specular );
					}
				}


				//
				// Go onto the next character
				//

				x += character->abcA + character->abcB + character->abcC;	//character->width;	//float_font_width;

				next = fetch_character ( &text_ptr );

				x += get_kerning_offset ( cur, next );

				cur = next;
			}

			//
			// Reset some renderstates
			//

			flush_triangle_primitives ();

			//
			// Restore the old viewport settings
			//

			active_viewport = old_active_viewport;

			active_int_viewport = old_active_int_viewport;

	//		end_3d_scene ();

			//
			// return the length in pixels of the text written to screen
			//

			return (x - original_x_position);
		}
	//	else
		{

	//		return ( 0 );
		}
	}
	else
	{

		return ( 0 );
	}
#else
	return 0;
#endif
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_kerning_offset ( wchar_t first, wchar_t second )
{

	int
		count;

	font_character
		*character;

	character = &current_font->characters[first];

	if ( character->kerning_pairs )
	{

		count = 0;

		while ( TRUE )
		{

			if ( character->kerning_pairs[count].wFirst != first )
			{

				return ( 0 );
			}
			else
			{

				if ( character->kerning_pairs[count].wSecond == second )
				{

					return ( character->kerning_pairs[count].iKernAmount );
				}
			}

			count++;
		}
	}

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

float ui_get_string_length (const char *string)
{
#ifndef OGRE_EE

	int
		length;

	const char
		*current_char;

	font_character
		*character;

	wchar_t
		cur,
		next;

	if (!string)
	{

		return 0;
	}

	current_char = string;

	length = 0;

	//
	// spin along string adding up length in pixels
	//

	cur = fetch_character (&current_char);

	while (cur)
	{

		character = &current_font->characters[cur];

		if (!character->valid)
		{

			//current_char ++;

			//continue;

			break;
		}

//		length += character->width;

		length += character->abcA + character->abcB + character->abcC;

		next = fetch_character ( &current_char );

		length += get_kerning_offset ( cur, next );

		cur = next;
	}

	return length;
#else
	return 0;
#endif
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ui_display_centred_text (const char *text, float x1, float x2, float y1, float y2)
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
#endif

void set_ui_font_type ( font_types font )
{
	ASSERT ((font >= 0) && (font < NUM_FONT_TYPES));

	current_font_type = font;

	current_font = &ui_fonts [font];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_font_colour ( rgb_colour colour )
{

	current_font_colour = colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

font_types get_ui_font_type (void)
{

	return current_font_type;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour get_ui_font_colour (void)
{

	return current_font_colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_save_current_font (void)
{
	store_font = get_ui_font_type ();

	store_colour = get_ui_font_colour ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_restore_current_font (void)
{
	set_ui_font_type (store_font);

	set_ui_font_colour (store_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_set_object_font (ui_object *obj)
{

	int
		state;

	ASSERT (obj);

	state = get_ui_object_state (obj);

	if (state == UI_OBJECT_STATE_ON)
	{

		set_ui_font_type (get_ui_object_selected_font_type (obj));

		set_ui_font_colour (get_ui_object_selected_font_colour (obj));
	}
	else
	{

		if (get_ui_object_highlighted(obj))
		{

			rgb_colour
				col;

			col = get_ui_object_highlighted_font_colour (obj);

			set_ui_font_type (get_ui_object_highlighted_font_type (obj));

			set_ui_font_colour (get_ui_object_highlighted_font_colour (obj));
		}
		else
		{

			set_ui_font_type (get_ui_object_font_type (obj));

			set_ui_font_colour (get_ui_object_font_colour (obj));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
