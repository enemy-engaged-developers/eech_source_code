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
// VJ 050118
// this unit contains all function necessary for custom texture handling
// the defult textures are read from the texture.bin/pal files, 
// then the default override texture are read in 3d_init.c
// a list of pointers is stored in these structures
//    *backup_system_textures[MAX_TEXTURES];
//    backup_system_texture_info[MAX_TEXTURES];
// in flight.c the warzone specific textures are loaded and 
// in flight.c the default textures are restored after the flight
// warzone textures are created and destroyed, the default custom textures are created but never destroyed.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Have_Quick - 12/5/2003
//
// This will look in TEXTURE_OVERRIDE_DIRECTORY for any 24bit .bmp files
// If it finds any of these files and the file name matches an existing
// texture name, it will create a screen for the bmp and set the system_textures
// pointer to point to the new screen.
//
// Any questions or comments please send an email to the EECHdev mailing list or
// post your question on the SimHQ EECH forum
//
// TODO - add support for Alpha channels
//
// TODO - add support for mipmapping
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics.h"

//VJ 050304 needed for texture colour mod
#include "cmndline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_TEXTURE_HEIGHT 512

#define MAX_TEXTURE_WIDTH 512

#define DEBUG_MODULE 0

#define ALLOW_TEXTURE_CREATION 1

int
	half_texture_graphics = FALSE;

// VJ 04/12/12 desert camouflage texture name indicator
#define DESERTIND_1 "_DESERT"
#define DESERTIND_2 "-D"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TEXTURE_FLAGS
{

	union
	{

		struct
		{

			unsigned short int
				reserved_texture:1,
				vertically_inverted:1,
				contains_alpha:1,
				referenced:1,
				wrapped:1,
				mipmap_enabled:1,
				main_texture:1,
				camoflage_texture:1;

			unsigned char
				number_of_camoflage_textures,
				camoflage_index;
		};

		unsigned int
			flags;
	};
};

typedef struct TEXTURE_FLAGS texture_flags;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SYSTEM_TEXTURE_INFORMATION
{

	texture_flags
		flags;

	screen
		*texture_screen;
};

typedef struct SYSTEM_TEXTURE_INFORMATION system_texture_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TEXTURE_NAME_HASH_ENTRY
{

	int
		hash,
		texture_index;

	struct TEXTURE_NAME_HASH_ENTRY
		*succ;
};

typedef struct TEXTURE_NAME_HASH_ENTRY texture_name_hash_entry;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
struct DDSURFACEDESC2 
Member Description 
DWORD dwSize Size of structure. This member must be set to 124. 
DWORD dwFlags Flags to indicate valid fields. Always include DDSD_CAPS, DDSD_PIXELFORMAT, DDSD_WIDTH, DDSD_HEIGHT. 
DWORD dwHeight Height of the main image in pixels 
DWORD dwWidth Width of the main image in pixels 
DWORD dwPitchOrLinearSize For uncompressed formats, this is the number of bytes per scan line (DWORD> aligned) for the main image. dwFlags should include DDSD_PITCH in this case. For compressed formats, this is the total number of bytes for the main image. dwFlags should be include DDSD_LINEARSIZE in this case. 
DWORD dwDepth For volume textures, this is the depth of the volume. dwFlags should include DDSD_DEPTH in this case. 
DWORD dwMipMapCount For items with mipmap levels, this is the total number of levels in the mipmap chain of the main image. dwFlags should include DDSD_MIPMAPCOUNT in this case. 
DWORD dwReserved1[11]  
DDPIXELFORMAT ddpfPixelFormat 32-byte value that specifies the pixel format structure. 
DDCAPS2 ddsCaps 16-byte value that specifies the capabilities structure. 
DWORD dwReserved2 
*/

int
	number_of_system_texture_palettes,
	number_of_system_textures,
	number_of_system_texture_camoflages;

//VJ 050322 texture coulor mod: texture scale array, 64 is enough for terrain textures
int 
	texture_override_scales[64][2];
	
//FILE *fout;

screen
	*system_textures[MAX_TEXTURES],
	//VJ 050116 custom texture mod: backup textures to restore default
   *backup_system_textures[MAX_TEXTURES];
	//this does not seem to be used
	//*application_textures[MAX_TEXTURES];

static BOOL override_present;

system_texture_information
	system_texture_info[MAX_TEXTURES],
	//VJ 050116 custom texture mod: backup textures to restore default
	backup_system_texture_info[MAX_TEXTURES];

LPDIRECTDRAWPALETTE
	system_texture_palettes[MAX_TEXTURES_PALETTES];

PALETTEENTRY
	system_texture_colour_tables[MAX_TEXTURES_PALETTES][256];

char
	system_texture_names[MAX_TEXTURES][128];

texture_name_hash_entry
	system_texture_name_hashes[MAX_TEXTURES];

texture_name_hash_entry
	*system_texture_name_hash_table[256];

int
	system_textures_referenced[MAX_TEXTURES];

unsigned char
	texture_image_data[MAX_TEXTURE_WIDTH*MAX_TEXTURE_HEIGHT*4];



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start Have_Quick
// 12/5/2003
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 041212 organization of texture directory
#define TEXTURE_OVERRIDE_DIRECTORY "..\\cohokum\\graphics\\textures"
#define TEXTURE_OVERRIDE_DIRECTORY_COCKPIT "cockpit"
#define TEXTURE_OVERRIDE_DIRECTORY_TERRAIN "terrain"
#define TEXTURE_OVERRIDE_DIRECTORY_CAMO "camo"

#define BITMAP_ID		(0x4D42)

char
	system_texture_override_names[MAX_TEXTURES][128];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end Have_Quick
// 12/5/2003
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void create_internal_texture_palettes ( void );

void convert_no_alpha_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp );

void convert_single_alpha_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp );

void convert_multiple_alpha_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp );

void convert_no_alpha_24bit_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp, int reverse );

void convert_single_alpha_32bit_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp );
void convert_single_alpha_32bit_texture_map_data_v ( unsigned char *data, unsigned char *dataa, int width, int height, screen *this_texture);

void convert_multiple_alpha_32bit_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp, int reverse );

//VJ 050503 check bitmap
int check_bitmap_header ( BITMAPINFOHEADER bmih, char *full_override_texture_filename );

//void load_texture_override_dds ( char system_texture_override_names[MAX_TEXTURES][128]);

screen *create_texture_map_dds ( int type, DDSURFACEDESC2 ddsd );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 04/12/12 comment: set = 0 for default or 1 for desert
void set_texture_camoflage ( int set )
{

	int
		count;

	for ( count = 0; count < number_of_system_textures; count++ )
	{

		if ( system_texture_info[count].flags.main_texture )
		{

			if ( system_texture_info[count].flags.number_of_camoflage_textures )
			{

				{

					int
						index;

					for ( index = 1; index <= system_texture_info[count].flags.number_of_camoflage_textures; index++ )
					{

						if ( system_texture_info[count+index].flags.camoflage_texture )
						{

							if ( system_texture_info[count+index].flags.camoflage_index > 1 )
							{

								debug_log ( "Error: Texture: %s has incorrect camoflage name", system_texture_names[count] );
							}
						}
					}
				}
			}
		}
	}

	for ( count = 0; count < number_of_system_textures; count++ )
	{
		if ( system_texture_info[count].flags.main_texture )
		{

			if ( system_texture_info[count].flags.number_of_camoflage_textures )
			{
				if ( set == 0 )
				{
					system_textures[count] = system_texture_info[count].texture_screen;
				}
				else
				{

					int
						index;

					for ( index = 1; index <= system_texture_info[count].flags.number_of_camoflage_textures; index++ )
					{

						if ( system_texture_info[count+index].flags.camoflage_texture )
						{
							if ( system_texture_info[count+index].flags.camoflage_index == set )
							{
								system_textures[count] = system_texture_info[count+index].texture_screen;
								break;
							}
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void release_system_textures ( void )
{

#if ( !DEBUG )
/*
	int
		count;

	HRESULT
		ddrval;

	//
	// Release the system memory textures
	//

	for ( count = 0; count < MAX_TEXTURES; count++ )
	{

		if ( system_textures[count].used )
		{

			if ( !system_textures[count].clone_screen )
			{

				if ( system_textures[count].palette )
				{

					IDirectDrawSurface7_SetPalette ( system_textures[count].surface, NULL );

					system_textures[count].palette = NULL;
				}

				release_texture_surface ( &system_textures[count].surface );

				system_textures[count].used = FALSE;
			}
		}
	}

	//
	// Finally any palettes
	//

	for ( count = 0; count < number_of_system_texture_palettes; count++ )
	{

		if ( system_texture_palettes[count] )
		{

			ddrval = IDirectDrawPalette_Release ( system_texture_palettes[count] );

			if ( ddrval < DD_OK )
			{

				debug_log ( "Unable to release palette: %s", get_ddraw_error_message ( ddrval ) );
			}
			else if ( ddrval > DD_OK )
			{

				debug_log ( "Palette not released, %d references left", ddrval );
			}
			else
			{

				debug_log ( "Released palette!" );
			}

			system_texture_palettes[count] = NULL;
		}
	}
	*/
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_system_texture_index ( char *name )
{

	int
		letter,
		length,
		hash,
		hash_index;

	texture_name_hash_entry
		*entry;

	length = strlen ( name );

	hash = length;

	for ( letter = 0; letter < length; letter++ )
	{

		hash += name[letter];

		hash <<= 1;
	}

	hash_index = hash & 0xff;

	entry = system_texture_name_hash_table[hash_index];

	while ( entry )
	{

		if ( entry->hash == hash )
		{

			if ( stricmp ( system_texture_names[entry->texture_index], name ) == 0 )
			{

				return ( entry->texture_index );
			}
		}
		else
		{

			entry = entry->succ;
		}
	}

	debug_log ( "Unable to find texture: %s", name );

	return ( -1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL load_texturemap_data ( char *path )
{

	int
		count;

	int
		width,
		height,
		type,
		texture_format_type;

	FILE
		*fp;

	char
		filename[512];

	number_of_system_texture_camoflages = 0;

	//
	// Mark off the system texture slots as not used / locked
	//

	memset ( system_textures, 0, sizeof ( system_textures ) );

	//
	// Reset texture hash table
	//

	memset ( system_texture_name_hash_table, 0, ( sizeof ( texture_name_hash_entry * ) * 256 ) );

	//
	// Load the texture data
	//

	if ( d3d_paletted_textures_supported )
	{

		sprintf ( filename, "%s\\textures.pal", path );
	}
	else
	{

		sprintf ( filename, "%s\\textures.bin", path );
	}

	fp = safe_fopen ( filename, "rb" );

	//
	// First integer is the number of palettes the textures use in total.
	//

	fread ( &number_of_system_texture_palettes, 4, 1, fp );

	for ( count = 0; count < number_of_system_texture_palettes; count++ )
	{

		int
			temp;

		fread ( system_texture_colour_tables[count], sizeof ( PALETTEENTRY ), 256, fp );

		for ( temp = 0; temp < 256; temp++ )
		{

			system_texture_colour_tables[count][temp].peFlags = D3DPAL_READONLY | PC_NOCOLLAPSE;
		}
	}

	//
	// Now create the direct draw palette interfaces for the palettes
	//

	create_internal_texture_palettes ();

	fread ( &number_of_system_textures, 4, 1, fp );

	debug_log ( "Reading in %d textures", number_of_system_textures );


	if ( d3d_paletted_textures_supported )
	{

		for ( count = 0; count < number_of_system_textures; count++ )
		{

			int
				temp,
				length,
				letter,
				hash,
				hash_index,
				number_of_mipmaps;

			unsigned int
				value;

			screen
				*this_texture;

			texture_flags
				flags;

			fread ( &value, sizeof ( unsigned int ), 1, fp );

			flags.flags = value;

			system_texture_info[count].flags.flags = flags.flags;

			system_texture_info[count].texture_screen = NULL;

			memset ( system_texture_names[count], 0, 128 );

			fread ( &length, sizeof ( length ), 1, fp );

			fread ( system_texture_names[count], length, 1, fp );

			for ( letter = 0; letter < 128; letter++ )
			{

				system_texture_names[count][letter] = toupper ( system_texture_names[count][letter] );
			}

			hash = strlen ( system_texture_names[count] );

			for ( letter = 0; letter < strlen ( system_texture_names[count] ); letter++ )
			{

				hash += system_texture_names[count][letter];

				hash <<= 1;
			}

			hash_index = hash & 0xff;

			system_texture_name_hashes[count].hash = hash;
			system_texture_name_hashes[count].texture_index = count;
			system_texture_name_hashes[count].succ = system_texture_name_hash_table[hash_index];
			system_texture_name_hash_table[hash_index] = &system_texture_name_hashes[count];

			if ( flags.reserved_texture )
			{

				//
				// Reserve this texture slot
				//

				system_textures[count] = NULL;
			}
			else
			{

				int
					palette_index;

				fread ( &type, sizeof ( type ), 1, fp );
				fread ( &number_of_mipmaps, sizeof ( int ), 1, fp );
				fread ( &width, sizeof ( int ), 1, fp );
				fread ( &height, sizeof ( int ), 1, fp );
				fread ( &palette_index, sizeof ( int ), 1, fp );

				texture_format_type = type;

				ASSERT ( width <= MAX_TEXTURE_WIDTH );
				ASSERT ( height <= MAX_TEXTURE_HEIGHT );

				//
				// If we compress the textures, skip over the first level texture
				//

				if ( compress_system_textures )
				{

					width >>= 1;
					height >>= 1;
					number_of_mipmaps--;

					switch ( type )
					{

						case TEXTURE_TYPE_NOALPHA:
						case TEXTURE_TYPE_NOALPHA_NOPALETTE:
						case TEXTURE_TYPE_SINGLEALPHA:
						{

							fseek ( fp, ( width * height * 4 ), SEEK_CUR );

							break;
						}

						case TEXTURE_TYPE_MULTIPLEALPHA:
						{

							fseek ( fp, ( width * height * 8 ), SEEK_CUR );

							break;
						}
					}
				}

				while ( ( width > d3d_maximum_texture_width ) || ( height > d3d_maximum_texture_height ) )
				{

					width >>= 1;
					height >>= 1;
					number_of_mipmaps--;

					switch ( type )
					{

						case TEXTURE_TYPE_NOALPHA:
						case TEXTURE_TYPE_NOALPHA_NOPALETTE:
						case TEXTURE_TYPE_SINGLEALPHA:
						{

							fseek ( fp, ( width * height * 4 ), SEEK_CUR );

							break;
						}

						case TEXTURE_TYPE_MULTIPLEALPHA:
						{

							fseek ( fp, ( width * height * 8 ), SEEK_CUR );

							break;
						}
					}
				}

				if ( ( width != height ) && ( d3d_square_only_textures ) )
				{

					//
					// All textures have width >= height
					//

					this_texture = create_texture_map ( width, width, texture_format_type, number_of_mipmaps + 1,
																		system_texture_palettes[palette_index], system_texture_colour_tables[palette_index] );
				}
				else
				{

					this_texture = create_texture_map ( width, height, texture_format_type, number_of_mipmaps + 1,
																		system_texture_palettes[palette_index], system_texture_colour_tables[palette_index] );
				}

				system_textures[count] = this_texture;

				system_texture_info[count].texture_screen = this_texture;

				//
				// Now fill the data in
				//

				for ( temp = 0; temp <= number_of_mipmaps; temp++ )
				{


					if ( ( temp == 0 ) || ( d3d_mipmap_textures ) )
					{

#if ( ALLOW_TEXTURE_CREATION )
						while ( !lock_texture ( this_texture, temp ) )
						{

							Sleep ( 100 );
						}
#endif

						switch ( type )
						{

							case TEXTURE_TYPE_NOALPHA:
							{

								fread ( texture_image_data, ( width * height ), 1, fp );

#if ( ALLOW_TEXTURE_CREATION )
								convert_no_alpha_texture_map_data ( texture_image_data, width, height, this_texture, fp );
#endif

								break;
							}

							case TEXTURE_TYPE_SINGLEALPHA:
							{

								fread ( texture_image_data, ( width * height ), 1, fp );

#if ( ALLOW_TEXTURE_CREATION )
								convert_single_alpha_texture_map_data ( texture_image_data, width, height, this_texture, fp );
#endif

								break;
							}

							case TEXTURE_TYPE_MULTIPLEALPHA:
							{

								fread ( texture_image_data, ( width * height * 2 ), 1, fp );

#if ( ALLOW_TEXTURE_CREATION )
								convert_multiple_alpha_texture_map_data ( texture_image_data, width, height, this_texture, fp );
#endif

								break;
							}
						}

#if ( ALLOW_TEXTURE_CREATION )
						unlock_texture ( this_texture );
#endif
					}
					else
					{

						//
						// Skip over the mipmap data
						//

						switch ( type )
						{

							case TEXTURE_TYPE_NOALPHA:
							case TEXTURE_TYPE_SINGLEALPHA:
							{

								fseek ( fp, ( width * height ), SEEK_CUR );

								break;
							}

							case TEXTURE_TYPE_MULTIPLEALPHA:
							{

								fseek ( fp, ( width * height * 2 ), SEEK_CUR );

								break;
							}
						}
					}

					width >>= 1;

					height >>= 1;
				}
			}
		}
	}
	else // 24 bit: !d3d_paletted_textures_supported
	{
	/*
		for ( count = 0; count < number_of_system_textures; count++ )
		{

			int
				temp,
				letter,
				number_of_mipmaps;

			screen
				*this_texture;

			memset ( system_texture_names[count], 0, 128 );

			fread ( system_texture_names[count], 128, 1, fp );

			for ( letter = 0; letter < 128; letter++ )
			{

				system_texture_names[count][letter] = toupper ( system_texture_names[count][letter] );
			}

			fread ( &type, 4, 1, fp );

			//
			// If the texture is a SCREEN texture, just leave it alone.
			//

			if ( type == TEXTURE_TYPE_SCREEN )
			{

				//
				// Reserve this texture slot
				//

				reserve_texture_map ();
			}
			else
			{

				int
					vertically_inverted;

				fread ( &palette_index, 4, 1, fp );
				fread ( &width, 4, 1, fp );
				fread ( &height, 4, 1, fp );
				fread ( &vertically_inverted, 4, 1, fp );
				fread ( &number_of_mipmaps, 4, 1, fp );

				texture_format_type = type;

				if ( compress_system_textures )
				{

					width >>= 1;
					height >>= 1;
					number_of_mipmaps--;
				}

				if ( ( width != height ) && ( d3d_square_only_textures ) )
				{

					//
					// All textures have width >= height
					//

					this_texture = create_texture_map ( width, width, texture_format_type, number_of_mipmaps,
																		system_texture_palettes[palette_index], system_texture_colour_tables[palette_index] );
				}
				else
				{

					this_texture = create_texture_map ( width, height, texture_format_type, number_of_mipmaps,
																		system_texture_palettes[palette_index], system_texture_colour_tables[palette_index] );
				}

				//
				// If we compress the textures, skip over the first level texture
				//

				if ( compress_system_textures )
				{

					switch ( type )
					{

						case TEXTURE_TYPE_NOALPHA:
						case TEXTURE_TYPE_SINGLEALPHA:
						{

							fseek ( fp, ( width * height * 4 ), SEEK_CUR );

							break;
						}

						case TEXTURE_TYPE_MULTIPLEALPHA:
						{

							fseek ( fp, ( width * height * 8 ), SEEK_CUR );

							break;
						}
					}
				}

				//
				// Now fill the data in
				//

				for ( temp = 0; temp < number_of_mipmaps; temp++ )
				{


					int
						file_position;

					if ( ( temp == 0 ) || ( d3d_mipmap_textures ) )
					{

	#if ( ALLOW_TEXTURE_CREATION )
						while ( !lock_texture ( this_texture, temp ) )
						{

							Sleep ( 100 );
						}
	#endif

						file_position = ftell ( fp );

						switch ( type )
						{

							case TEXTURE_TYPE_NOALPHA:
							{

								fread ( texture_image_data, ( width * height ), 1, fp );

	#if ( ALLOW_TEXTURE_CREATION )
								convert_no_alpha_texture_map_data ( texture_image_data, width, height, this_texture, fp );
	#endif

								break;
							}

							case TEXTURE_TYPE_SINGLEALPHA:
							{

								fread ( texture_image_data, ( width * height ), 1, fp );

	#if ( ALLOW_TEXTURE_CREATION )
								convert_single_alpha_texture_map_data ( texture_image_data, width, height, this_texture, fp );
	#endif

								break;
							}

							case TEXTURE_TYPE_MULTIPLEALPHA:
							{

								fread ( texture_image_data, ( width * height * 2 ), 1, fp );

	#if ( ALLOW_TEXTURE_CREATION )
								convert_multiple_alpha_texture_map_data ( texture_image_data, width, height, this_texture, fp );
	#endif

								break;
							}
						}

	#if ( ALLOW_TEXTURE_CREATION )
						unlock_texture ( this_texture );
	#endif
					}
					else
					{

						//
						// Skip over the mipmap data
						//

						switch ( type )
						{

							case TEXTURE_TYPE_NOALPHA:
							case TEXTURE_TYPE_SINGLEALPHA:
							{

								fseek ( fp, ( width * height ), SEEK_CUR );

								break;
							}

							case TEXTURE_TYPE_MULTIPLEALPHA:
							{

								fseek ( fp, ( width * height * 2 ), SEEK_CUR );

								break;
							}
						}
					}

					width >>= 1;

					height >>= 1;
				}

				width = ftell ( fp );
			}
		}
		*/
//VJ 24 bit texture loading
		for ( count = 0; count < number_of_system_textures; count++ )
		{

			int
				temp,
				length,
				letter,
				hash,
				hash_index,
				number_of_mipmaps;

			unsigned int
				value;

			screen
				*this_texture;

			texture_flags
				flags;

			fread ( &value, sizeof ( unsigned int ), 1, fp );

			flags.flags = value;

			system_texture_info[count].flags.flags = flags.flags;

			system_texture_info[count].texture_screen = NULL;

			memset ( system_texture_names[count], 0, 128 );

			fread ( &length, sizeof ( length ), 1, fp );

			fread ( system_texture_names[count], length, 1, fp );

			for ( letter = 0; letter < 128; letter++ )
			{

				system_texture_names[count][letter] = toupper ( system_texture_names[count][letter] );
			}

			hash = strlen ( system_texture_names[count] );

			for ( letter = 0; letter < strlen ( system_texture_names[count] ); letter++ )
			{

				hash += system_texture_names[count][letter];

				hash <<= 1;
			}

			hash_index = hash & 0xff;

			system_texture_name_hashes[count].hash = hash;
			system_texture_name_hashes[count].texture_index = count;
			system_texture_name_hashes[count].succ = system_texture_name_hash_table[hash_index];
			system_texture_name_hash_table[hash_index] = &system_texture_name_hashes[count];
			if ( flags.reserved_texture )
			{

				//
				// Reserve this texture slot
				//

				system_textures[count] = NULL;
			}
			else
			{

				fread ( &type, sizeof ( type ), 1, fp );
				fread ( &number_of_mipmaps, 4, 1, fp );
				fread ( &width, 4, 1, fp );
				fread ( &height, 4, 1, fp );

				if ( type == TEXTURE_TYPE_NOALPHA )
				{

					type = TEXTURE_TYPE_NOALPHA_NOPALETTE;
				}

				texture_format_type = type;

				//
				// If we compress the textures, skip over the first level texture
				//
//VJ 050423 compress_system_textures = FALSE in textsys.c as far as I know
				if ( compress_system_textures )
				{

					width >>= 1;
					height >>= 1;
					number_of_mipmaps--;

					switch ( type )
					{

						case TEXTURE_TYPE_NOALPHA:
						case TEXTURE_TYPE_NOALPHA_NOPALETTE:
						{

							fseek ( fp, ( width * height * 12 ), SEEK_CUR );

							break;
						}

						case TEXTURE_TYPE_SINGLEALPHA:
						{

							fseek ( fp, ( width * height * 16 ), SEEK_CUR );

							break;
						}

						case TEXTURE_TYPE_MULTIPLEALPHA:
						{

							fseek ( fp, ( width * height * 16 ), SEEK_CUR );

							break;
						}
					}
				}

				while ( ( width > d3d_maximum_texture_width ) || ( height > d3d_maximum_texture_height ) )
				{

					width >>= 1;
					height >>= 1;
					number_of_mipmaps--;

					switch ( type )
					{

						case TEXTURE_TYPE_NOALPHA:
						case TEXTURE_TYPE_NOALPHA_NOPALETTE:
						{

							fseek ( fp, ( width * height * 12 ), SEEK_CUR );

							break;
						}

						case TEXTURE_TYPE_SINGLEALPHA:
						{

							fseek ( fp, ( width * height * 16 ), SEEK_CUR );

							break;
						}

						case TEXTURE_TYPE_MULTIPLEALPHA:
						{

							fseek ( fp, ( width * height * 16 ), SEEK_CUR );

							break;
						}
					}
				}

//VJ mip mapped textures are just one behind the other and width/height is halved

				if ( ( width != height ) && ( d3d_square_only_textures ) )
				{

					//
					// All textures have width >= height
					//

					this_texture = create_texture_map ( width, width, texture_format_type, number_of_mipmaps + 1,
																		system_texture_palettes[0], system_texture_colour_tables[0] );
				}
				else
				{

					this_texture = create_texture_map ( width, height, texture_format_type, number_of_mipmaps + 1,
																		system_texture_palettes[0], system_texture_colour_tables[0] );
				}

				system_textures[count] = this_texture;

				system_texture_info[count].texture_screen = this_texture;

				//
				// Now fill the data in
				//

				for ( temp = 0; temp <= number_of_mipmaps; temp++ )
				{


					if ( ( temp == 0 ) || ( d3d_mipmap_textures ) )
					{
//VJ# in C:\gms\Razorworks\eech-new\modules\graphics\textsys.c
#if ( ALLOW_TEXTURE_CREATION )
						while ( !lock_texture ( this_texture, temp ) )
						{

							Sleep ( 100 );
						}
#endif

						switch ( type )
						{

							case TEXTURE_TYPE_NOALPHA:
							case TEXTURE_TYPE_NOALPHA_NOPALETTE:
							{
//3 bytes for RGB
								fread ( texture_image_data, ( width * height * 3 ), 1, fp );

#if ( ALLOW_TEXTURE_CREATION )
								convert_no_alpha_24bit_texture_map_data ( texture_image_data, width, height, this_texture, fp, 0 );
#endif

								break;
							}

							case TEXTURE_TYPE_SINGLEALPHA:
							{
//4 bytes for RGBA

								fread ( texture_image_data, ( width * height * 4 ), 1, fp );

#if ( ALLOW_TEXTURE_CREATION )
								convert_single_alpha_32bit_texture_map_data ( texture_image_data, width, height, this_texture, fp );
#endif

								break;
							}

							case TEXTURE_TYPE_MULTIPLEALPHA:
							{

								fread ( texture_image_data, ( width * height * 4 ), 1, fp );

#if ( ALLOW_TEXTURE_CREATION )
								convert_multiple_alpha_32bit_texture_map_data ( texture_image_data, width, height, this_texture, fp, 0 );
#endif

								break;
							}
						}

#if ( ALLOW_TEXTURE_CREATION )
						unlock_texture ( this_texture );
#endif
					}
					else
					{

						// graphics card cannot handle mipmapping
						// Skip over the mipmap data
						//

						switch ( type )
						{

							case TEXTURE_TYPE_NOALPHA:
							case TEXTURE_TYPE_NOALPHA_NOPALETTE:
							{

								fseek ( fp, ( width * height * 3 ), SEEK_CUR );

								break;
							}

							case TEXTURE_TYPE_SINGLEALPHA:
							{

								fseek ( fp, ( width * height * 4 ), SEEK_CUR );

								break;
							}

							case TEXTURE_TYPE_MULTIPLEALPHA:
							{

								fseek ( fp, ( width * height * 4 ), SEEK_CUR );

								break;
							}
						}
					}

					width >>= 1;

					height >>= 1;
				}
			}
		}
//		fclose(fout);
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_no_alpha_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp )
{

	unsigned char
		value;

	int
		x,
		y;

	int
		y_count,
		y_repeat;

	if ( ( width > height ) && ( d3d_square_only_textures ) )
	{

		y_repeat = width / height;
	}
	else
	{

		y_repeat = 1;
	}

	if ( this_texture->palette )
	{

		//
		// We're dealing with a 8bit texture format - paletted
		//

		unsigned char
			*ptr;

		int
			pitch;

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			memcpy ( ptr, data, width );

			for ( y_count = 1; y_count < y_repeat; y_count++ )
			{

				memcpy ( &ptr[ ( y_count * pitch ) ], data, width );
			}

			ptr += ( y_repeat * pitch );

			data += width;
		}
	}
	else
	{

		if ( colour_texture_pixel_width <= 16 )
		{

			unsigned char
				*ptr;

			int
				pitch;

			unsigned short int
				pixel_value;

			//
			// We're dealing with a 16bit texture format.
			//

			initialise_set_texture_pixel_lookup_table ( this_texture );

			ptr = get_screen_data ( this_texture );

			pitch = get_screen_pitch ( this_texture );

			for ( y = 0; y < height; y++ )
			{

				for ( x = 0; x < width; x++ )
				{

					value = *data++;

					pixel_value = set_texture_pixel_lookup_table[value];

					*( ( unsigned short int * ) &ptr[( x * 2 )] ) = pixel_value;

					for ( y_count = 0; y_count < y_repeat; y_count++ )
					{

						*( ( unsigned short int * ) &ptr[( y_count * pitch ) + ( x * 2 )] ) = pixel_value;
					}
				}

				ptr += ( y_repeat * pitch );
			}
		}
		else
		{

			unsigned char
				*ptr;

			int
				pitch;

			unsigned int
				pixel_value;

			//
			// We're dealing with a 32 texture format.
			//

			initialise_set_texture_pixel_lookup_table ( this_texture );

			ptr = get_screen_data ( this_texture );

			pitch = get_screen_pitch ( this_texture );

			for ( y = 0; y < height; y++ )
			{

				for ( x = 0; x < width; x++ )
				{

					value = *data++;

					pixel_value = set_texture_pixel_32bit_lookup_table[value];

					*( ( unsigned int * ) &ptr[( x * 4 )] ) = pixel_value;

					for ( y_count = 0; y_count < y_repeat; y_count++ )
					{

						*( ( unsigned int * ) &ptr[( y_count * pitch ) + ( x * 4 )] ) = pixel_value;
					}
				}

				ptr += ( y_repeat * pitch );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_single_alpha_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp )
{

	int
		x,
		y,
		y_coordinate,
		y_count,
		y_repeat;

	if ( ( width > height ) && ( d3d_square_only_textures ) )
	{

		y_repeat = width / height;
	}
	else
	{

		y_repeat = 1;
	}

	if ( texture_formats[TEXTURE_TYPE_SINGLEALPHA].bpp_alpha )
	{

		y_coordinate = 0;

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				unsigned char
					value,
					alpha;

				value = *data++;

				if ( value )
				{

					alpha = 255;
				}
				else
				{

					alpha = 0;
				}

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					set_texture_pixel ( this_texture, x, ( y_coordinate + y_count ), value, alpha );
				}
			}

			y_coordinate += y_repeat;
		}
	}
	else
	{

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				unsigned char
					value;

				value = *data++;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					set_texture_pixel ( this_texture, x, ( y + y_count ), value, 0 );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_multiple_alpha_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp )
{

	int
		x,
		y,
		y_count,
		y_repeat;

	if ( ( width > height ) && ( d3d_square_only_textures ) )
	{

		y_repeat = width / height;
	}
	else
	{

		y_repeat = 1;
	}

	if ( texture_formats[TEXTURE_TYPE_MULTIPLEALPHA].bpp_alpha )
	{

		if ( multiple_alpha_texture_pixel_width <= 16 )
		{

			unsigned char
				*ptr;

			int
				pitch;

			initialise_set_texture_pixel_lookup_table ( this_texture );

			ptr = get_screen_data ( this_texture );

			pitch = get_screen_pitch ( this_texture );

			//
			// Performance tuned texture loader.
			//

			for ( y = 0; y < height; y++ )
			{

				unsigned short int
					*line_ptr;

				unsigned char
					*source_ptr;

				line_ptr = ( unsigned short int * ) ptr;

				source_ptr = data;

				for ( x = 0; x < width; x++ )
				{

					unsigned char
						colour,
						alpha;

					unsigned short int
						pixel_value;

					unsigned int
						texture_alpha;

					alpha = *source_ptr++;
					colour = *source_ptr++;

					pixel_value = set_texture_pixel_lookup_table[colour];

					texture_alpha = ( 255 - alpha );

					texture_alpha <<= 24;

					texture_alpha &= texture_multiple_alpha_alpha_mask;

					texture_alpha >>= texture_multiple_alpha_alpha_shift;

					pixel_value |= texture_alpha;

					*line_ptr++ = pixel_value;
				}

				//
				// Now copy that line of data
				//

				for ( y_count = 1; y_count < y_repeat; y_count++ )
				{

					memcpy ( &ptr[ ( y_count * pitch ) ], ptr, ( width * 2 ) );
				}

				ptr += ( y_repeat * pitch );

				data += ( width * 2 );
			}
		}
		else
		{

			unsigned char
				*ptr;

			int
				pitch;

			initialise_set_texture_pixel_lookup_table ( this_texture );

			ptr = get_screen_data ( this_texture );

			pitch = get_screen_pitch ( this_texture );

			for ( y = 0; y < height; y++ )
			{

				unsigned int
					*line_ptr;

				unsigned char
					*source_ptr;

				line_ptr = ( unsigned int * ) ptr;

				source_ptr = data;

				for ( x = 0; x < width; x++ )
				{

					unsigned char
						colour,
						alpha;

					unsigned int
						pixel_value;

					unsigned int
						texture_alpha;

					alpha = *source_ptr++;
					colour = *source_ptr++;

					pixel_value = set_texture_pixel_32bit_lookup_table[colour];

					texture_alpha = ( 255 - alpha );

					texture_alpha <<= 24;

					texture_alpha &= texture_multiple_alpha_alpha_mask;

					texture_alpha >>= texture_multiple_alpha_alpha_shift;

					pixel_value |= texture_alpha;

					*line_ptr++ = pixel_value;
				}

				//
				// Now copy that line of data
				//

				for ( y_count = 1; y_count < y_repeat; y_count++ )
				{

					memcpy ( &ptr[ ( y_count * pitch ) ], ptr, ( width * 4 ) );
				}

				ptr += ( y_repeat * pitch );

				data += ( width * 2 );
			}
		}
	}
	else
	{

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				unsigned char
					value,
					alpha;

				alpha = *data++;
				value = *data++;

				if ( alpha )
				{

					alpha = 0;
				}
				else
				{

					alpha = 255;
				}

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					set_texture_pixel ( this_texture, x, ( y + y_count ), value, alpha );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_no_alpha_24bit_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp, int reverse )
{

	int
		x,
		y;

	int
		y_count,
		y_repeat;

	unsigned int
		red,
		green,
		blue;

	if ( ( width > height ) && ( d3d_square_only_textures ) )
	{

		y_repeat = width / height;
	}
	else
	{

		y_repeat = 1;
	}

	if ( colour_nopalette_texture_pixel_width <= 16 )
	{

		unsigned char
			*ptr;

		int
			pitch;

		unsigned short int
			pixel_value;

		//
		// We're dealing with a 16bit texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{
				if (!reverse){
				red = *data++;
				green = *data++;
				blue = *data++;
				}else{				
				blue = *data++;
				green = *data++;
				red = *data++;
				}				

				red <<= 24;
				green <<= 24;
				blue <<= 24;

				red &= texture_colour_nopalette_red_mask;
				green &= texture_colour_nopalette_green_mask;
				blue &= texture_colour_nopalette_blue_mask;

				red >>= texture_colour_nopalette_red_shift;
				green >>= texture_colour_nopalette_green_shift;
				blue >>= texture_colour_nopalette_blue_shift;

				pixel_value = ( red | green | blue );

				*( ( unsigned short int * ) &ptr[( x * 2 )] ) = pixel_value;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					*( ( unsigned short int * ) &ptr[( y_count * pitch ) + ( x * 2 )] ) = pixel_value;
				}
			}

			ptr += ( y_repeat * pitch );
		}
	}
	else
	{

		unsigned char
			*ptr;

		int
			pitch;

		unsigned int
			pixel_value;

		//
		// We're dealing with a 32 texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				if (!reverse){
				red = *data++;
				green = *data++;
				blue = *data++;
				}else{				
				blue = *data++;
				green = *data++;
				red = *data++;
				}				

				red <<= 24;
				green <<= 24;
				blue <<= 24;

				red &= texture_colour_nopalette_red_mask;
				green &= texture_colour_nopalette_green_mask;
				blue &= texture_colour_nopalette_blue_mask;

				red >>= texture_colour_nopalette_red_shift;
				green >>= texture_colour_nopalette_green_shift;
				blue >>= texture_colour_nopalette_blue_shift;

				pixel_value = ( red | green | blue );

				*( ( unsigned int * ) &ptr[( x * 4 )] ) = pixel_value;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					*( ( unsigned int * ) &ptr[( y_count * pitch ) + ( x * 4 )] ) = pixel_value;
				}
			}

			ptr += ( y_repeat * pitch );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_single_alpha_32bit_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp )
{

	int
		x,
		y;

	int
		y_count,
		y_repeat;

	unsigned int
		red,
		green,
		blue,
		alpha;

	if ( ( width > height ) && ( d3d_square_only_textures ) )
	{

		y_repeat = width / height;
	}
	else
	{

		y_repeat = 1;
	}

	if ( single_alpha_texture_pixel_width <= 16 )
	{

		unsigned char
			*ptr;

		int
			pitch;

		unsigned short int
			pixel_value;

		//
		// We're dealing with a 16bit texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				red = *data++;
				green = *data++;
				blue = *data++;
				alpha = *data++;
				alpha = 255 - alpha;

				red <<= 24;
				green <<= 24;
				blue <<= 24;
				alpha <<= 24;

				red &= texture_single_alpha_red_mask;
				green &= texture_single_alpha_green_mask;
				blue &= texture_single_alpha_blue_mask;
				alpha &= texture_single_alpha_alpha_mask;

				red >>= texture_single_alpha_red_shift;
				green >>= texture_single_alpha_green_shift;
				blue >>= texture_single_alpha_blue_shift;
				alpha >>= texture_single_alpha_alpha_shift;

				pixel_value = ( red | green | blue | alpha );

				*( ( unsigned short int * ) &ptr[( x * 2 )] ) = pixel_value;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					*( ( unsigned short int * ) &ptr[( y_count * pitch ) + ( x * 2 )] ) = pixel_value;
				}
			}

			ptr += ( y_repeat * pitch );
		}
	}
	else
	{

		unsigned char
			*ptr;

		int
			pitch;

		unsigned int
			pixel_value;

		//
		// We're dealing with a 32 texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				red = *data++;
				green = *data++;
				blue = *data++;
				alpha = *data++;
				alpha = 255 - alpha;

				red <<= 24;
				green <<= 24;
				blue <<= 24;
				alpha <<= 24;

				red &= texture_single_alpha_red_mask;
				green &= texture_single_alpha_green_mask;
				blue &= texture_single_alpha_blue_mask;
				alpha &= texture_single_alpha_alpha_mask;

				red >>= texture_single_alpha_red_shift;
				green >>= texture_single_alpha_green_shift;
				blue >>= texture_single_alpha_blue_shift;
				alpha >>= texture_single_alpha_alpha_shift;

				pixel_value = ( red | green | blue | alpha );

				*( ( unsigned int * ) &ptr[( x * 4 )] ) = pixel_value;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					*( ( unsigned int * ) &ptr[( y_count * pitch ) + ( x * 4 )] ) = pixel_value;
				}
			}

			ptr += ( y_repeat * pitch );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_multiple_alpha_32bit_texture_map_data ( unsigned char *data, int width, int height, screen *this_texture, FILE *fp, int reverse )
{

	int
		x,
		y;

	int
		y_count,
		y_repeat;

	unsigned int
		red,
		green,
		blue,
		alpha;

	if ( ( width > height ) && ( d3d_square_only_textures ) )
	{

		y_repeat = width / height;
	}
	else
	{

		y_repeat = 1;
	}

	if ( multiple_alpha_texture_pixel_width <= 16 )
	{

		unsigned char
			*ptr;

		int
			pitch;

		unsigned short int
			pixel_value;

		//
		// We're dealing with a 16bit texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				if (!reverse){
					red = *data++;
					green = *data++;
					blue = *data++;
				}
				else{
					blue = *data++;
					green = *data++;
					red = *data++;
				}						
				alpha = *data++;
				alpha = 255 - alpha;

				red <<= 24;
				green <<= 24;
				blue <<= 24;
				alpha <<= 24;

				red &= texture_multiple_alpha_red_mask;
				green &= texture_multiple_alpha_green_mask;
				blue &= texture_multiple_alpha_blue_mask;
				alpha &= texture_multiple_alpha_alpha_mask;

				red >>= texture_multiple_alpha_red_shift;
				green >>= texture_multiple_alpha_green_shift;
				blue >>= texture_multiple_alpha_blue_shift;
				alpha >>= texture_multiple_alpha_alpha_shift;

				pixel_value = ( red | green | blue | alpha );

				*( ( unsigned short int * ) &ptr[( x * 2 )] ) = pixel_value;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					*( ( unsigned short int * ) &ptr[( y_count * pitch ) + ( x * 2 )] ) = pixel_value;
				}
			}

			ptr += ( y_repeat * pitch );
		}
	}
	else
	{

		unsigned char
			*ptr;

		int
			pitch;

		unsigned int
			pixel_value;

		//
		// We're dealing with a 32 texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				if (!reverse){
					red = *data++;
					green = *data++;
					blue = *data++;
				}
				else{
					blue = *data++;
					green = *data++;
					red = *data++;
				}						
				alpha = *data++;
				alpha = 255 - alpha;

				red <<= 24;
				green <<= 24;
				blue <<= 24;
				alpha <<= 24;

				red &= texture_multiple_alpha_red_mask;
				green &= texture_multiple_alpha_green_mask;
				blue &= texture_multiple_alpha_blue_mask;
				alpha &= texture_multiple_alpha_alpha_mask;

				red >>= texture_multiple_alpha_red_shift;
				green >>= texture_multiple_alpha_green_shift;
				blue >>= texture_multiple_alpha_blue_shift;
				alpha >>= texture_multiple_alpha_alpha_shift;

				pixel_value = ( red | green | blue | alpha );

				*( ( unsigned int * ) &ptr[( x * 4 )] ) = pixel_value;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					*( ( unsigned int * ) &ptr[( y_count * pitch ) + ( x * 4 )] ) = pixel_value;
				}
			}

			ptr += ( y_repeat * pitch );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen *get_system_texture_ptr ( int index )
{

	return ( system_textures[index] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_internal_texture_palettes ( void )
{

	int
		count;

	HRESULT
		ddrval;

	for ( count = 0; count < number_of_system_texture_palettes; count++ )
	{

		ddrval = IDirectDraw7_CreatePalette ( ddraw.ddraw, DDPCAPS_8BIT | DDPCAPS_ALLOW256,
															system_texture_colour_tables[count],
															&system_texture_palettes[count],
															NULL );

		if ( ddrval != DD_OK )
		{

			debug_log ( "Unable to create a texture palette: %s", get_ddraw_error_message ( ddrval ) );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen *create_texture_map ( int width, int height, texture_map_types type, int number_of_mipmaps, LPDIRECTDRAWPALETTE texture_palette, PALETTEENTRY *texture_colour_table )
{

	DDSURFACEDESC2
		ddsd;

	screen
		*texture;

	int
		texture_paletted;

	texture = get_free_screen ();

	texture->type = type;
	texture->width = width;
	texture->height = height;

	texture_paletted = FALSE;

	//
	// Allocate a system memory surface
	//

	memcpy ( &ddsd.ddpfPixelFormat, &texture_formats[type].format, sizeof ( DDPIXELFORMAT ) );

	texture_paletted = texture_formats[type].palette;

	texture->contains_alpha = ( texture_formats[type].bpp_alpha ) ? TRUE : FALSE;

	ddsd.dwSize = sizeof ( ddsd );
	ddsd.dwWidth = width;
	ddsd.dwHeight = height;
	ddsd.dwMipMapCount = 0;
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;

	if ( ( d3d_mipmap_textures ) && ( number_of_mipmaps > 1 ) )
	{

		ddsd.dwFlags |= DDSD_MIPMAPCOUNT;
		ddsd.ddsCaps.dwCaps |= DDSCAPS_COMPLEX | DDSCAPS_MIPMAP;
		ddsd.dwMipMapCount = number_of_mipmaps;
	}

	ddsd.ddsCaps.dwCaps2 = DDSCAPS2_HINTSTATIC | DDSCAPS2_D3DTEXTUREMANAGE;
	ddsd.ddsCaps.dwCaps3 = 0;
	ddsd.ddsCaps.dwCaps4 = 0;

#if ( ALLOW_TEXTURE_CREATION )
	{

		HRESULT
			ddrval;

		ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &texture->surface, NULL );

		if ( ddrval != DD_OK )
		{

			debug_fatal ( "Unable to create texture surface: %s ( %d, %d )", get_ddraw_error_message ( ddrval ), width, height );
		}

		//
		// Get the surface description to check the texture
		//

		ddsd.dwSize = sizeof ( ddsd );

		ddrval = IDirectDrawSurface7_GetSurfaceDesc ( texture->surface, &ddsd );

		if ( ddrval != DD_OK )
		{

			debug_fatal ( "Unable to get texture surface description: %s", get_ddraw_error_message ( ddrval ) );
		}

		//
		//
		//

		if ( ( d3d_mipmap_textures ) && ( number_of_mipmaps > 1 ) )
		{

			if ( ddsd.dwMipMapCount != number_of_mipmaps )
			{

				debug_log ( "CREATED TEXTURE WITH INCORRECT NUMBER OF MIPMAPS!" );
			}
		}

		//
		// Attach the palette now ( if necessary )
		//

		if ( texture_paletted )
		{

			ddrval = IDirectDrawSurface7_SetPalette ( texture->surface, texture_palette );

			if ( ddrval != DD_OK )
			{

				debug_fatal ( "Unable to set palette on texture: %s", get_ddraw_error_message ( ddrval ) );
			}

			texture->palette = texture_palette;
		}
		else
		{

			texture->palette = NULL;
		}
	}
#endif

	texture->used = TRUE;
	texture->colour_table = texture_colour_table;
	texture->clone_screen = FALSE;
	texture->do_not_destroy = TRUE;

	return ( texture );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_system_indexed_texture_map ( struct SCREEN *this_screen, int width, int height, int index, texture_map_types type )
{

	DDSURFACEDESC2
		ddsd;

	HRESULT
		ddrval;

	this_screen->type = type;
	this_screen->width = width;
	this_screen->height = height;
	this_screen->video_memory = FALSE;
	this_screen->locked = FALSE;
	this_screen->pitch = FALSE;
	this_screen->data = NULL;
	this_screen->pixel_length = 0;
	this_screen->used = TRUE;

	switch ( type )
	{

		case SCREEN_FORMAT_TYPE_NOALPHA:
		case SCREEN_FORMAT_TYPE_VIDEOSCREEN:
		case SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE:
		{

			this_screen->contains_alpha = FALSE;

			break;
		}

		case SCREEN_FORMAT_TYPE_MULTIPLEALPHA_16BITS:
		case SCREEN_FORMAT_TYPE_SINGLEALPHA:
		case SCREEN_FORMAT_TYPE_MULTIPLEALPHA:
		{

			this_screen->contains_alpha = TRUE;

			break;
		}
	}

	//
	// Allocate a system memory surface
	//

	memcpy ( &ddsd.ddpfPixelFormat, &texture_formats[type].format, sizeof ( DDPIXELFORMAT ) );

	ddsd.dwSize = sizeof ( ddsd );

	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;

	ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;

	ddsd.dwHeight = height;

	ddsd.dwWidth = width;

	ddsd.ddsCaps.dwCaps2 = DDSCAPS2_HINTDYNAMIC | DDSCAPS2_D3DTEXTUREMANAGE;
	ddsd.ddsCaps.dwCaps3 = 0;
	ddsd.ddsCaps.dwCaps4 = 0;

	ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &this_screen->surface, NULL );

	if ( ddrval != DD_OK )
	{

		debug_log ( "Unable to create texture surface: %s", get_ddraw_error_message ( ddrval ) );

		return ( FALSE );
	}

	//
	// Now duplicate this screen to the texture screen
	//

	system_textures[index] = this_screen;

	return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int match_system_texture_name ( char *name )
{

	char
		real_name[128];

	char
		*p,
		*ptr;

	int
		count, camo = 0;

	ptr = real_name;

	// convert to uppercase
	while ( ( *name != '\0' ) && ( *name != '.' ) )
	{

		*ptr++ = toupper ( *name++ );
	}
	*ptr++ = '\0';

	// throw away the first part of the name = the sub-directory of cohokum\graphics\textures
	// scan string for last occurence of '\\'
	// throw away that part
	//VJ 050319 texture colour mod, adjustment
	p = strrchr(real_name,'\\');
	p++;

	strcpy(real_name, p);

	//VJ 04/12/12 if textimpex name then delete -BIN-etc	24bit
	if (strstr(real_name, "-BIN"))
	{
		p = strstr(real_name, "-BIN");
	   real_name[strlen(real_name)-strlen(p)] = '\0';
	}

	//VJ 04/12/17 if textimpex name then delete -PAL-etc	8bit
	if (strstr(real_name, "-PAL"))
	{
		p = strstr(real_name, "-PAL");
	   real_name[strlen(real_name)-strlen(p)] = '\0';
	}

//VJ 04/12/12 increase count by 1 assuming the _DESERT of -D indicates a desert camoflage texture
	if (strstr(real_name, "BREEZE_BLOCKS_DESERT_CAMO"))
	{
		// this is the only name with _DESERT_ inside its name, must be an overview 
		// treat as an exception
		 return (385);
	}
	else
   if (strstr(real_name, DESERTIND_1))
   {
		//check for _DESERT
       real_name[strlen(real_name)-strlen(DESERTIND_1)] = '\0';
       camo = 1;
   }
   else
   if (strstr(real_name, DESERTIND_2))
   {
		//check for -D
       real_name[strlen(real_name)-strlen(DESERTIND_2)] = '\0';
       camo = 1;
   }

	for ( count = 0; count < number_of_system_textures; count++ )
	{
		if ( strcmp ( system_texture_names[count], real_name ) == 0 )
		{

			system_textures_referenced[count] = TRUE;

			return ( count + camo );
		}
	}
	
	// this crashes the game in an assert somewhere
	return ( -1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *get_system_texture_name ( int index )
{

	if ( ( index >= 0 ) && ( index < number_of_system_textures ) )
	{

		return ( system_texture_names[index] );
	}
	else
	{

		return ( NULL );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_system_texture_stats ( void )
{

	texture_map_types
		type;

	int
		count,
		total,
		width,
		height;

	type = TEXTURE_TYPE_NOALPHA;

	for ( width = 128; width > 0; width >>= 1 )
	{

		for ( height = 128; height > 0; height >>= 1 )
		{

			total = 0;

			for ( count = 0; count < number_of_system_textures; count++ )
			{

				if (	( system_textures[count]->type == type ) &&
						( system_textures[count]->width == width ) &&
						( system_textures[count]->height == height ) )
				{

					total++;
				}
			}

			if ( total )
			{

				debug_log ( "TYPE: NOALPHA ( %d, %d ) %d", width, height, total );
			}

			if ( total < 5 )
			{

				for ( count = 0; count < number_of_system_textures; count++ )
				{

					if (	( system_textures[count]->type == type ) &&
							( system_textures[count]->width == width ) &&
							( system_textures[count]->height == height ) )
					{

						debug_log ( "%s", system_texture_names[count] );
					}
				}
			}
		}
	}

	type = TEXTURE_TYPE_SINGLEALPHA;

	for ( width = 128; width > 0; width >>= 1 )
	{

		for ( height = 128; height > 0; height >>= 1 )
		{

			total = 0;

			for ( count = 0; count < number_of_system_textures; count++ )
			{

				if (	( system_textures[count]->type == type ) &&
						( system_textures[count]->width == width ) &&
						( system_textures[count]->height == height ) )
				{

					total++;
				}
			}

			if ( total )
			{

				debug_log ( "TYPE: SINGLEALPHA ( %d, %d ) %d", width, height, total );
			}

			if ( total < 5 )
			{

				for ( count = 0; count < number_of_system_textures; count++ )
				{

					if (	( system_textures[count]->type == type ) &&
							( system_textures[count]->width == width ) &&
							( system_textures[count]->height == height ) )
					{

						debug_log ( "%s", system_texture_names[count] );
					}
				}
			}
		}
	}

	type = TEXTURE_TYPE_MULTIPLEALPHA;

	for ( width = 128; width > 0; width >>= 1 )
	{

		for ( height = 128; height > 0; height >>= 1 )
		{

			total = 0;

			for ( count = 0; count < number_of_system_textures; count++ )
			{

				if (	( system_textures[count]->type == type ) &&
						( system_textures[count]->width == width ) &&
						( system_textures[count]->height == height ) )
				{

					total++;
				}
			}

			if ( total )
			{

				debug_log ( "TYPE: MULTIPLEALPHA ( %d, %d ) %d", width, height, total );
			}

			if ( total < 5 )
			{

				for ( count = 0; count < number_of_system_textures; count++ )
				{

					if (	( system_textures[count]->type == type ) &&
							( system_textures[count]->width == width ) &&
							( system_textures[count]->height == height ) )
					{

						debug_log ( "%s", system_texture_names[count] );
					}
				}
			}
		}
	}

	for ( count = 0; count < number_of_system_textures; count++ )
	{

		if (	( system_textures[count]->type == TEXTURE_TYPE_NOALPHA ) &&
				( system_textures[count]->width == 128 ) )
		{

			debug_log ( "NOALPHA: %s: %d, %d", system_texture_names[count], system_textures[count]->width, system_textures[count]->height );
		}
	}
	for ( count = 0; count < number_of_system_textures; count++ )
	{

		if (	( system_textures[count]->type == TEXTURE_TYPE_SINGLEALPHA ) &&
				( system_textures[count]->width == 128 ) )
		{

			debug_log ( "SINGLE_ALPHA: %s: %d, %d", system_texture_names[count], system_textures[count]->width, system_textures[count]->height );
		}
	}

	for ( count = 0; count < number_of_system_textures; count++ )
	{

		if (	( system_textures[count]->type == TEXTURE_TYPE_MULTIPLEALPHA ) &&
				( system_textures[count]->width == 128 ) )
		{

			debug_log ( "MULTIPLE_ALPHA: %s: %d, %d", system_texture_names[count], system_textures[count]->width, system_textures[count]->height );
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

texture_graphic *create_texture_graphic ( char *filename )
{

	int
		width,
		height,
		channels,
		texture_x,
		texture_y,
		x,
		y,
		count,
		texture_width_power,
		texture_width_mask,
		texture_height_power,
		texture_height_mask,
		temp,
		base_texture_index;

	char
		*data;

	char
		**texture_data;

	int
		*texture_pitch;

	texture_graphic
		*graphic;

	screen
		*old_active_screen;

	texture_map_types
		type;

	old_active_screen = get_active_screen ();

	data = load_psd_file ( filename, &width, &height, &channels );

	if ( ( d3d_total_video_texture_memory < 8192*1024 ) && ( ( width > 64 ) || ( height > 64 ) ) )
	{

		if ( channels ==  3 )
		{

			psd_rgb
				*dest,
				*source;

			source = ( psd_rgb * ) data;

			dest = ( psd_rgb * ) data;

			for ( y = 0; y < height; y += 2 )
			{

				for ( x = 0; x < width; x += 2 )
				{

					*dest++ = source[ y*width + x ];
				}
			}
		}
		else if ( channels ==  4 )
		{

			psd_rgba
				*dest,
				*source;

			source = ( psd_rgba * )  data;

			dest = ( psd_rgba * )  data;

			for ( y = 0; y < height; y += 2 )
			{

				for ( x = 0; x < width; x += 2 )
				{

					*dest++ = source[ y*width + x ];
				}
			}
		}

		width += ( width & 1 );
		height += ( height & 1 );
		width /= 2;
		height /= 2;
	}

	graphic = safe_malloc ( sizeof ( texture_graphic ) );

	{

		int
			texture_width,
			texture_height,
			finished;

		texture_width = 16;
		texture_height = 16;
		finished = FALSE;

		while ( !finished )
		{

			if ( ( texture_width >= d3d_maximum_texture_width ) || ( texture_height >= d3d_maximum_texture_height ) )
			{

				finished = TRUE;
			}
			else
			{

				if ( ( texture_width >= width ) && ( texture_height >= height ) )
				{

					finished = TRUE;
				}

				if ( texture_width < width )
				{

					texture_width *= 2;
				}

				if ( texture_height < height )
				{

					texture_height *= 2;
				}
			}
		}

		if ( d3d_square_only_textures  )
		{

			if ( texture_width != texture_height )
			{

				texture_width = max ( texture_width, texture_height );

				texture_height = texture_width;
			}
		}

		graphic->texture_width = texture_width;
		graphic->texture_height = texture_height;
	}

	graphic->graphic_width = width;
	graphic->graphic_height = height;
	graphic->number_of_textures_wide = width / graphic->texture_width;

	if ( ( graphic->number_of_textures_wide * graphic->texture_width ) != width )
	{

		graphic->number_of_textures_wide++;
	}

	graphic->number_of_textures_high = height / graphic->texture_height;

	if ( ( graphic->number_of_textures_high * graphic->texture_height ) != height )
	{

		graphic->number_of_textures_high++;
	}

	ASSERT ( ( channels == 3 ) || ( channels == 4 ) );

	if ( channels == 3 )
	{

		type = TEXTURE_TYPE_NOALPHA_NOPALETTE;

		graphic->transparent = FALSE;
	}
	else
	{

		type = TEXTURE_TYPE_MULTIPLEALPHA_16BIT;

		graphic->transparent = TRUE;
	}

	//
	// Set up the texture shifts & masks
	//

	texture_width_power = 0;

	temp = graphic->texture_width;

	while ( temp != 1 )
	{

		temp >>= 1;

		texture_width_power++;
	}

	texture_height_power = 0;

	temp = graphic->texture_height;

	while ( temp != 1 )
	{

		temp >>= 1;

		texture_height_power++;
	}

	texture_width_mask = graphic->texture_width - 1;

	texture_height_mask = graphic->texture_height - 1;

	//
	// Allocate the textures
	//

	graphic->number_of_textures = graphic->number_of_textures_wide * graphic->number_of_textures_high;

	graphic->textures = safe_malloc ( sizeof ( texture_graphic_texture ) * graphic->number_of_textures );

	count = 0;

	for ( texture_y = 0; texture_y < graphic->number_of_textures_high; texture_y++ )
	{

		for ( texture_x = 0; texture_x < graphic->number_of_textures_wide; texture_x++ )
		{

			float
				umax,
				vmax;

			umax = 1.0;
			vmax = 1.0;

			if ( texture_x == ( graphic->number_of_textures_wide - 1 ) )
			{

				if ( ( graphic->number_of_textures_wide * graphic->texture_width ) > graphic->graphic_width )
				{

					float
						last_width;

					last_width = graphic->graphic_width - ( ( graphic->number_of_textures_wide - 1 ) * graphic->texture_width );

					umax = ( last_width / ( float ) graphic->texture_width );
				}
			}

			if ( texture_y == ( graphic->number_of_textures_high - 1 ) )
			{

				if ( ( graphic->number_of_textures_high * graphic->texture_height ) > graphic->graphic_height )
				{

					float
						last_height;

					last_height = graphic->graphic_height - ( ( graphic->number_of_textures_high - 1 ) * graphic->texture_height );

					vmax = ( last_height / ( float ) graphic->texture_height );
				}
			}

			graphic->textures[count].umax = umax;
			graphic->textures[count].vmax = vmax;
			graphic->textures[count].texture = create_user_texture_screen ( graphic->texture_width, graphic->texture_height, type, 0 );

			count++;
		}
	}

	//
	// Set active screen to initialise the screen format bitmasks & shifts
	//

	set_active_screen ( graphic->textures[0].texture );

	//
	// Grab pointers & pitches of all the texture screens
	//

	texture_data = safe_malloc ( sizeof ( char * ) * graphic->number_of_textures );

	texture_pitch = safe_malloc ( sizeof ( int ) * graphic->number_of_textures );

	for ( count = 0; count < graphic->number_of_textures; count++ )
	{

		if ( !lock_screen ( graphic->textures[count].texture ) )
		{

			debug_fatal ( "Unable to lock screen during load_texture_graphic" );
		}

		texture_data[count] = get_screen_data ( graphic->textures[count].texture );

		texture_pitch[count] = get_screen_pitch ( graphic->textures[count].texture );
	}

	if ( channels == 3 )
	{

		psd_rgb
			*ptr;

		ptr = ( psd_rgb * ) data;

		if ( get_screen_pixel_width ( active_screen ) == 2 )
		{

			for ( y = 0; y < height; y++ )
			{

				texture_y = y >> texture_height_power;

				base_texture_index = texture_y * graphic->number_of_textures_wide;

				for ( x = 0; x < width; x++ )
				{

					int
						pixel_x;

					unsigned int
						red,
						green,
						blue;

					unsigned short int
						*pixels;

					unsigned short int
						value;

					texture_x = x >> texture_width_power;

					pixel_x = x & texture_width_mask;

					pixels = ( unsigned short int * ) texture_data[base_texture_index + texture_x];

					red = ( ( unsigned int ) ptr->r ) << 24;
					green = ( ( unsigned int ) ptr->g ) << 24;
					blue = ( ( unsigned int ) ptr->b ) << 24;

					red &= active_screen_red_mask;
					green &= active_screen_green_mask;
					blue &= active_screen_blue_mask;

					red >>= active_screen_red_shift;
					green >>= active_screen_green_shift;
					blue >>= active_screen_blue_shift;

					value =  ( red | green | blue );

					pixels[pixel_x] = value;

					ptr++;
				}

				for ( count = 0; count < graphic->number_of_textures_wide; count++ )
				{

					texture_data[base_texture_index + count] += texture_pitch[base_texture_index + count];
				}
			}
		}
		else
		{

			for ( y = 0; y < height; y++ )
			{

				texture_y = y >> texture_height_power;

				base_texture_index = texture_y * graphic->number_of_textures_wide;

				for ( x = 0; x < width; x++ )
				{

					int
						pixel_x;

					unsigned int
						red,
						green,
						blue;

					unsigned int
						*pixels;

					unsigned int
						value;

					texture_x = x >> texture_width_power;

					pixel_x = x & texture_width_mask;

					pixels = ( unsigned int * ) texture_data[base_texture_index + texture_x];

					red = ( ( unsigned int ) ptr->r ) << 24;
					green = ( ( unsigned int ) ptr->g ) << 24;
					blue = ( ( unsigned int ) ptr->b ) << 24;

					red &= active_screen_red_mask;
					green &= active_screen_green_mask;
					blue &= active_screen_blue_mask;

					red >>= active_screen_red_shift;
					green >>= active_screen_green_shift;
					blue >>= active_screen_blue_shift;

					value =  ( red | green | blue );

					pixels[pixel_x] = value;

					ptr++;
				}

				for ( count = 0; count < graphic->number_of_textures_wide; count++ )
				{

					texture_data[base_texture_index + count] += texture_pitch[base_texture_index + count];
				}
			}
		}
	}
	else
	{

		psd_rgba
			*ptr;

		ptr = ( psd_rgba * ) data;

		if ( get_screen_pixel_width ( active_screen ) == 2 )
		{

			for ( y = 0; y < height; y++ )
			{

				texture_y = y >> texture_height_power;

				base_texture_index = texture_y * graphic->number_of_textures_wide;

				for ( x = 0; x < width; x++ )
				{

					int
						pixel_x;

					unsigned int
						red,
						green,
						blue,
						alpha;

					unsigned short int
						*pixels;

					unsigned short int
						value;

					texture_x = x >> texture_width_power;

					pixel_x = x & texture_width_mask;

					pixels = ( unsigned short int * ) texture_data[base_texture_index + texture_x];

					red = ( ( unsigned int ) ptr->r ) << 24;
					green = ( ( unsigned int ) ptr->g ) << 24;
					blue = ( ( unsigned int ) ptr->b ) << 24;
					alpha = ( ( unsigned int ) ptr->a ) << 24;

					red &= active_screen_red_mask;
					green &= active_screen_green_mask;
					blue &= active_screen_blue_mask;
					alpha &= active_screen_alpha_mask;

					red >>= active_screen_red_shift;
					green >>= active_screen_green_shift;
					blue >>= active_screen_blue_shift;
					alpha >>= active_screen_alpha_shift;

					value =  ( red | green | blue | alpha );

					pixels[pixel_x] = value;

					ptr++;
				}

				for ( count = 0; count < graphic->number_of_textures_wide; count++ )
				{

					texture_data[base_texture_index + count] += texture_pitch[base_texture_index + count];
				}
			}
		}
		else
		{

			for ( y = 0; y < height; y++ )
			{

				texture_y = y >> texture_height_power;

				base_texture_index = texture_y * graphic->number_of_textures_wide;

				for ( x = 0; x < width; x++ )
				{

					int
						pixel_x;

					unsigned int
						red,
						green,
						blue,
						alpha;

					unsigned int
						*pixels;

					unsigned int
						value;

					texture_x = x >> texture_width_power;

					pixel_x = x & texture_width_mask;

					pixels = ( unsigned int * ) texture_data[base_texture_index + texture_x];

					red = ( ( unsigned int ) ptr->r ) << 24;
					green = ( ( unsigned int ) ptr->g ) << 24;
					blue = ( ( unsigned int ) ptr->b ) << 24;
					alpha = ( ( unsigned int ) ptr->a ) << 24;

					red &= active_screen_red_mask;
					green &= active_screen_green_mask;
					blue &= active_screen_blue_mask;
					alpha &= active_screen_alpha_mask;

					red >>= active_screen_red_shift;
					green >>= active_screen_green_shift;
					blue >>= active_screen_blue_shift;
					alpha >>= active_screen_alpha_shift;

					value =  ( red | green | blue | alpha );

					pixels[pixel_x] = value;

					ptr++;
				}

				for ( count = 0; count < graphic->number_of_textures_wide; count++ )
				{

					texture_data[base_texture_index + count] += texture_pitch[base_texture_index + count];
				}
			}
		}
	}

	//
	// Unlock the textures
	//

	for ( count = 0; count < graphic->number_of_textures; count++ )
	{

		unlock_screen ( graphic->textures[count].texture );
	}

	safe_free ( texture_data );

	safe_free ( texture_pitch );

	set_active_screen ( old_active_screen );

	//
	// Free up the psd stuff
	//

	safe_free ( data );

	return ( graphic );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_texture_graphic ( texture_graphic *graphic )
{

	int
		count;

	for ( count = 0; count < graphic->number_of_textures; count++ )
	{

		destroy_screen ( graphic->textures[count].texture );
	}

	safe_free ( graphic->textures );

	safe_free ( graphic );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_texture_graphic_source_dimensions ( texture_graphic *graphic, int *width, int *height )
{

	ASSERT ( graphic );
	ASSERT ( width );
	ASSERT ( height );

	*width = graphic->graphic_width;

	*height = graphic->graphic_height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start VJ custom texture mod
// based on work by Have_Quick 12/2/2003
// 05/01/15, 050116, 050118
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_texture_override_names ( void )
{
	int count;
	for ( count = 0; count < MAX_TEXTURES; count++ )
   	system_texture_override_names[count][0] = '\0';
  	override_present = FALSE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this function is called from \aphavoc\source\app3d\3d_init.c, line 123
void load_custom_textures ( void )
{
	int count = 0;

	// empty all the strings
	clear_texture_override_names ();

	initialize_texture_override_names ( system_texture_override_names, "." );

	initialize_texture_override_names ( system_texture_override_names, TEXTURE_OVERRIDE_DIRECTORY_COCKPIT );

	initialize_texture_override_names ( system_texture_override_names, TEXTURE_OVERRIDE_DIRECTORY_CAMO );

	initialize_texture_override_names ( system_texture_override_names, TEXTURE_OVERRIDE_DIRECTORY_TERRAIN );

	load_texture_override ( system_texture_override_names );

	memset ( backup_system_textures, 0, sizeof ( backup_system_textures ) );

	//make a backup of the pointers
	//while (system_texture_override_names[count][0] != '\0' && count < MAX_TEXTURES)
	for (count = 0; count < number_of_system_textures; count++)
	{
		backup_system_textures[count] = system_textures[count];
		backup_system_texture_info[count] = system_texture_info[count];
		
		//count++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_texture_override ( char system_texture_override_names[MAX_TEXTURES][128])
{

	FILE
		*fp, *fpa;

// VJ 041217 bitmap header info: http://msdn.microsoft.com/library/default.asp?url=/library/en-us/gdi/bitmaps_5f8y.asp
	BITMAPFILEHEADER
		bmfh, bmfha;

	BITMAPINFOHEADER
		bmih, bmiha;

	char
		*buffer, *buffera, *buffer4;

	char
		full_override_texture_filename[128],
		full_override_texture_filename_a[128];

	int
		count, temp, mipmap, alpha,
		width, height, 
		buffer_size;


	//VJ 041217 palette for 8 bit textures
	rgb_colour 
		pal[256];

	//static
	screen
		*override_screen;

	// Now that all the screens are loaded we check to see if there is are any overrides
	for( count=0; count < MAX_TEXTURES; count++ )
	{
		int retrieved_index = 0;

		if (system_texture_override_names[count][0] != '\0')		   
			retrieved_index = match_system_texture_name ( system_texture_override_names[count] );

		if( retrieved_index > 0)
		{

			sprintf ( full_override_texture_filename, "%s\\%s.bmp", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count] );

			debug_log ("++OVERRIDES++ looking for file %s",full_override_texture_filename);

			if ( !file_exist ( full_override_texture_filename ) )
				continue;

			//VJ 050426 destroy texture that is to be replaced
			if ( system_textures[retrieved_index]->palette )
			{
				IDirectDrawSurface7_SetPalette ( system_textures[retrieved_index]->surface, NULL );
				system_textures[retrieved_index]->palette = NULL;
			}
			release_texture_surface ( &system_textures[retrieved_index]->surface );
	
			// check nr of mipmap levels;			
			mipmap = 1;
			sprintf ( full_override_texture_filename, "%s\\%s_%d.bmp", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count], mipmap );
			while (file_exist ( full_override_texture_filename ) )
			{
				mipmap++;
				sprintf ( full_override_texture_filename, "%s\\%s_%d.bmp", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count], mipmap ); 
			}
			mipmap--;

		//if (mipmap > 0) debug_fatal("mipmap %s %d",full_override_texture_filename,mipmap);		

			// check alpha presence
			sprintf ( full_override_texture_filename, "%s\\%s_a.bmp", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count]);
			alpha = 0;
			if (file_exist ( full_override_texture_filename )) alpha = 1;
		
//VJ mipmapping, set mipmap to 0 for now, itnworks but still beta stage
mipmap = 0;			
alpha = 0;

			for ( temp = 0; temp <= mipmap; temp++ )
			{
	   		
				if (temp == 0)
					sprintf ( full_override_texture_filename, "%s\\%s.bmp", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count] );
				else
					sprintf ( full_override_texture_filename, "%s\\%s_%d.bmp", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count], temp ); 

				fp = safe_fopen (full_override_texture_filename, "rb");
				
				fread (&bmfh, sizeof (bmfh), 1, fp);
      	
				//read bitmap header info structure
				fread (&bmih, sizeof (bmih), 1, fp);   			
   			//VJ 041217 if it is a 8bit texture read the palette, structure rgb_colour
   			
				if (bmih.biBitCount == 8){
 	   			fread (&pal, sizeof (pal), 1, fp);
 				}
 				
				
				//check bitmap header for correct format
      		if (!check_bitmap_header ( bmih, full_override_texture_filename) )
      		{
					safe_fclose (fp);
      			return;
      		}      	

				if (alpha > 0)
				{
					if (temp == 0)
						sprintf ( full_override_texture_filename_a, "%s\\%s_a.bmp", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count] );
					else
						sprintf ( full_override_texture_filename_a, "%s\\%s_%d_a.bmp", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count], temp ); 										

					fpa = safe_fopen (full_override_texture_filename_a, "rb");
			
					fread (&bmfha, sizeof (bmfha), 1, fpa);
      	
					fread (&bmiha, sizeof (bmiha), 1, fpa);   			
					if (bmih.biBitCount == 8)
 		   			fread (&pal, sizeof (pal), 1, fp);
				}


    			  	
				//VJ 050426 create a new texture map with mipmap levels if needed
				width = bmih.biWidth;
				height = bmih.biHeight;
				//C:\gms\Razorworks\eech-new\modules\graphics\scrnstr.h
				if (temp == 0)
				{
						if (alpha == 0)
						{
							override_screen = create_texture_map (width, height, TEXTURE_TYPE_NOALPHA_NOPALETTE, 
				         	       	   mipmap+1, system_texture_palettes[0], system_texture_colour_tables[0] );
				      }
				      else
				      {
							override_screen = create_texture_map (width, height, TEXTURE_TYPE_SINGLEALPHA, 
				         	       	   mipmap+1, system_texture_palettes[0], system_texture_colour_tables[0] );
						}				         	       	   
			   }   	       	   
   			     	
			   if (bmih.biBitCount == 24)
				   buffer_size = width * height * 3;
				// note color depth is assumed here
				
			   //if (bmih.biBitCount == 8)
			     // buffer_size = width * height;
      	
				buffer = safe_malloc (buffer_size);
      	
				fread (buffer, buffer_size, 1, fp);

				if (alpha > 0)
				{					
					buffer4 = safe_malloc (width * height * 4);      	
					if (bmih.biBitCount == 8)					
						buffera = safe_malloc (width * height);      	
					else
						buffera = safe_malloc (buffer_size);      	
						
					fread (buffera, buffer_size, 1, fp);
				}	
      	
				while ( !lock_texture ( override_screen, temp ) )
				{
					Sleep ( 100 );
				}
   		/*
				if (alpha > 0)
				{
					int i, j = 0;
	   			for (i = 0; i < width*height*4; i+=4)
   				{
   					buffer4[i] = buffer[j+2];
   					buffer4[i+1] = buffer[j+1];
   					buffer4[i+2] = buffer[j];
   					buffer4[i+3] = buffera[j]==255 ? 255 : 0;//buffer[j] > 10 ? 255: 0; //buffera[j];
	   				j++;//j += 3;
   				}
   			}	
   			*/
				//only for NON PALETTE files
				if (alpha == 0)
					convert_no_alpha_24bit_texture_map_data ( buffer, width, height , override_screen, fp, 1 );
				else	
					convert_single_alpha_32bit_texture_map_data_v ( buffer, buffera, width, height , override_screen);
				
				unlock_texture ( override_screen );
				
				safe_free (buffer);

				safe_fclose (fp);

				if (alpha > 0)
				{
					safe_free (buffera);
					safe_free (buffer4);
					safe_fclose (fpa);
				}					
			}

			// now we set the pointer in the system textxures array to point to this
			// screen rather than the original screen
			set_system_texture_screen (override_screen, retrieved_index);

			//VJ 04/12/12 add the sreen also to this array because the function set_texture_camoflage uses it and it is called after this stuff
			system_texture_info[retrieved_index].texture_screen = override_screen;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialize_texture_override_names ( char system_texture_override_names[MAX_TEXTURES][128], char *mapname )
{

	directory_file_list
		*directory_listing;

	int
		valid_file,
		index = 0;

	unsigned char
		directory_search_path[256],
		*filename;

	// go to place where no names are stored yet, more dirs can be read in one go
	while (system_texture_override_names[index][0] != '\0' && index < MAX_TEXTURES) 
	   index++;

	sprintf (directory_search_path, "%s\\%s\\*.bmp", TEXTURE_OVERRIDE_DIRECTORY, mapname);

	directory_listing = get_first_directory_file ( directory_search_path );
	
	if ( directory_listing )
	{
		valid_file = TRUE;

		while ( valid_file )
		{
			if ( get_directory_file_type ( directory_listing ) == DIRECTORY_FILE_TYPE_FILE )
			{
				filename = strupr(get_directory_file_filename ( directory_listing ));

				debug_log ("++TEXTURE OVERRIDES++ found override file %s %d", filename, index );

				//we don't want the .bmp in the overides index
				filename[strlen(filename) - 4] = '\0';

				if (index < MAX_TEXTURES)
					sprintf (system_texture_override_names[index], "%s\\%s", mapname, filename);
				//avoid overflow, not likely because of fixed name list
				
				index++;
			}
			valid_file = get_next_directory_file ( directory_listing );
		}
	}

//VJ 050515 do the same for dds files and continue index++
	sprintf (directory_search_path, "%s\\%s\\*.dds", TEXTURE_OVERRIDE_DIRECTORY, mapname);

	directory_listing = get_first_directory_file ( directory_search_path );
	
	if ( directory_listing )
	{
		valid_file = TRUE;

		while ( valid_file )
		{
			if ( get_directory_file_type ( directory_listing ) == DIRECTORY_FILE_TYPE_FILE )
			{
				filename = strupr(get_directory_file_filename ( directory_listing ));

				debug_log ("++TEXTURE OVERRIDES++ found override file %s %d", filename, index );

				//we don't want the .dds in the overides index
				filename[strlen(filename) - 4] = '\0';

				if (index < MAX_TEXTURES)
					sprintf (system_texture_override_names[index], "%s\\%s", mapname, filename);
				//avoid overflow, not likely because of fixed name list
				
				index++;
			}
			valid_file = get_next_directory_file ( directory_listing );
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ load warzone specific textures, called from \aphavoc\source\ai\faction\faction.c line 142
void load_warzone_override_textures (char *warzone_name)
{
	char directory_textdir_path[256];

	// empty name database
	clear_texture_override_names ();

	sprintf (directory_textdir_path, "%s\\%s\\texturedirs.txt",TEXTURE_OVERRIDE_DIRECTORY,warzone_name);

	debug_log("Overide dir warzone name %s", warzone_name);

	if ( file_exist ( directory_textdir_path ) )
	{
//		int count;
		FILE *ftextdir;
		char buf[256];
		char *p;

		ftextdir = fopen(directory_textdir_path,"r");

		// skip comment lines
		fscanf(ftextdir,"%[^\n]\n",buf);
		while (buf[0] == '#')
				fscanf(ftextdir,"%[^\n]\n",buf);

		// get directory names, can be more than one
		while (strchr(buf,'='))
		{
			//format: dir1=[name] etc.
			p = strtok(buf,"=");
			p = strtok(NULL,"#");

			if (p)
			{
				int i;
				//strip leading and trailing spaces
				i = strlen(p)-1;
				while (i > 0 && p[i] == ' ')
					i--;
				p[i+1]='\0';
				while (p[0] == ' ')
				  p++;

				// get override texture names in array
				initialize_texture_override_names ( system_texture_override_names, p );		
				
				override_present = TRUE;

				#if DEBUG_MODULE
				for (count = 0; count < number_of_system_textures; count++ )
				{
					int retrieved_index;			
			   	if (system_texture_override_names[count][0] != '\0')
			   	{
						retrieved_index = match_system_texture_name ( system_texture_override_names[count] );
						debug_log("Texture override +++ warzone screen %d (%d) : %s",retrieved_index,count,system_texture_override_names[count]);
					}
				}
				#endif				
			}
			// get the next specified dir
			fscanf(ftextdir,"%[^\n]\n",buf);
		}

   	// load and replace the default texures and all the textures that were loaded at startup (in textuser.c)
   	if (override_present)
			load_texture_override ( system_texture_override_names );

	}

	//VJ 050319 texture colour mod, load terrain textures
	if (command_line_texture_colour == 1)
	{
		if (strstr(warzone_name, "map1" )) sprintf (directory_textdir_path, "%s\\thailand",TEXTURE_OVERRIDE_DIRECTORY_TERRAIN);
		if (strstr(warzone_name, "map2" )) sprintf (directory_textdir_path, "%s\\cuba"    ,TEXTURE_OVERRIDE_DIRECTORY_TERRAIN);
		if (strstr(warzone_name, "map3" )) sprintf (directory_textdir_path, "%s\\georgia" ,TEXTURE_OVERRIDE_DIRECTORY_TERRAIN);
		if (strstr(warzone_name, "map4" )) sprintf (directory_textdir_path, "%s\\taiwan"  ,TEXTURE_OVERRIDE_DIRECTORY_TERRAIN);
		if (strstr(warzone_name, "map5" )) sprintf (directory_textdir_path, "%s\\lebanon" ,TEXTURE_OVERRIDE_DIRECTORY_TERRAIN);
		if (strstr(warzone_name, "map6" )) sprintf (directory_textdir_path, "%s\\yemen"   ,TEXTURE_OVERRIDE_DIRECTORY_TERRAIN);

		debug_log(" === texture colour mod dir:  %s",directory_textdir_path);

		//TEXTURE_OVERRIDE_DIRECTORY is concatinated in functions 
		initialize_texture_override_names ( system_texture_override_names, directory_textdir_path );
		
		load_texture_override ( system_texture_override_names );

//VJ mipmapping dds files still under construction, just ignore
//		load_texture_override_dds ( system_texture_override_names );

		initialize_terrain_texture_scales ( directory_textdir_path );

		//VJ 050412 flag to destroy later on
		//override_present = TRUE;
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//restore pointers to default + startup override textures
void restore_default_textures ( void )
{
	int count = 0;

 	if (override_present)
 	{
	   while (system_texture_override_names[count][0] != '\0' && count < MAX_TEXTURES)
	   {
			int retrieved_index = match_system_texture_name ( system_texture_override_names[count] );
	
			debug_log("Texture override +++ destroyed screen %d (%d) : %s",retrieved_index,count,system_texture_override_names[count]);
		
			if (system_textures[ retrieved_index] && system_textures[ retrieved_index]->surface)
			   destroy_screen ( system_textures[ retrieved_index] );
	
			system_textures[retrieved_index] = backup_system_textures[retrieved_index];
			system_texture_info[retrieved_index] = backup_system_texture_info[retrieved_index];
	
			count++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050322 texture colour mod, function to read texture scale file
void initialize_terrain_texture_scales ( char *mapname )
{
	char filename[128];

	sprintf (filename, "%s\\%s\\texture_scales.txt", TEXTURE_OVERRIDE_DIRECTORY, mapname);

  debug_log("===TEXTURE SCALES DIRECTORY=== %s",filename);

	global_infrared = -1;
	// initialize infra red
	
	if ( file_exist ( filename ) )
	{
		FILE *fin;
		char buf[256];
		char *p;
		int c, index, count;
		
		fin = fopen(filename,"r");

		// skip comment lines
		fscanf(fin,"%[^\n]\n",buf);
		while (buf[0] == '#')
				fscanf(fin,"%[^\n]\n",buf);

		for (count = 0; count < 64; count ++)
		{
			texture_override_scales[count][0] = 0;
			texture_override_scales[count][1] = 64; //safe value
			texture_override_scales[count][2] = 64; //safe value
		}
		
		count = 0;
		while (count < 64 && 
				 strchr(buf,'=') && (strstr(buf,"TERRAIN") || strstr(buf,"CITY")))			
		{			
			int i;
			p = strtok(buf,"=");

			//scan name
			if (p)
			{
				//strip leading and trailing spaces
				i = strlen(p)-1;
				
				while (i > 0 && (p[i] == ' ' || p[i] == '\t'))
//				while (i > 0 && p[i] == ' ')
					i--;
				p[i+1]='\0';
				while (p[0] == ' ')
				  p++;
				index = -1;

				for ( c = 0; c < number_of_system_textures; c++ )
				{
					if ( strcmp ( system_texture_names[c], p ) == 0 )
					{
						index = c;
						break;
					}
				}				
				texture_override_scales[count][0] = index;
			}				  
			
/*
			//scan 1st scale
			p = strtok(NULL,",");
			if (p)
			{		
				texture_override_scales[count][1] = atoi(p);						  
			}				  
*/			
			//scan 2nd scale
			p = strtok(NULL,"#");
			if (p)
			{		
				texture_override_scales[count][1] = atoi(p);						  
			}				  

			fscanf(fin,"%[^\n]\n",buf);			
			// next line
			
			debug_log("===scales %d %d %d",count, texture_override_scales[count][0], texture_override_scales[count][1]);		
			count++;
		}
		fclose(fin);
	}			  
}	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End VJ custom texture mod
// based on work by Have_Quick 12/2/2003
// 05/01/15, 050116, 050118
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_bitmap_header ( BITMAPINFOHEADER bmih, char *full_override_texture_filename )
{  	   	
	if (bmih.biCompression != BI_RGB)
	{
		debug_log ("%s is not uncompressed RGB!", full_override_texture_filename );
		return 0;
	}
   	
	//VJ only 8 and 24 bit uncompressed bitmaps are read
	if (bmih.biBitCount != 8 && bmih.biBitCount != 24)
	{
		debug_log ("%s is not 24 bit!", full_override_texture_filename );
		return 0;
	}
   	
	if (bmih.biHeight > MAX_TEXTURE_WIDTH)
	{
		debug_log ("%s taller than the maximum allowed", full_override_texture_filename );
		return 0;
	}
   	
	if (bmih.biWidth > MAX_TEXTURE_WIDTH)
	{
		debug_fatal ("%s wider than the maximum allowed", full_override_texture_filename );
		return 0;
	}
	return 1;
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_single_alpha_32bit_texture_map_data_v ( unsigned char *data, unsigned char *dataa, int width, int height, screen *this_texture )
{

	int
		x,
		y;

	int
		y_count,
		y_repeat;

	unsigned int
		red,
		green,
		blue,
		alpha;

	if ( ( width > height ) && ( d3d_square_only_textures ) )
	{

		y_repeat = width / height;
	}
	else
	{

		y_repeat = 1;
	}

	if ( single_alpha_texture_pixel_width <= 16 )
	{

		unsigned char
			*ptr;

		int
			pitch;

		unsigned short int
			pixel_value;

		//
		// We're dealing with a 16bit texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				blue = *data++;
				green = *data++;
				red = *data++;
				alpha = *dataa++;
				
				alpha = 255 - alpha;

				red <<= 24;
				green <<= 24;
				blue <<= 24;
				alpha <<= 24;
/*
				red &= texture_single_alpha_red_mask;
				green &= texture_single_alpha_green_mask;
				blue &= texture_single_alpha_blue_mask;
				alpha &= texture_single_alpha_alpha_mask;

				red >>= texture_single_alpha_red_shift;
				green >>= texture_single_alpha_green_shift;
				blue >>= texture_single_alpha_blue_shift;
				alpha >>= texture_single_alpha_alpha_shift;
*/

				red &= texture_multiple_alpha_red_mask;
				green &= texture_multiple_alpha_green_mask;
				blue &= texture_multiple_alpha_blue_mask;
				alpha &= texture_multiple_alpha_alpha_mask;

				red >>= texture_multiple_alpha_red_shift;
				green >>= texture_multiple_alpha_green_shift;
				blue >>= texture_multiple_alpha_blue_shift;
				alpha >>= texture_multiple_alpha_alpha_shift;


				pixel_value = ( red | green | blue | alpha );

				*( ( unsigned short int * ) &ptr[( x * 2 )] ) = pixel_value;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					*( ( unsigned short int * ) &ptr[( y_count * pitch ) + ( x * 2 )] ) = pixel_value;
				}
			}

			ptr += ( y_repeat * pitch );
		}
	}
	else
	{

		unsigned char
			*ptr;

		int
			pitch;

		unsigned int
			pixel_value;

		//
		// We're dealing with a 32 texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				blue = *data++;
				green = *data++;
				red = *data++;
				alpha = *dataa++;
				alpha = 255 - alpha;

				red <<= 24;
				green <<= 24;
				blue <<= 24;
				alpha <<= 24;

/*
				red &= texture_single_alpha_red_mask;
				green &= texture_single_alpha_green_mask;
				blue &= texture_single_alpha_blue_mask;
				alpha &= texture_single_alpha_alpha_mask;
				
				
				red >>= texture_single_alpha_red_shift;
				green >>= texture_single_alpha_green_shift;
				blue >>= texture_single_alpha_blue_shift;
				alpha >>= texture_single_alpha_alpha_shift;
*/
				red &= texture_multiple_alpha_red_mask;
				green &= texture_multiple_alpha_green_mask;
				blue &= texture_multiple_alpha_blue_mask;
				alpha &= texture_multiple_alpha_alpha_mask;

				red >>= texture_multiple_alpha_red_shift;
				green >>= texture_multiple_alpha_green_shift;
				blue >>= texture_multiple_alpha_blue_shift;
				alpha >>= texture_multiple_alpha_alpha_shift;

				pixel_value = ( red | green | blue | alpha );

				*( ( unsigned int * ) &ptr[( x * 4 )] ) = pixel_value;

				for ( y_count = 0; y_count < y_repeat; y_count++ )
				{

					*( ( unsigned int * ) &ptr[( y_count * pitch ) + ( x * 4 )] ) = pixel_value;
				}
			}

			ptr += ( y_repeat * pitch );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ mipmapping dds files still under construction, just ignore

void load_texture_override_dds ( char system_texture_override_names[MAX_TEXTURES][128])
{

	FILE
		*fp;

	DDSURFACEDESC2 ddsh;
	DWORD dwmagic;
	
	int type;
	
	char
		*buffer;

	char
		full_override_texture_filename[128];

	int
		count, temp, mipmap,
		width, height, 
		buffer_size;

	//static
	screen
		*override_screen;

	// Now that all the screens are loaded we check to see if there is are any overrides
	for( count=0; count < MAX_TEXTURES; count++ )
	{
		int retrieved_index = 0;

		if (system_texture_override_names[count][0] != '\0')		   
			retrieved_index = match_system_texture_name ( system_texture_override_names[count] );

		if( retrieved_index > 0)
		{

			sprintf ( full_override_texture_filename, "%s\\%s.dds", TEXTURE_OVERRIDE_DIRECTORY, system_texture_override_names[count] );

			debug_log ("++OVERRIDES DDS++ looking for file %s",full_override_texture_filename);

			if ( !file_exist ( full_override_texture_filename ) )
				continue;

			//VJ 050426 destroy texture that is to be replaced
			if ( system_textures[retrieved_index]->palette )
			{
				IDirectDrawSurface7_SetPalette ( system_textures[retrieved_index]->surface, NULL );
				system_textures[retrieved_index]->palette = NULL;
			}
			release_texture_surface ( &system_textures[retrieved_index]->surface );
	
	
			fp = safe_fopen (full_override_texture_filename, "rb");
			fread (&dwmagic, sizeof (dwmagic), 1, fp);

			fread (&ddsh, sizeof (ddsh), 1, fp);
			
			if ( ddsh.dwFlags & DDSD_LINEARSIZE )
			{
			 	debug_fatal("Compressed dds files not supported: %s",full_override_texture_filename);
			}  
			
			if ( ddsh.ddpfPixelFormat.dwFlags & DDPF_FOURCC  )
			{
			 	debug_fatal("Only RGB dds files supported: %s",full_override_texture_filename);
			}  

			mipmap = ddsh.dwMipMapCount;

//C:\gms\Razorworks\eech-new\modules\graphics\textsys.h			
			if (ddsh.ddpfPixelFormat.dwFlags & DDPF_ALPHAPIXELS )
				type = TEXTURE_TYPE_MULTIPLEALPHA;
			else	
				type = TEXTURE_TYPE_NOALPHA_NOPALETTE;
				
		//			debug_fatal("type %d %d %s",type, mipmap,full_override_texture_filename);
			width = ddsh.dwWidth;
			height = ddsh.dwHeight;

			override_screen = create_texture_map (width, height, type, mipmap+1, system_texture_palettes[0], system_texture_colour_tables[0] );
			//override_screen = create_texture_map_dds (type, ddsh);


			for ( temp = 0; temp <= mipmap; temp++ )
			{

				//VJ 050426 create a new texture map with mipmap levels if needed
				//C:\gms\Razorworks\eech-new\modules\graphics\scrnstr.h				
   			     	
			   buffer_size = width * height * (ddsh.ddpfPixelFormat.dwRGBBitCount >> 3);
				buffer = safe_malloc (buffer_size);     	
				fread (buffer, buffer_size, 1, fp);
				
 				while ( !lock_texture ( override_screen, temp ) )
				{
					Sleep ( 100 );
				}
				
				if (type == TEXTURE_TYPE_NOALPHA_NOPALETTE)
					convert_no_alpha_24bit_texture_map_data ( buffer, width, height, override_screen, fp, 1 );
				if (type == TEXTURE_TYPE_MULTIPLEALPHA)
					convert_multiple_alpha_32bit_texture_map_data ( buffer, width, height, override_screen, fp, 1);
				
				unlock_texture ( override_screen );
				
				safe_free (buffer);

				width >>= 1;
				height >>= 1;

			}

			safe_fclose (fp);
			
			// now we set the pointer in the system textxures array to point to this
			// screen rather than the original screen
			set_system_texture_screen (override_screen, retrieved_index);

			//VJ 04/12/12 add the sreen also to this array because the function set_texture_camoflage uses it and it is called after this stuff
			system_texture_info[retrieved_index].texture_screen = override_screen;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ mipmapping dds files still under construction, just ignore
screen *create_texture_map_dds ( int type, DDSURFACEDESC2 ddsd )
{

	screen
		*texture;

	HRESULT
		ddrval;

	texture = get_free_screen ();

	texture->type = type;
	texture->width = 	ddsd.dwWidth;
	texture->height = ddsd.dwHeight;

	//texture_paletted = texture_formats[type].palette;

	texture->contains_alpha = FALSE;//( texture_formats[type].bpp_alpha ) ? TRUE : FALSE;

	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
	//ddsd.dwMipMapCount += 1;
	/*
	if ( ( d3d_mipmap_textures ) && ( number_of_mipmaps > 1 ) )
	{

		ddsd.dwFlags |= DDSD_MIPMAPCOUNT;
		ddsd.ddsCaps.dwCaps |= DDSCAPS_COMPLEX | DDSCAPS_MIPMAP;
		ddsd.dwMipMapCount = number_of_mipmaps;
	}
*/
	ddsd.ddsCaps.dwCaps2 = DDSCAPS2_HINTSTATIC | DDSCAPS2_D3DTEXTUREMANAGE;
	ddsd.ddsCaps.dwCaps3 = 0;
	ddsd.ddsCaps.dwCaps4 = 0;


		ddrval = IDirectDraw7_CreateSurface ( ddraw.ddraw, &ddsd, &texture->surface, NULL );

		if ( ddrval != DD_OK )
		{

			debug_fatal ( "Unable to create texture surface: %s ", get_ddraw_error_message ( ddrval ));
		}

		//
		// Get the surface description to check the texture
		//

		ddsd.dwSize = sizeof ( ddsd );

		ddrval = IDirectDrawSurface7_GetSurfaceDesc ( texture->surface, &ddsd );

		if ( ddrval != DD_OK )
		{

			debug_fatal ( "Unable to get texture surface description: %s", get_ddraw_error_message ( ddrval ) );
		}

		texture->palette = NULL;

		texture->used = TRUE;
		texture->colour_table = NULL;//texture_colour_table;
		texture->clone_screen = FALSE;
		texture->do_not_destroy = TRUE;

	return ( texture );
}
