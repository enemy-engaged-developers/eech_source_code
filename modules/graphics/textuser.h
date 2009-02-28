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

#define MAX_TEXTURES 8192

#define MAX_TEXTURES_PALETTES 128 // Jabberwock 040213 - Testing for texture related CTDs

#define MAX_HARDWARE_TEXTURES 512

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	number_of_system_textures,
	number_of_system_texture_palettes;

extern PALETTEENTRY
	system_texture_colour_tables[MAX_TEXTURES_PALETTES][256];

extern struct SCREEN 
	*system_textures[MAX_TEXTURES],
	//VJ 050116 custom texture mod: backup textures to restore default
	*backup_system_textures[MAX_TEXTURES];
	// this does not seem to be used!
	//*application_textures[MAX_TEXTURES];

extern char
	system_texture_names[MAX_TEXTURES][128];

extern int
	system_textures_referenced[MAX_TEXTURES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050818 dynamic water INFO STRUCTURE
struct TERRAIN_DYNAMIC_WATER_INFO
{

	int	
		start,
		number,
		delay,
		scale_top,
		scale_bottom,
		alpha,
		type,
		placenr;
	
	char
		name_top[128],
		name_bottom[128];
};

typedef struct TERRAIN_DYNAMIC_WATER_INFO terrain_dynamic_water_info;


//VJ 051223 contour heights in texture scale file for painless adding of custom maps
struct CUSTOM_MAP_INFO
{
	// 0 = sea, 1 = river, 2 = reservoir
	terrain_dynamic_water_info
		water_info[3]; 
	
	//for desert maps: 0 = flowing river, 1 = dry river bed
	int 
		dry_river;  

	// for using gouraud shading on the terrain with the colors in default.rgb // Craig
	int
		gouraud_shading;

	//contour heigths 9 intervals
	int
		user_defined_contour_heights;
		
	float 
		contour_heights[9];

	char 
		name[128];
	int
	 	mapnr;
	
	//same as global season 1 = default, 2 = default+winter, 3=desert
	int
		season; 
		
  //VJ 050322 texture colour mod: texture scale array, 64 is enough for terrain textures
	int 
		texture_override_scales[64][2];
		
	//VJ 060120 keep the total number of textures = 
	//number_of_system_textures+all water textures+extra terrain textures	
	int 
		last_texture;	
			
};
typedef struct CUSTOM_MAP_INFO custom_map_info;	

extern custom_map_info
	current_map_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_texture_camoflage ( int set );

extern void release_system_textures ( void );

extern void recreate_agp_memory_textures ( void );

extern BOOL load_texturemap_data ( const char *texture_binary_filename );

extern int get_system_texture_index ( const char *name );

extern struct SCREEN *create_texture_map ( int width, int height, texture_map_types type, int number_of_mipmaps, LPDIRECTDRAWPALETTE texture_palette, PALETTEENTRY *texture_colour_table );

extern struct SCREEN *get_system_texture_ptr ( int index );

extern int create_system_indexed_texture_map ( struct SCREEN *this_screen, int width, int height, int index, enum SCREEN_FORMAT_TYPES type );

extern int match_system_texture_name ( const char *name );

extern const char *get_system_texture_name ( int index );

extern void report_system_texture_stats ( void );

extern struct TEXTURE_GRAPHIC *create_texture_graphic ( const char *filename );

extern void destroy_texture_graphic ( struct TEXTURE_GRAPHIC *graphic );

extern void get_texture_graphic_source_dimensions ( struct TEXTURE_GRAPHIC *graphic, int *width, int *height );

//VJ 050116 custom texture mod: all functions are in textuser.c except for this one
//VJ 051223 changed function parameter to void
extern void load_warzone_override_textures ( void );

extern void restore_default_textures( void );

extern void initialise_custom_map_info( void );

extern void read_map_info_data( void );

// returns index of texture
// returns 0 if no more texture indices left (increase MAX_TEXTURES if this happens under normal circumstances)
extern int add_new_texture(char* texture_name);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

