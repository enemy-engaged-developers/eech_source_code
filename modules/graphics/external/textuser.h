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

#define MAX_TEXTURES 2048

#define MAX_TEXTURES_PALETTES 128 // Jabberwock 040213 - Testing for texture related CTDs

#define MAX_HARDWARE_TEXTURES 512

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	number_of_system_textures,
	number_of_system_texture_palettes;

extern struct SCREEN 
	system_textures[MAX_TEXTURES],
	application_textures[MAX_TEXTURES];

extern char
	system_texture_names[MAX_TEXTURES][128];

extern int
	system_textures_referenced[MAX_TEXTURES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_texture_camoflage ( int set );

extern void release_system_textures ( void );

extern void free_agp_memory_textures ( void );

extern void recreate_agp_memory_textures ( void );

extern int load_texturemap_data ( char *texture_binary_filename );

extern int get_system_texture_index ( char *name );

extern struct SCREEN *get_system_texture_ptr ( int index );

extern int create_system_indexed_texture_map ( struct SCREEN *this_screen, int width, int height, int index, enum SCREEN_FORMAT_TYPES type );

extern int match_system_texture_name ( char *name );

extern char *get_system_texture_name ( int index );

extern void report_system_texture_stats ( void );

extern struct TEXTURE_GRAPHIC *create_texture_graphic ( char *filename );

extern void destroy_texture_graphic ( struct TEXTURE_GRAPHIC *graphic );

extern void get_texture_graphic_source_dimensions ( struct TEXTURE_GRAPHIC *graphic, int *width, int *height );

//VJ 050116 custom texture mod: functions needed 
extern void load_custom_textures( void );
extern void initialize_texture_override_names ( char system_texture_override_names[MAX_TEXTURES][128], char *mapname );
extern void load_texture_override ( char system_texture_override_names[MAX_TEXTURES][128], char *mapname );
extern void clear_texture_override_names ( void );
extern void restore_default_textures( void );
extern void load_warzone_override_textures (char *warzone_name);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

