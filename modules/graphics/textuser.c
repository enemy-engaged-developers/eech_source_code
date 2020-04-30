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
// VJ 050619
// CUSTOM TEXTURE CHANGES
// All custom textures are now read when you enter the warzone
// the call is made from the function "
// first a list is made in which the filenames are stored from the correct textures (that is those names
// that appear in the list. The directories are read in a specific order:
// razorworks\cohokum\graphics\textures
// razorworks\cohokum\graphics\textures\cockpit
// razorworks\cohokum\graphics\textures\camo
// razorworks\cohokum\graphics\textures\terrain
// then according to the warzone (map1-map10)
// the file texturedirs.txt is read and any directory names in it, e.g. if "alaska" is found
// the directory razorworks\cohokum\graphics\textures\alaska is searched and
// the textures are put into the list. If a texture name already exists it is overwritten, so that the
// last occurence i the one used.
// Last if the eech.ini option "texture_colour=1" is set, the terrain textures specific to
// the warzones are read, of map1-map6 only (the others have only one texture)


// a list of pointers is stored in these structures
//    *backup_system_textures[MAX_TEXTURES];
//    backup_system_texture_info[MAX_TEXTURES];
// in flight.c the warzone specific textures are loaded and
// in flight.c the default textures are restored after the flight
// warzone textures are created and destroyed, the default custom textures are created but never destroyed.
//
// SCREEN defined in modules\graphics\scrnstr.h
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ 050814 NOTE:
// - bmp bitmaps are always considered 24 bit RGB non-mipmap and non-alpha blended
// - dds are 24 bit RGB format and may contains mipmaps, and may contain an alpha channel
//   the format with alpha is: unsigned 32 bit A8R8G8B8
// - eech wants the format BRG so red and blue channel are swapped on reading

//texture names are in eech-new\modules\3d\textname.h
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics.h"
#include "project.h"

//VJ 051223 changed to project.h to access get_current_game_session()
//this includes cmndline.h and global.h needed for texture colour mod and winter textures


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define ALLOW_TEXTURE_CREATION 1

// VJ 04/12/12 desert camouflage texture name indicator
#define TEXTSUFFIX_SIZE 2
#define TEXTSUFFIX_DESERT "-D"
//VJ 051011 add winter textures
#define TEXTSUFFIX_WINTER "-W"

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

#ifndef OGRE_EE
	screen
		*texture_screen = nullptr;
#endif
};

typedef struct SYSTEM_TEXTURE_INFORMATION system_texture_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TEXTURE_NAME_HASH_ENTRY
{

	int
		hash = 0,
		texture_index = 0;

	struct TEXTURE_NAME_HASH_ENTRY
		*succ = nullptr;
};

typedef struct TEXTURE_NAME_HASH_ENTRY texture_name_hash_entry;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_system_textures,
	texture_sprite_index,
	number_of_system_texture_camoflages;

#ifndef OGRE_EE
screen
	*system_textures[MAX_TEXTURES],
	//VJ 050116 custom texture mod: backup textures to restore default
	*backup_system_textures[MAX_TEXTURES];
#endif

system_texture_information
	system_texture_info[MAX_TEXTURES],
	//VJ 050116 custom texture mod: backup textures to restore default
	backup_system_texture_info[MAX_TEXTURES];

char
	system_texture_names[MAX_TEXTURES][128];

texture_name_hash_entry
	system_texture_name_hashes[MAX_TEXTURES];

texture_name_hash_entry
	*system_texture_name_hash_table[256];

char
	new_texture_sources[MAX_TEXTURES][260];

static int
	texture_camoflage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ 050618 structures for custom textures
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 041212 organization of texture directory
#define TEXTURE_OVERRIDE_DIRECTORY "..\\COHOKUM\\GRAPHICS\\TEXTURES"
#define TEXTURE_OVERRIDE_DIRECTORY_COCKPIT "COCKPIT"
#define TEXTURE_OVERRIDE_DIRECTORY_TERRAIN "TERRAIN"
#define TEXTURE_OVERRIDE_DIRECTORY_CAMO "CAMO"
//VJ 050814 dynamic water and general directories
#define TEXTURE_OVERRIDE_DIRECTORY_WATER "TERRAIN\\WATER"
#define TEXTURE_OVERRIDE_DIRECTORY_GENERAL "GENERAL"
#define TEXTURE_OVERRIDE_DIRECTORY_ANIMATION "ANIMATION"
#define TEXTURE_OVERRIDE_DIRECTORY_TEMP "TEMP"

enum FILE_TYPE
{
	TYPE_ORIGINAL,
	TYPE_BMP,
	TYPE_DDS,
	TYPE_TGA,
};

typedef enum FILE_TYPE file_type;

enum CAMO_TYPE
{
	CAMO_REGULAR,
	CAMO_WINTER,
	CAMO_DESERT,
};

typedef enum CAMO_TYPE camo_type;

struct OVERRIDENAME
{
	char name[64]; //texture name
	char path[260];  //full path+file name on disk
	file_type type;
//VJ 051011 add winter textures
	camo_type camo;
};

typedef struct OVERRIDENAME overridename;

overridename
	system_texture_override_names[MAX_TEXTURES];

//VJ 050621 backup of commandline
static int
	texture_colour_bak = -1;

//VJ 040814 dynamic water
//VJ 051226 moved to map info structure
//terrain_dynamic_water_info
	//water_info[3]; // sea, river, reservoir

//VJ 051225 moved all map info to one structure
custom_map_info
	current_map_info;

#ifdef OGRE_EE
static const unsigned char
	white[4] = { 0xFF, 0xFF, 0xFF, 0 };
#endif

static const unsigned char
	*textures_bin = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static unsigned get_hash(const char* name);
static void add_texture_to_name_hash(unsigned texture_index);

#ifndef OGRE_EE
void convert_no_alpha_24bit_texture_map_data ( const unsigned char *data, int width, int height, screen *this_texture );

void convert_single_alpha_32bit_texture_map_data ( const unsigned char *data, int width, int height, screen *this_texture );

void convert_multiple_alpha_32bit_texture_map_data ( const unsigned char *data, int width, int height, screen *this_texture );
#endif

//VJ 050619 the following functions are used in custom texture mods, in this file only

//VJ 050814 cleaned up differences between dds and bmp download
static int check_bitmap_header ( BITMAPINFOHEADER bmih, const char *full_override_texture_filename );
static int initialize_texture_override_names ( const char *mapname );
static void load_texture_override ( void );
static void clear_texture_override_names ( void );
#ifndef OGRE_EE
static screen *load_dds_file_screen (const char *full_override_texture_filename, int step, float gamma_adjustment);
static screen *load_tga_file_screen (const char *full_override_texture_filename, int step, float gamma_adjustment);
#endif
static void load_texture_water( void );
static void initialize_terrain_texture_scales ( const char *mapname );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 04/12/12 comment: set = 0 for default or 1 for desert
void set_texture_camoflage ( int set )
{
	texture_camoflage = set;
}

#ifndef OGRE_EE
static void real_set_texture_camoflage ( int set )
{
	int
		count;

#ifdef DEBUG
	for ( count = 0; count < number_of_system_textures; count++ )
	{
		int
			camo;
		camo = system_texture_info[count].flags.number_of_camoflage_textures;
		if ( camo )
		{
			int
				index;
			for ( index = 1; index <= camo; index++ )
			{
				if ( !system_texture_info[count + index].flags.camoflage_texture || system_texture_info[count + index].flags.camoflage_index != index )
				{
					#if DEBUG_MODULE
					debug_log ( "Error: Texture: %s has incorrect camoflage name", system_texture_names[count] );
					#endif
				}
			}
		}
	}
#endif

	for ( count = 0; count < number_of_system_textures; count++ )
	{
		if ( system_texture_info[count].flags.number_of_camoflage_textures )
		{
			screen
				*texture = nullptr;
			texture = system_texture_info[count + set].texture_screen;
			if ( texture )
			{
				system_textures[count] = texture;
			}
		}
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void release_system_textures ( void )
{

#if ( !DEBUG )
/*
	int
		count;

	//
	// Release the system memory textures
	//

	for ( count = 0; count < MAX_TEXTURES; count++ )
	{

		if ( system_textures[count].used )
		{

			release_texture_surface ( &system_textures[count].surface );

			system_textures[count].used = FALSE;
		}
	}
	*/
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_system_texture_index ( const char *name )
{
	int
		hash,
		hash_index;

	texture_name_hash_entry
		*entry = nullptr;
	int
		length = strlen ( name );
	char
		real_name[256];
	int
		offset;
	int
		camo;

	memcpy ( real_name, name, length + 1 );
	strupr ( real_name );

	camo = 0;
	offset = length - TEXTSUFFIX_SIZE;
	if ( offset > 0 && !memcmp ( real_name + offset, TEXTSUFFIX_DESERT, TEXTSUFFIX_SIZE ) )
	{
		real_name[offset] = 0;
		camo = 1;
	}

	hash = get_hash ( real_name );
	hash_index = hash & 0xff;


	for ( entry = system_texture_name_hash_table[hash_index]; entry; entry = entry->succ )
	{
		if ( entry->hash == hash &&
			!strcmp ( system_texture_names[entry->texture_index], real_name ) &&
			!system_texture_info[entry->texture_index].flags.camoflage_texture )
		{
			return ( entry->texture_index );
		}
	}

	return ( -1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL load_texturemap_data ( const char *path )
{

	int
		count;

	int
		width,
		height,
		type;

	texture_map_types
		texture_format_type;

	const unsigned char
		*fp = nullptr;

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

	sprintf ( filename, "%s\\textures.bin", path );

	textures_bin = static_cast<unsigned char*>(mopen ( filename ));

#define fread(dst, size, nmemb, ptr) do { memcpy((dst), (ptr), (size) * (nmemb)); (ptr) += (size) * (nmemb); } while (0)
#define fseek(ptr, size, where) ((ptr) += (size))

	fp = textures_bin;

	//
	// First integer is the number of palettes the textures use in total.
	//

	fread ( &count, 4, 1, fp );

	fseek ( fp, count * 1024, SEEK_CUR );

	fread ( &number_of_system_textures, 4, 1, fp );
	ASSERT ( number_of_system_textures == TEXTURE_INDEX_LAST_DEFAULT_INDEX + 1 );

	#if DEBUG_MODULE
	debug_log ( "Reading in %d textures", number_of_system_textures );
	#endif

	{

// deleted a chunk here that was commented out

//VJ 24 bit texture loading
		for ( count = 0; count < number_of_system_textures; count++ )
		{

			int
				temp,
				length,
				number_of_mipmaps;

			unsigned int
				value;

			screen
				*this_texture = nullptr;

			texture_flags
				flags;

			fread ( &value, sizeof ( unsigned int ), 1, fp );

			flags.flags = value;

			system_texture_info[count].flags.flags = flags.flags;

			system_texture_info[count].texture_screen = NULL;

			memset ( system_texture_names[count], 0, 128 );

			fread ( &length, sizeof ( length ), 1, fp );

			fread ( system_texture_names[count], length, 1, fp );

			strupr ( system_texture_names[count] );

			add_texture_to_name_hash ( count );

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

				texture_format_type = (texture_map_types) type;

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

				this_texture = create_texture_map ( width, height, texture_format_type, number_of_mipmaps + 1 );

				system_textures[count] = this_texture;

				system_texture_info[count].texture_screen = this_texture;


				//
				// Now fill the data in
				//

				for ( temp = 0; temp <= number_of_mipmaps; temp++ )
				{


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
#if ( ALLOW_TEXTURE_CREATION )
								convert_no_alpha_24bit_texture_map_data ( fp, width, height, this_texture );
#endif

								//3 bytes for RGB
								fseek ( fp, ( width * height * 3 ), SEEK_CUR );

								break;
							}

							case TEXTURE_TYPE_SINGLEALPHA:
							{
#if ( ALLOW_TEXTURE_CREATION )
								convert_single_alpha_32bit_texture_map_data ( fp, width, height, this_texture );
#endif

								//4 bytes for RGBA
								fseek ( fp, ( width * height * 4 ), SEEK_CUR );

								break;
							}

							case TEXTURE_TYPE_MULTIPLEALPHA:
							{
#if ( ALLOW_TEXTURE_CREATION )
								convert_multiple_alpha_32bit_texture_map_data ( fp, width, height, this_texture );
#endif

								fseek ( fp, ( width * height * 4 ), SEEK_CUR );

								break;
							}
						}

#if ( ALLOW_TEXTURE_CREATION )
						unlock_texture ( this_texture );
#endif
					}
#if 0
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
#endif

					width >>= 1;

					height >>= 1;
				}
			}
		}//for count to number_of_system_textures
	}

#undef fread
#undef fseek

	mclose ( ( void * ) textures_bin );

	register_exit_function ( &restore_default_textures );

	// adjust for texture indices added since EECH was released (i.e. not in the big texures-file)
	number_of_system_textures = TEXTURE_INDEX_LAST;

	texture_sprite_index = add_new_texture("SPRITE_LIGHT", "");

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unload_texturemap_data ( void )
{
	int
		count;

	for ( count = 0; count < MAX_TEXTURES; count++ )
	{
		if ( system_texture_info[count].texture_screen )
		{
			f3d_texture_release ( system_texture_info[count].texture_screen );

			system_texture_info[count].texture_screen->used = FALSE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_no_alpha_24bit_texture_map_data ( const unsigned char *data, int width, int height, screen *this_texture )
{

	int
		x,
		y;

	{

		unsigned int
			*ptr = nullptr;

		int
			pitch;

		rgb_colour
			colour;

		//
		// We're dealing with a 32 texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				colour.r = *data++;
				colour.g = *data++;
				colour.b = *data++;

				ptr[x] = colour.colour;
			}

			ptr += pitch;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_single_alpha_32bit_texture_map_data ( const unsigned char *data, int width, int height, screen *this_texture )
{

	int
		x,
		y;


	{

		unsigned int
			*ptr = nullptr;

		int
			pitch;

		rgb_colour
			colour;

		//
		// We're dealing with a 32 texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				colour.r = *data++;
				colour.g = *data++;
				colour.b = *data++;
				colour.alpha = ~*data++;

				ptr[x] = colour.colour;
			}

			ptr += pitch;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_multiple_alpha_32bit_texture_map_data ( const unsigned char *data, int width, int height, screen *this_texture )
{

	int
		x,
		y;


	{

		unsigned int
			*ptr = nullptr;

		int
			pitch;

		real_colour
			colour;

		//
		// We're dealing with a 32 texture format.
		//

		ptr = get_screen_data ( this_texture );

		pitch = get_screen_pitch ( this_texture );

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				colour.r = *data++;
				colour.g = *data++;
				colour.b = *data++;
				colour.alpha = ~*data++;

				ptr[x] = colour.colour;
			}

			ptr += pitch;
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

screen *create_texture_map ( int width, int height, texture_map_types type, int number_of_mipmaps )
{
	screen
		*texture = nullptr;

	texture = get_free_screen ();

	f3d_texture_create ( texture, width, height, number_of_mipmaps, TEXTURE_MAP_ALPHA(type) ? TEXTURE_ROLE_STATIC_RGBA : TEXTURE_ROLE_STATIC_RGBX );

	texture->used = TRUE;

	return ( texture );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_system_indexed_texture_map ( struct SCREEN *this_screen, int width, int height, int index, enum TEXTURE_MAP_TYPES type )
{
	f3d_texture_create ( this_screen, width, height, 1, TEXTURE_MAP_ALPHA(type) ? TEXTURE_ROLE_DYNAMIC_RGBA : TEXTURE_ROLE_DYNAMIC_RGBX );

	system_textures[index] = this_screen;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050619 this function assumes that the name has no path information
//and is the filename with extention only, which it should be to work with the rest
static int match_system_texture_name ( const char *name, camo_type* camo )
{
	char
		real_name[128];

	char
		*ptr = nullptr;

	int
		index;

	ptr = real_name;
	// convert to uppercase and strip filename extention
	while ( ( *name != '\0' ) && ( *name != '.' ) )
	{
		*ptr++ = toupper ( *name++ );
	}
	*ptr = '\0';

	*camo = CAMO_REGULAR;

	if ( ptr - real_name > TEXTSUFFIX_SIZE )
	{
		ptr -= TEXTSUFFIX_SIZE;
		if ( !memcmp ( ptr, TEXTSUFFIX_DESERT, TEXTSUFFIX_SIZE ) )
		{
			//check for -D
			*ptr = '\0';
			*camo = CAMO_DESERT;
		}
		else if ( !memcmp ( ptr, TEXTSUFFIX_WINTER, TEXTSUFFIX_SIZE ) )
		{
			//VJ 051011 add winter textures
			//check for -W
			*ptr = '\0';
			*camo = CAMO_WINTER;
		}
	}

	index = get_system_texture_index ( real_name );
	if ( index < 0 )
	{
		return -1;
	}

	if ( *camo == CAMO_DESERT && system_texture_info[index].flags.number_of_camoflage_textures )
	{
		index++;
	}

	#if DEBUG_MODULE
	debug_log("Texture file %s %i %i\n", real_name, index, *camo);
	#endif

	return index;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_system_texture_name ( int index )
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
#if 0
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

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

texture_graphic *create_texture_graphic ( const char *filename, int ref_count )
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
		*data = nullptr;

	unsigned
		**texture_data;

	int
		*texture_pitch = nullptr;

	texture_graphic
		*graphic = nullptr;

	screen
		*old_active_screen = nullptr;

	texture_map_types
		type;

	old_active_screen = get_active_screen ();

	data = ( char * ) load_psd_file ( filename, &width, &height, &channels );

	/*if ( ( d3d_total_video_texture_memory < 8192*1024 ) && ( ( width > 64 ) || ( height > 64 ) ) )
	{

		if ( channels == 3 )
		{

			psd_rgb
				*dest = nullptr,
				*source = nullptr;

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
		else if ( channels == 4 )
		{

			psd_rgba
				*dest = nullptr,
				*source = nullptr;

			source = ( psd_rgba * ) data;

			dest = ( psd_rgba * ) data;

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
	}*/

	graphic = ( texture_graphic * ) safe_malloc ( sizeof ( texture_graphic ) );

	graphic->ref_count = ref_count;

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

	graphic->textures = ( texture_graphic_texture * ) safe_malloc ( sizeof ( texture_graphic_texture ) * graphic->number_of_textures );

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
			graphic->textures[count].texture = create_user_texture_screen ( graphic->texture_width, graphic->texture_height, type, 1 );

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

	texture_data = ( unsigned * * ) safe_malloc ( sizeof ( unsigned * ) * graphic->number_of_textures );

	texture_pitch = ( int * ) safe_malloc ( sizeof ( int ) * graphic->number_of_textures );

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
			*ptr = nullptr;

		ptr = ( psd_rgb * ) data;

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
						*pixels = nullptr;

					rgb_colour
						value;

					texture_x = x >> texture_width_power;

					pixel_x = x & texture_width_mask;

					pixels = texture_data[base_texture_index + texture_x];

					value.red = ptr->r;
					value.green = ptr->g;
					value.blue = ptr->b;
					value.alpha = 0;

					pixels[pixel_x] = value.colour;

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
			*ptr = nullptr;

		ptr = ( psd_rgba * ) data;

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
						*pixels = nullptr;

					rgb_colour
						value;

					texture_x = x >> texture_width_power;

					pixel_x = x & texture_width_mask;

					pixels = texture_data[base_texture_index + texture_x];

					value.red = ptr->r;
					value.green = ptr->g;
					value.blue = ptr->b;
					value.alpha = ptr->a;

					pixels[pixel_x] = value.colour;

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

	ASSERT ( graphic );
	ASSERT ( graphic->ref_count > 0 );

	graphic->ref_count--;

	if ( graphic->ref_count )
	{
		return;
	}

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

texture_graphic *texture_graphic_addref ( texture_graphic *graphic )
{
	ASSERT ( graphic );
	ASSERT ( graphic->ref_count >= 0 );

	graphic->ref_count++;

	return graphic;
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
	{
		system_texture_override_names[count].name[0] = '\0';
		system_texture_override_names[count].path[0] = '\0';
		system_texture_override_names[count].type = TYPE_ORIGINAL;
		system_texture_override_names[count].camo = CAMO_REGULAR;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050619 this function scans the directory for bmp and dds files that occur in the texture list
// and puts them in the override names structure.
// NOTE: dds files take preference over bmp files.
// NOTE: if a name already exists from previous calls to this function they are overwritten
int initialize_texture_override_names ( const char *mapname )
{
	directory_file_list
		*directory_listing = nullptr;

	int
		count = 0;

	char
		directory_search_path[260],
		filename[260];

	camo_type
		overrider = CAMO_REGULAR;

	switch (get_global_season())
	{
	case SESSION_SEASON_WINTER:
		overrider = CAMO_WINTER;
		break;
	case SESSION_SEASON_DESERT:
		overrider = CAMO_DESERT;
		break;
	default:
		break;
	}

	snprintf (directory_search_path, sizeof (directory_search_path), "%s\\%s\\*", TEXTURE_OVERRIDE_DIRECTORY, mapname);
	directory_listing = get_first_directory_file ( directory_search_path );
	if ( !directory_listing )
		return 0;

	do
	{
		switch ( get_directory_file_type ( directory_listing ) )
		{
		case DIRECTORY_FILE_TYPE_DIRECTORY:
			{
				{
					const char
						*this_entry = get_directory_file_filename ( directory_listing );

					if (*this_entry == '.')
					{
						break;
					}

					snprintf(filename, sizeof(filename), "%s\\%s", mapname, this_entry);
					strupr(filename);

					#if DEBUG_MODULE
					debug_log("Entering directory %s", filename);
					#endif

					count += initialize_texture_override_names(filename);
				}
				break;
			}
		case DIRECTORY_FILE_TYPE_FILE:
			{
				int
					index;
				camo_type
					camo;
				const char*
					extension;
				file_type
					type = TYPE_ORIGINAL;

				strcpy(filename, get_directory_file_filename ( directory_listing ));
				strupr(filename);

				extension = strrchr(filename, '.');
				if (!extension)
				{
					#if DEBUG_MODULE
					debug_log("No extension for file: %s", filename);
					#endif
					break;
				}

				if (strcmp(extension, ".BMP") == 0)
					type = TYPE_BMP;
				else if (strcmp(extension, ".TGA") == 0)
					type = TYPE_TGA;
				else if (strcmp(extension, ".DDS") == 0)
					type = TYPE_DDS;
				else if (strcmp(extension, ".TXT") == 0)
					continue;
				else
				{
					#if DEBUG_MODULE
					debug_log("Texture file not BMP, TGA or DDS: %s", filename);
					#endif
					continue;
				}

				index = match_system_texture_name ( filename, &camo );

				if (index >= 0 && index < MAX_TEXTURES)
				{
					file_type
						old_type;

					old_type = system_texture_override_names[index].type;

					if (camo == overrider || camo == CAMO_REGULAR && old_type == TYPE_ORIGINAL || camo == CAMO_DESERT && system_texture_info[index].flags.camoflage_texture)
					{
						system_texture_override_names[index].type = type;
						sprintf(system_texture_override_names[index].path, "%s\\%s\\%s", TEXTURE_OVERRIDE_DIRECTORY, mapname, filename);
						strupr(system_texture_override_names[index].path);
						strcpy(system_texture_override_names[index].name, filename);
						system_texture_override_names[index].camo = camo;
						#if DEBUG_MODULE
						debug_log ("++TEXTURE OVERRIDES++ found override file %s %d", filename, index );
						#endif

						if (old_type == TYPE_ORIGINAL)
							count++;
					}
				}
				break;
			}
		default:
			break;
		}
	}
	while ( get_next_directory_file ( directory_listing ) );

	destroy_directory_file_list ( directory_listing );

	return (count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ load warzone specific textures, called from: eech-new\aphavoc\source\flight.c about line 130
//with this function textures are called from just before you go into campaign
//they are called in a crtain order and later occurences of a texture take precedence over earlier
void load_warzone_override_textures ( void )
{
	char directory_textdir_path[256];
	int nrtextfound = 0;
	int count;

	// VJ 051226 NOTE: map_info structure is called from aphavoc\source\ui_menu\sessparm\sparm_sc.c
	// and main variables are already set (warzone name, number, countours etc.

	// empty all the strings
	clear_texture_override_names ();

	initialize_terrain_textures ();
	initialise_noisemaps ();

	// first seek all textures in common directories
	//VJ 051024 do not use root directory to search
	//nrtextfound = initialize_texture_override_names ( "." );

	nrtextfound += initialize_texture_override_names ( TEXTURE_OVERRIDE_DIRECTORY_GENERAL );

	nrtextfound += initialize_texture_override_names ( TEXTURE_OVERRIDE_DIRECTORY_COCKPIT );

	nrtextfound += initialize_texture_override_names ( TEXTURE_OVERRIDE_DIRECTORY_CAMO );

	nrtextfound += initialize_texture_override_names ( TEXTURE_OVERRIDE_DIRECTORY_ANIMATION );

	//VJ 051229 changed the order of reading: first all the official dirs, last the user defined dirs.
	//Makes more sense, else people make textures but they are not shown

	//look for the modded and mipmapped terrain textures
	//VJ 050319 texture colour mod, load terrain textures

	// Casm 20AUG05 Moved backup before "if"
	//VJ 050621 backup commandline var, set to 0 if no textures found
	ASSERT ( texture_colour_bak == -1 );
	texture_colour_bak = command_line_texture_colour;


	if (command_line_texture_colour)
	{

		//VJ 051223 removed string list with warzone names:
		//look directly for texture dir with name current_map_info.name" (= session title)
		//That way warzones can be added automatically without adding strings to the code
		sprintf (directory_textdir_path, "%s\\%s", TEXTURE_OVERRIDE_DIRECTORY_TERRAIN, current_map_info.name);
		#if DEBUG_MODULE
		debug_log("=== loading custom info: texture dir:  %s",directory_textdir_path);
		#endif

		//note: TEXTURE_OVERRIDE_DIRECTORY is concatinated in functions
		nrtextfound += initialize_texture_override_names ( directory_textdir_path );

		if (nrtextfound == 0)
			command_line_texture_colour = 0;

		//VJ read text file with scale indicators for terrain texture display
		initialize_terrain_texture_scales ( directory_textdir_path );
	}


	//VJ 051228 last look for the user defined directories. Specified in a text file in the map dir
	sprintf (directory_textdir_path, "%s\\texturedirs.txt",get_current_game_session()->data_path);

	#if DEBUG_MODULE
	debug_log("=== Searching for aditional paths in texturedirs.txt of warzone %s",get_current_game_session()->warzone_name);
	#endif

	if ( file_exist ( directory_textdir_path ) )
	{
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
				#if DEBUG_MODULE
				debug_log("=== Looking for additional textures in %s",p);
				#endif

				// get override texture names in array
				nrtextfound += initialize_texture_override_names ( p );

			}
			// get the next specified dir
			fscanf(ftextdir,"%[^\n]\n",buf);
		}
	}

	// Global overrider. For testing mostly
	nrtextfound += initialize_texture_override_names ( TEXTURE_OVERRIDE_DIRECTORY_TEMP );

	#if DEBUG_MODULE
	debug_log("Nr override textures found %d",nrtextfound);
	#endif

	//now we have all the names, load the bmp and dds files

	//VJ 050619 make a backup of the original pointers to the screens
	memset ( backup_system_textures, 0, sizeof ( backup_system_textures ) );
	for (count = 0; count < number_of_system_textures; count++)
	{
		backup_system_textures[count] = system_textures[count];
		backup_system_texture_info[count] = system_texture_info[count];
	}

	//VJ 050530 read single bmp files
	//VJ 050530 read mipmapped dds files
	load_texture_override ();

	real_set_texture_camoflage ( texture_camoflage );
	apply_object_3d_reflection_texture_map ();

	//VJ 050820 dynamic water
	if (global_dynamic_water)
		load_texture_water();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050620 restore pointers to default + startup override textures
// called from \eech-new\aphavoc\source\flight.c
void restore_default_textures ( void )
{
	int count = 0;

	//VJ 050621 restore backup commandline
	if ( texture_colour_bak != -1 )
	{
		command_line_texture_colour = texture_colour_bak;
		texture_colour_bak = -1;
	}

	for (count = 0; count < MAX_TEXTURES; count++)
	if ( system_texture_override_names[count].type != TYPE_ORIGINAL )
	{

#if DEBUG_MODULE
		debug_log("Texture override +++ restore screen (%d) : %s",count,system_texture_override_names[count].name);
#endif
		f3d_texture_release(system_texture_info[count].texture_screen);

		system_texture_info[count].texture_screen->used = FALSE;

		// restore pointer to original textures
		system_textures[count] = backup_system_textures[count];

		system_texture_info[ count ] = backup_system_texture_info[ count ];
	}

	memset(backup_system_textures, 0, sizeof(backup_system_textures));

	clear_texture_override_names();

	//VJ 051225 reset map data
	initialise_custom_map_info();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050322 texture colour mod, function to read texture scale file
static void initialize_terrain_texture_scales ( const char *mapname )
{
	char filename[128];

	sprintf (filename, "%s\\%s\\texture_scales.txt", TEXTURE_OVERRIDE_DIRECTORY, mapname);

	if ( file_exist ( filename ) )
	{
		FILE *fin;
		char buf[256];
		char *p;
		int count;

		fin = fopen(filename,"r");

		// skip comment lines
		fscanf(fin,"%[^\n]\n",buf);
		while (buf[0] == '#')
				fscanf(fin,"%[^\n]\n",buf);

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
					i--;
				p[i+1]='\0';
				while (p[0] == ' ')
					p++;
				current_map_info.texture_override_scales[count][0] = get_system_texture_index (p);
			}

			//scan scale
			p = strtok(NULL,"#");
			if (p)
			{
				current_map_info.texture_override_scales[count][1] = atoi(p);
			}

			fscanf(fin,"%[^\n]\n",buf);
			// next line

			count++;
		}

		fclose(fin);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_bitmap_header ( BITMAPINFOHEADER bmih, const char *full_override_texture_filename )
{
	if (bmih.biCompression != BI_RGB)
	{
		#if DEBUG_MODULE
		debug_log ("%s is not uncompressed RGB!", full_override_texture_filename );
		#endif
		return 0;
	}

	//VJ only 32 and 24 bit uncompressed bitmaps are read
	if (bmih.biBitCount != 24 && bmih.biBitCount != 32)
	{
		debug_fatal ("%s is not 24 or 32 bit! (it is : %d)", full_override_texture_filename, bmih.biBitCount);
		return 0;
	}
	/* unlimited size
	if (bmih.biHeight > MAX_TEXTURE_HEIGHT)
	{
		debug_log ("%s taller than the maximum allowed", full_override_texture_filename );
		return 0;
	}

	if (bmih.biWidth > MAX_TEXTURE_WIDTH)
	{
		debug_fatal ("%s wider than the maximum allowed", full_override_texture_filename );
		return 0;
	}
	*/
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_texture_override ( void )
{
	const char
		*full_override_texture_filename = nullptr;

	int
		count;

	char
		missing_textures[4096] = { '\0' };

	// Now that all the screens are loaded we check to see if there is are any overrides
	for ( count = 0; count < MAX_TEXTURES; count++ )
	{
		screen
			*override_screen = NULL;

		full_override_texture_filename = system_texture_override_names[count].path;
		switch ( system_texture_override_names[count].type )
		{
			case TYPE_BMP:
			{
#if DEBUG_MODULE
				debug_log ("++OVERRIDES++ found bmp file %s", full_override_texture_filename);
#endif
				if (!*missing_textures)
				{
					override_screen = load_bmp_file_screen(full_override_texture_filename);
				}
				break;
			}
			case TYPE_TGA:
			{
#if DEBUG_MODULE
				debug_log ("++OVERRIDES++ found tga file %s", full_override_texture_filename);
#endif
				if (!*missing_textures)
				{
					override_screen = load_tga_file_screen(full_override_texture_filename, 0, texture_gamma_correction(count));
				}
				break;
			}
			case TYPE_DDS:
			{
#if DEBUG_MODULE
				debug_log ("++OVERRIDES++ found dds file %s", full_override_texture_filename);
#endif
				if (!*missing_textures)
				{
					override_screen = load_dds_file_screen(full_override_texture_filename, 0, texture_gamma_correction(count));
				}
				break;
			}
			default:
			{
				// need to provide all these textures ourselves
				if ( count >= TEXTURE_INDEX_LAST && count < number_of_system_textures )
				{
					sprintf ( missing_textures + strlen ( missing_textures ), "\n(%d): %s%s (object %s)", count, get_system_texture_name ( count ), system_texture_info[count].flags.camoflage_texture ? TEXTSUFFIX_DESERT : "", new_texture_sources[count] );
				}
				break;
			}
		}
		//VJ 050821 check if it worked
		if (override_screen)
		{
			// now we set the pointer in the system textxures array to point to this
			// screen rather than the original screen
			system_textures[count] = override_screen;
			//VJ 04/12/12 add the sreen also to this array because the function set_texture_camoflage uses it and it is called after this stuff
			system_texture_info[count].texture_screen = override_screen;
			// adjust alpha bit
			system_texture_info[count].flags.contains_alpha = override_screen->contains_alpha;
		}
		else
		{
			//not done, reset flag
			system_texture_override_names[count].type = TYPE_ORIGINAL;
		}
	}
	if (*missing_textures)
	{
		debug_fatal ( "Missing texture(s)%s", missing_textures );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050814 dynamic water
//VJ 051226 changed function parameter to void
void load_texture_water( void )
{
	FILE *fin;

	screen
		*override_screen = nullptr;

	int
		i, placenr, count;

	char
		buf[256],
		filename[256];

	char *p, *q;


	sprintf(filename,"%s\\%s\\waterinfo.txt", TEXTURE_OVERRIDE_DIRECTORY,TEXTURE_OVERRIDE_DIRECTORY_WATER );
	//VJ 050820 added file checking to prevent crash
	if ( !file_exist ( filename ) ){
		global_dynamic_water	= 0;
		return;
	}

	fin = fopen(filename,"r");
	if (!fin){
		global_dynamic_water	= 0;
		return;
	}

	// analyse riverinfo.txt
	// read comments
	fscanf(fin,"%[^\n]\n",buf);
	while (buf[0] == '#')
		fscanf(fin,"%[^\n]\n",buf);

	for (i = 0; i < 3; i++)
	{
		p = strtok(buf,"=");
		p = strtok(NULL,",");
		if (p){
			while (*p == ' ') p++;
				q = p;
			while (*q != ' ') q++;
				*q = '\0';
			strcpy(current_map_info.water_info[i].name_top, p);
		}
		p = strtok(NULL,",");
		if (p)
			current_map_info.water_info[i].delay = atoi(p);
		p = strtok(NULL,"#");
		if (p)
			current_map_info.water_info[i].scale_top = atoi(p);

		fscanf(fin,"%[^\n]\n",buf);
		p = strtok(buf,"=");
		p = strtok(NULL,",");
		if (p){
			while (*p == ' ') p++;
				q = p;
			while (*q != ' ') q++;
				*q = '\0';
			strcpy(current_map_info.water_info[i].name_bottom, p);
		}
		p = strtok(NULL,",");
		if (p)
			current_map_info.water_info[i].type = atoi(p);
		p = strtok(NULL,",");
		if (p)
			current_map_info.water_info[i].start = atoi(p);
		p = strtok(NULL,",");
		if (p)
			current_map_info.water_info[i].number = atoi(p);
		p = strtok(NULL,",");
		if (p)
			current_map_info.water_info[i].alpha = atoi(p);
		// tune according to warzone, lebanon is reference
		if (i == 0 && current_map_info.mapnr == 3)
			current_map_info.water_info[i].alpha -= 50;
		if (i == 0 && current_map_info.mapnr == 4)
			current_map_info.water_info[i].alpha -= 30;
		p = strtok(NULL,"#");
		if (p)
			current_map_info.water_info[i].scale_bottom = atoi(p);

		fscanf(fin,"%[^\n]\n",buf);

		#if DEBUG_MODULE
		debug_log("dynamic water %s %s", current_map_info.water_info[i].name_top, current_map_info.water_info[i].name_bottom);
		#endif
	}

	fclose(fin);


	//rivertextures are put behind last texture in system_texture_info array
	// order is river, sea, reservoir (0, 1, 2)

	placenr = number_of_system_textures;

	////// load textures

	for (i = 0; i < 3; i++)
	{
		int rivernr = 0;
		//placenr = add_new_texture(current_map_info.water_info[i].name_top, "textuser.c");
		current_map_info.water_info[i].placenr = placenr;
		// read the bottom texture
		sprintf(filename,"%s\\%s\\%s", TEXTURE_OVERRIDE_DIRECTORY, TEXTURE_OVERRIDE_DIRECTORY_WATER, current_map_info.water_info[i].name_top);

		#if DEBUG_MODULE
		debug_log("water %d %d %s",placenr, i, filename);
		#endif

		override_screen = load_tga_file_screen(filename, 0, 1.0);

		system_texture_info[placenr].flags.contains_alpha = 1;
		system_texture_info[placenr].flags.vertically_inverted = 1;
		system_texture_info[placenr].flags.mipmap_enabled = 1;
		system_texture_info[placenr].flags.wrapped = 1;

		system_textures[placenr] = override_screen;
		system_texture_info[placenr].texture_screen = override_screen;

		// load dynamic texture series
		rivernr = current_map_info.water_info[i].start;
		for ( count = 0; count < current_map_info.water_info[i].number; count++ )
		{
			char
				name[256];
			sprintf(name, "%s%0*d", current_map_info.water_info[i].name_bottom, current_map_info.water_info[i].number < 100 ? 2 : 3, rivernr);

			placenr++;
			system_texture_info[placenr].flags.contains_alpha = 1;
			system_texture_info[placenr].flags.vertically_inverted = 1;
			system_texture_info[placenr].flags.mipmap_enabled = 1;
			system_texture_info[placenr].flags.wrapped = 1;

			system_texture_info[placenr].texture_screen = NULL;
			strcpy ( system_texture_names[placenr], name );

			//debug_log("water %d %d %d %s",count, i, rivernr, system_texture_names[placenr]);

			rivernr++;

			switch ( current_map_info.water_info[i].type )
			{
			case TYPE_BMP:
			{
				sprintf(filename,"%s\\%s\\%s.bmp", TEXTURE_OVERRIDE_DIRECTORY,TEXTURE_OVERRIDE_DIRECTORY_WATER, name);
				override_screen = load_bmp_file_screen(filename);
				break;
			}
			case TYPE_TGA:
			{
				sprintf(filename,"%s\\%s\\%s.tga", TEXTURE_OVERRIDE_DIRECTORY,TEXTURE_OVERRIDE_DIRECTORY_WATER, name);
				override_screen = load_tga_file_screen(filename, current_map_info.water_info[i].alpha, 1.0);
				break;
			}
			case TYPE_DDS:
			{
				sprintf(filename,"%s\\%s\\%s.dds", TEXTURE_OVERRIDE_DIRECTORY,TEXTURE_OVERRIDE_DIRECTORY_WATER, name);
				override_screen = load_dds_file_screen(filename, current_map_info.water_info[i].alpha, 1.0);
				break;
			}
			}

			if (override_screen)
			{
				system_textures[placenr] = override_screen;
				system_texture_info[placenr].texture_screen = override_screen;
			}
		}
		placenr++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050814 load a mipmapped and alpha dds file and link to a screen
screen *load_dds_file_screen (const char *full_override_texture_filename, int step, float gamma_adjustment)
{
		int
			temp;
		FILE
			*fp = nullptr;

		struct DDS_PIXELFORMAT {
			DWORD dwSize;
			DWORD dwFlags;
			DWORD dwFourCC;
			DWORD dwRGBBitCount;
			DWORD dwRBitMask;
			DWORD dwGBitMask;
			DWORD dwBBitMask;
			DWORD dwABitMask;
		};

		typedef struct {
			DWORD           dwSize;
			DWORD           dwFlags;
			DWORD           dwHeight;
			DWORD           dwWidth;
			DWORD           dwPitchOrLinearSize;
			DWORD           dwDepth;
			DWORD           dwMipMapCount;
			DWORD           dwReserved1[11];
			struct DDS_PIXELFORMAT ddspf;
			DWORD           dwCaps;
			DWORD           dwCaps2;
			DWORD           dwCaps3;
			DWORD           dwCaps4;
			DWORD           dwReserved2;
		} DDS_HEADER;

		DDS_HEADER ddsh;

		DWORD dwmagic;

		texture_map_types
		    type;

		unsigned char
			*buffer = nullptr;

		int
			mipmap,
			width, height,
			buffer_size;

		screen
			*override_screen = nullptr;

		fp = safe_fopen (full_override_texture_filename, "rb");

		if (!fp)
			return (NULL);

		fread (&dwmagic, sizeof (dwmagic), 1, fp);

		fread (&ddsh, sizeof (ddsh), 1, fp);

/*
			if ( width != height )
			{
				debug_fatal("Only square dds files supported for now: %s",full_override_texture_filename);
			}
*/
		/*			if ( ddsh.dwFlags & DDSD_LINEARSIZE )
			{
				debug_fatal("Compressed dds files not supported: %s",full_override_texture_filename);
			}

			if ( ddsh.ddpfPixelFormat.dwFlags & DDPF_FOURCC )
			{
				debug_fatal("Only RGB dds files supported: %s",full_override_texture_filename);
			}
*/
		mipmap = ddsh.dwMipMapCount;

		if ( mipmap < 1 )
		{
			mipmap = 1;
//		 	debug_fatal("Only mipmapped dds files allowed, use bmps otherwise: %s",full_override_texture_filename);
		}

		//eech-new\modules\graphics\textsys.h
		if (ddsh.ddspf.dwFlags & 1 )
			type = TEXTURE_TYPE_MULTIPLEALPHA;
		else
			type = TEXTURE_TYPE_NOALPHA_NOPALETTE;

		width = ddsh.dwWidth;
		height = ddsh.dwHeight;

		//VJ 050530 set mipmapping to no mipmaps if wanted
		if (!global_mipmapping)
			mipmap = 1;

		#if DEBUG_MODULE
		debug_log(full_override_texture_filename);
		#endif
		override_screen = create_texture_map (width, height, type, mipmap );

		for ( temp = 0; temp < mipmap; temp++ )  //was <= mipmap!
		{
			int o, t;
			int nrbyte = ddsh.ddspf.dwRGBBitCount >> 3;
			//VJ 050426 create a new texture map with mipmap levels if needed
			//C:\gms\Razorworks\eech-new\modules\graphics\scrnstr.h

			buffer_size = width * height * nrbyte;
			buffer = ( unsigned char * ) safe_malloc (buffer_size);

			fread (buffer, buffer_size, 1, fp);

			for ( o = 0; o < buffer_size; o += nrbyte )
			{
				t = min((int)(buffer[o + 2] * gamma_adjustment), 255);
				buffer[o + 1] = min((int)(buffer[o + 1] * gamma_adjustment), 255);
				buffer[o + 2] = min((int)(buffer[o + 0] * gamma_adjustment), 255);
				buffer[o + 0] = t;
				//add alpha layer if necessary
				if (nrbyte == 4)
					buffer[o + 3] = bound(buffer[o + 3] + step, 0, 255);
			}

			while ( !lock_texture ( override_screen, temp ) )
			{
				Sleep ( 100 );
			}

			if (type == TEXTURE_TYPE_NOALPHA_NOPALETTE)
				convert_no_alpha_24bit_texture_map_data ( buffer, width, height, override_screen );
			if (type == TEXTURE_TYPE_MULTIPLEALPHA)// || type == TEXTURE_TYPE_SINGLEALPHA)
				convert_multiple_alpha_32bit_texture_map_data ( buffer, width, height, override_screen );
			if (type == TEXTURE_TYPE_SINGLEALPHA)
				convert_single_alpha_32bit_texture_map_data ( buffer, width, height, override_screen );

			unlock_texture ( override_screen );

			safe_free (buffer);

			width >>= 1;
			height >>= 1;

		}

		safe_fclose (fp);

		return override_screen;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen *load_tga_file_screen ( const char *full_override_texture_filename, int step, float gamma_adjustment )
{
		FILE
			*fp = nullptr;

		texture_map_types
			type;

		unsigned char
			header[18],
			*buffer = nullptr;

		int
			width,
			height,
			nrbytes,
			buffer_size,
			x,
			y;

		screen
			*override_screen = nullptr;

		fp = safe_fopen ( full_override_texture_filename, "rb" );

		fread ( header, sizeof ( header ), 1, fp );

		if ( header[1] || ( header[2] != 2 && header[2] != 10 ) || ( header[16] != 24 && header[16] != 32 ) || ( header[17] & 0xD0 ) )
		{
			safe_fclose ( fp );
			return NULL;
		}
		fseek ( fp, header[0], SEEK_CUR );

		if ( header[16] == 32 )
		{
			nrbytes = 4;
			type = TEXTURE_TYPE_MULTIPLEALPHA;
		}
		else
		{
			nrbytes = 3;
			type = TEXTURE_TYPE_NOALPHA_NOPALETTE;
		}

		width = ( ( int ) header[13] << 8 ) | header[12];
		height = ( ( int ) header[15] << 8 ) | header[14];

		override_screen = create_texture_map ( width, height, type, 0 );

		buffer_size = width * height * nrbytes;
		buffer = ( unsigned char * ) safe_malloc ( buffer_size );

		if ( header[2] == 2 )
		{
			fread ( buffer, buffer_size, 1, fp );
		}
		else
		{
			int
				offset;
			unsigned char
				count,
				buf[512];

			offset = 0;
			do
			{
				fread ( &count, 1, 1, fp );
				if ( count++ & 0x80 )
				{
					count -= 0x80;
					fread ( buf, nrbytes, 1, fp );
					while ( count-- )
					{
						memcpy ( buffer + offset, buf, nrbytes );
						offset += nrbytes;
					}
				}
				else
				{
					int
						size;

					size = count * nrbytes;
					fread ( buffer + offset, size, 1, fp );
					offset += size;
				}
			}
			while ( offset < buffer_size );
		}

		safe_fclose ( fp );

		for ( y = 0; y < height; y++ )
		{
			for ( x = 0; x < width; x++ )
			{
				int
					offset;
				unsigned char
					tmp;

				offset = ( y * width + x ) * nrbytes;

				tmp = min ( ( int ) ( buffer[offset + 2] * gamma_adjustment ), 255 );
				buffer[offset + 2] = min ( ( int ) ( buffer[offset + 0] * gamma_adjustment ), 255);
				buffer[offset + 1] = min ( ( int )( buffer[offset + 1] * gamma_adjustment ), 255);
				buffer[offset + 0] = tmp;
				/*if ( nrbyte == 4 )
					buffer[offset + 3] = min ( ( int ) ( buffer[offset + 3] * gamma_adjustment ), 255 );*/
			}
		}

		if ( !( header[17] & 0x20 ) )
		{
			for ( y = 0; y < height / 2; y++ )
			{
				int
					offset1,
					offset2;

				offset1 = y * width * nrbytes;
				offset2 = ( height - y - 1 ) * width * nrbytes;

				for ( x = 0; x < width * nrbytes; x++ )
				{
					unsigned char
						tmp;

					tmp = buffer[offset1 + x];
					buffer[offset1 + x] = buffer[offset2 + x];
					buffer[offset2 + x] = tmp;
				}
			}
		}

		while ( !lock_texture ( override_screen, 0 ) )
		{
			Sleep ( 100 );
		}

		if ( type == TEXTURE_TYPE_NOALPHA_NOPALETTE )
			convert_no_alpha_24bit_texture_map_data ( buffer, width, height, override_screen );
		else
			convert_multiple_alpha_32bit_texture_map_data ( buffer, width, height, override_screen );

		unlock_texture ( override_screen );

		safe_free ( buffer );

		return override_screen;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050814 load a non-mipmapped and non-alpha bitmap and link to a screen
screen *load_bmp_file_screen (const char *full_override_texture_filename)
{
	FILE
		*fp = nullptr;

// VJ 041217 bitmap header info: http://msdn.microsoft.com/library/default.asp?url=/library/en-us/gdi/bitmaps_5f8y.asp
	BITMAPFILEHEADER
		bmfh;

	BITMAPINFOHEADER
		bmih;

	unsigned char
		*buffer = nullptr, *bufferswap;

	int
		type,
		width, height,
		buffer_size = 0,
		x, y, mipmap, temp = 0;

	//static
	screen
		*override_screen = nullptr;

	//VJ 050530 mipmapping, set mipmap to 0 for now, it works but reserved for dds files
	mipmap = 0;

	fp = safe_fopen (full_override_texture_filename, "rb");

	fread (&bmfh, sizeof (bmfh), 1, fp);

	//read bitmap header info structure
	fread (&bmih, sizeof (bmih), 1, fp);
			//VJ 041217 if it is a 8bit texture read the palette, structure rgb_colour

	//check bitmap header for correct format
	if (!check_bitmap_header ( bmih, full_override_texture_filename) )
	{
		safe_fclose (fp);
		return NULL;
	}


	//VJ 050426 create a new texture map with mipmap levels if needed
	width = bmih.biWidth;
	height = bmih.biHeight;

	type = TEXTURE_TYPE_NOALPHA_NOPALETTE;

	//C:\gms\Razorworks\eech-new\modules\graphics\scrnstr.h
	#if DEBUG_MODULE
	debug_log(full_override_texture_filename);
	#endif
	override_screen = create_texture_map (width, height, (texture_map_types)type, mipmap+1 );

	if (bmih.biBitCount == 24)
		buffer_size = width * height * 3;
	else if (bmih.biBitCount == 32)
		buffer_size = width * height * 4;
	// note color depth is assumed here

	buffer = ( unsigned char * ) safe_malloc (buffer_size);
	bufferswap = ( unsigned char * ) safe_malloc (buffer_size);

	fread (buffer, buffer_size, 1, fp);


	//VJ 050618 changed this part to proper texture handling instead of drawing pixels on a screen
	//swap lines around, bitmaps are upside down in the game
	if (bmih.biBitCount == 24)
	{
		for ( y = 0; y < height; y++ )
		{
			for ( x = 0; x < width; x++ )
			{
				bufferswap[(height-y-1)*width*3 + x*3 + 0] = buffer[y*width*3 + x*3 + 2];
				bufferswap[(height-y-1)*width*3 + x*3 + 1] = buffer[y*width*3 + x*3 + 1];
				bufferswap[(height-y-1)*width*3 + x*3 + 2] = buffer[y*width*3 + x*3 + 0];
			}
		}
	}
	if (bmih.biBitCount == 32)
	{
		for ( y = 0; y < height; y++ )
		{
			for ( x = 0; x < width; x++ )
			{
				// ignore alpha channel
				bufferswap[(height-y-1)*width*3 + x*3 + 0] = buffer[y*width*4 + x*4 + 2];
				bufferswap[(height-y-1)*width*3 + x*3 + 1] = buffer[y*width*4 + x*4 + 1];
				bufferswap[(height-y-1)*width*3 + x*3 + 2] = buffer[y*width*4 + x*4 + 0];
//				 bufferswap[(height-y-1)*width*4 + x*4 + 3] = buffer[y*width*4 + x*4 + 3];
			}
		}
	}

	while ( !lock_texture ( override_screen, temp ) )
	{
		Sleep ( 100 );
	}

	//only for NON PALETTE files
	if (bmih.biBitCount == 24 || bmih.biBitCount == 32)
		convert_no_alpha_24bit_texture_map_data ( bufferswap, width, height , override_screen );

	unlock_texture ( override_screen );

	safe_free (buffer);
	safe_free (bufferswap);

	safe_fclose (fp);

	return override_screen;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 051226 custom map info used in terrtype.c
// moved water and texture scale info to structure CUSTOM_MAP_INFO
//enables adding custom maps without changing the code
void initialise_custom_map_info( void )
{
	int i;

	current_map_info.user_defined_contour_heights = 0;
	for (i = 0; i < 9; i++)
		current_map_info.contour_heights[i] = 0;

	for (i = 0; i < 64; i ++)
	{
		current_map_info.texture_override_scales[i][0] = 0;
		current_map_info.texture_override_scales[i][1] = 64; //safe value
	}

	current_map_info.name[0] = '\0';

	current_map_info.mapnr = 0;

//set the map season to default. There are 4 settings: default and desert,
//and summer and winter for the maps that change seasonally
//VJ 060319 further bug fixes
	current_map_info.season = SESSION_SEASON_INVALID;

	current_map_info.dry_river = 0;

	current_map_info.gouraud_shading = 0; // Craig Feb. 2009

	current_map_info.latitude = current_map_info.longitude = 0.0;

	for (i = 0; i < 3; i++){
		current_map_info.water_info[i].start = 0;
		current_map_info.water_info[i].number = 0;
		current_map_info.water_info[i].delay = 0;
		current_map_info.water_info[i].scale_top = 0;
		current_map_info.water_info[i].scale_bottom = 0;
		current_map_info.water_info[i].alpha = 0;
		current_map_info.water_info[i].type = TYPE_ORIGINAL;
		current_map_info.water_info[i].placenr = 0;
		current_map_info.water_info[i].name_top[0] = '\0';
		current_map_info.water_info[i].name_bottom[0] = '\0';
	}
}

float get_current_map_latitude_offset(void)
{
	return current_map_info.latitude;
}

float get_current_map_longitude_offset(void)
{
	return current_map_info.longitude;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialize_known_coordinates(void)
{
	switch (current_map_info.mapnr)
	{
	case 1:  // Thailand
		current_map_info.latitude = rad(18.393);
		current_map_info.longitude = rad(97.87);
		break;
	case 2:  // Cuba
		current_map_info.latitude = rad(19.577);
		current_map_info.longitude = rad(-78.628);
		break;
	case 3:  // Georgia
		current_map_info.latitude = rad(41.16);
		current_map_info.longitude = rad(40.185);
		break;
	case 4:  // Taiwan
		current_map_info.latitude = rad(21.96);
		current_map_info.longitude = rad(119.75);
		break;
	case 5:  // Lebanon
		current_map_info.latitude = rad(32.86);
		current_map_info.longitude = rad(35.01);
		break;
	case 6:  // Yemen
		current_map_info.latitude = rad(16.77);
		current_map_info.longitude = rad(43.03);
		break;
	case 7:  // Alaska
		current_map_info.latitude = rad(64.34);
		current_map_info.longitude = rad(-167.13);
		break;
	case 8:  // Aleutean islands
		current_map_info.latitude = rad(51.25);
		current_map_info.longitude = rad(-178.53);
		break;
	case 9:  // Kuwait
		current_map_info.latitude = rad(28.29);
		current_map_info.longitude = rad(45.82);
		break;
	case 10: // Libya
		current_map_info.latitude = rad(21.33);
		current_map_info.longitude = rad(17.27);
		break;
	case 11: // Grand Canyon
		current_map_info.latitude = rad(35.65);
		current_map_info.longitude = rad(-114.04);
		break;
	case 12: // Mars
		// not on earth...
		break;
	case 13: // Alexander Archipelago
		current_map_info.latitude = rad(54.44);
		current_map_info.longitude = rad(-134.55);
		break;
	case 14: // Skagway
		current_map_info.latitude = rad(59.01);
		current_map_info.longitude = rad(-137.055);
		break;
	case 15: // Red Sea
		current_map_info.latitude = rad(21.0);
		current_map_info.longitude = rad(35.5);
		break;
	case 17: // Afognak
		current_map_info.latitude = rad(55.99);
		current_map_info.longitude = rad(-155.86);
		break;
	case 18: // Puerto Rico
		current_map_info.latitude = rad(17.55);
		current_map_info.longitude = rad(-68.06);
		break;
	case 31: // New Grand Canyon
		current_map_info.latitude = rad(35.65);
		current_map_info.longitude = rad(-114.04);
		break;
	}
}

static int startswith(const char* string, const char* prefix)
{
	return strncmp(string, prefix, strlen(prefix)) == 0;
}

//VJ 052127 read map info data
//VJ 060319 further bug fixes
//called from \eech-new\aphavoc\source\ui_menu\sessparm\sparm_sc.c with menu
//called from \eech-new\aphavoc\source\comms\comm_man.c in case of MP
//called from eech-new\aphavoc\source\ai\faction\faction.c in case of load save game
void read_map_info_data ( void )
{
	FILE *fin;

	char
		buf[256],
		filename[128];

	const char
		*map = nullptr;

	directory_file_list
		*list = nullptr;

	//VJ 060218 texture bug autosave fix, mapinfo was reinitialized each autosave
	// moved to init_3d.c
	//initialise_custom_map_info();

	// VJ 051223 head of the session list, title field contains warzone name "Taiwan" etc
	//strcpy(current_map_info.name, get_session_list()->title);
	//VJ 040206: doesn't work in MP because the title is: -multiplayer- !!!

	// the purpose of this bit of code is to detect the warzone name which is then used
	// as directory name under /graphics/textures/terrain/[name] to read the textures from

	//VJ 020206 Changed to using data_path, because that one is initialized in multiplayer

	// try and read an integer > 9
	map = strchr(get_current_game_session()->data_path, '\0')-2;
	current_map_info.mapnr = atoi(map);
	// if result = 0 then read it as an integer < 9
	if (current_map_info.mapnr == 0)	{
		map++;
		current_map_info.mapnr = atoi(map);
	}

	initialize_known_coordinates();

	#if DEBUG_MODULE
	debug_log("###CUSTOM TEXTURE STARTUP: read_map_info_data: warzone number: %d",current_map_info.mapnr);
	#endif

	// now find the "short" name of the warzone by the campaign file. This is how it is done in the first place in uisession.c!
	//use the data_path to find the texture name by looking at the first file in the first campaign dir
	//which is always taiwan.chc or yemen.chc etc
	sprintf(filename,"%s\\camp01\\*.chc", get_current_game_session()->data_path);
	list = get_first_directory_file(filename);
	map = get_directory_file_filename (list);

	// look for the last occurence of '\\' or '/'
	if (strrchr(map,'\\')){
		map = strrchr(map, '\\');
	}
	else
	if (strrchr(map,'/')){
		map = strrchr(map, '/');
	}
	//copy the file name
	strcpy(current_map_info.name, map);

	current_map_info.name[strlen(map)-4] = '\0';
	destroy_directory_file_list ( list );

	#if DEBUG_MODULE
	debug_log("###CUSTOM TEXTURE STARTUP: read_map_info_data: warzone name: %s",current_map_info.name);
	#endif

	//we now know the name
	// parse mapinfo.txt that should be added to new custom campaigns
	sprintf(filename,"%s\\mapinfo.txt", get_current_game_session()->data_path);

	//VJ 050820 added file checking to prevent crash
	if ( file_exist ( filename ) )
	{
		#if DEBUG_MODULE
		debug_log("###CUSTOM TEXTURE STARTUP: read_map_info_data: reading mainfo.txt: %s",filename);
		#endif

		fin = fopen(filename,"r");

		while (fgets(buf, sizeof(buf), fin))
		{
			char
				*variable = strtok(buf,"="),
				*value = strtok(NULL,"#");

			if (!*variable || !value || !*value)
				continue;

			//VJ 051225 added more map info for custom map reading
			//scan contours and camo

			// if a season is not determined by the interface, MP or savegame
			if (startswith(variable, "season"))
			{
				if (current_map_info.season == SESSION_SEASON_INVALID)
				{
					current_map_info.season = atoi(value);
					if (current_map_info.season == 0)
						current_map_info.season = 1;
					#if DEBUG_MODULE
					debug_log("###CUSTOM TEXTURE STARTUP: read_map_info_data: mapinfo.txt: season: %d",	current_map_info.season);
					#endif
					set_global_season( current_map_info.season );
				}
			}

			else if (startswith(variable, "dry river"))
			{
				current_map_info.dry_river = atoi(value);
				#if DEBUG_MODULE
				debug_log("###CUSTOM TEXTURE STARTUP: read_map_info_data: mapinfo.txt: dry river: %d",	current_map_info.dry_river);
				#endif
			}

			else if (startswith(variable, "coordinate"))
			{
				float lat, lng;
				if (sscanf(value, "%f,%f", &lat, &lng) == 2)
				{
					current_map_info.latitude = rad(lat);
					current_map_info.longitude = rad(lng);
				}
			}

			// Craig start Feb. 2009
			else if (startswith(variable, "gouraud_shading"))
			{
				current_map_info.gouraud_shading = atoi(value);
				#if DEBUG_MODULE
				debug_log("###CUSTOM TEXTURE STARTUP: read_map_info_data: mapinfo.txt: gouraud_shading: %d",	current_map_info.gouraud_shading);
				#endif
			}
			// Craig end
		}

		fclose(fin);
	}

	//if no mapinfo.tct and no season determined yet, initialize what we know
	if(current_map_info.season == SESSION_SEASON_INVALID)
	{
		switch (current_map_info.mapnr) {
			case 5:
			case 6:
			case 9:
			case 10:
			case 12:
			{
				set_global_season( SESSION_SEASON_DESERT );
				break;
			}
			case 3: //georgia
			{
				set_global_season( SESSION_SEASON_SUMMER );
				break;
			}
			case 7:
			case 8:
			{
				set_global_season( SESSION_SEASON_WINTER );
				break;
			}
			default:
			{
				set_global_season( SESSION_SEASON_DEFAULT );
			}
		}
		#if DEBUG_MODULE
		debug_log("###CUSTOM TEXTURE STARTUP: read_map_info_data: default season: %d",	current_map_info.season);
		#endif
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int add_new_texture(const char* texture_name, const char* source)
{
	int
		offset,
		camo,
		texture_index;

	char
		name[128];

	texture_flags
		*flags = nullptr;

	strncpy ( name, texture_name, 127 );
	name[127] = '\0';
	strupr ( name );
	offset = strlen ( name ) - TEXTSUFFIX_SIZE;
	camo = offset > 0 && ( !memcmp ( name + offset, TEXTSUFFIX_DESERT, sizeof ( TEXTSUFFIX_DESERT ) ) || !memcmp ( name + offset, TEXTSUFFIX_WINTER, sizeof ( TEXTSUFFIX_WINTER ) ) );
	if ( camo )
	{
		name[offset] = '\0';
	}

	texture_index = get_system_texture_index ( name );
	if ( texture_index != -1 )
	{
		if ( camo && !system_texture_info[texture_index].flags.number_of_camoflage_textures )
		{
			debug_fatal ( "Texture '%s': %s defined it as non-camo but %s says it's camo", name, new_texture_sources[texture_index], source );
		}
		if ( texture_index > TEXTURE_INDEX_LAST_DEFAULT_INDEX && !camo && system_texture_info[texture_index].flags.number_of_camoflage_textures )
		{
			debug_fatal ( "Texture '%s': %s defined it as camo but %s says it's non-camo", name, new_texture_sources[texture_index], source );
		}
		return texture_index;
	}

	if ( number_of_system_textures >= MAX_TEXTURES )
	{
		#if DEBUG_MODULE
		debug_log ( "No available slot for a new texture" );
		#endif
		return 0;
	}

	strcpy ( system_texture_names[number_of_system_textures], name );
	strcpy ( new_texture_sources[number_of_system_textures], source );
	if ( camo )
	{
		#if DEBUG_MODULE
		debug_log ( "Adding texture %i '%s' camo main", number_of_system_textures, name );
		#endif

		flags = &system_texture_info[number_of_system_textures].flags;
		flags->main_texture = 1;
		flags->number_of_camoflage_textures = 1;
		add_texture_to_name_hash ( number_of_system_textures++ );

		strcpy ( system_texture_names[number_of_system_textures], name );
		strcpy ( new_texture_sources[number_of_system_textures], source );
	}

	#if DEBUG_MODULE
	debug_log ( "Adding texture %i '%s'", number_of_system_textures, system_texture_names[number_of_system_textures] );
	#endif
	flags = &system_texture_info[number_of_system_textures].flags;
	flags->main_texture = !camo;
	flags->camoflage_texture = camo;
	flags->camoflage_index = camo;
	add_texture_to_name_hash ( number_of_system_textures );
	return number_of_system_textures++ - camo;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned get_hash(const char* name)
{
	unsigned length = strlen(name);
	unsigned letter;
	unsigned hash = length;

	for ( letter = 0; letter < length; letter++ )
	{
		hash += toupper ( name[letter] );
		hash <<= 1;
	}

	return hash;
}

void add_texture_to_name_hash(unsigned texture_index)
{
	unsigned hash = get_hash(system_texture_names[texture_index]);
	unsigned hash_index = hash & 0xff;

	system_texture_name_hashes[texture_index].hash = hash;
	system_texture_name_hashes[texture_index].texture_index = texture_index;
	system_texture_name_hashes[texture_index].succ = system_texture_name_hash_table[hash_index];
	system_texture_name_hash_table[hash_index] = &system_texture_name_hashes[texture_index];
}
