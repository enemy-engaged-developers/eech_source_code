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

enum DISPLAY_TYPES
{

	DISPLAY_INVALID,
	DISPLAY_WINDOW,
	DISPLAY_FULLSCREEN,
};

typedef enum DISPLAY_TYPES display_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Used in modules/graphics */

extern PALETTEENTRY
	application_colour_table[256],
	application_palette[256];


/* This file only */

extern BOOL
	double_buffer;              // Double buffering enabled ?


/* Used everywhere */

extern int
	application_video_width,
	application_video_height,
	application_video_colourdepth;


/* used in aphavoc/source/project.c */

extern ddraw_initialisation_errors
	direct_draw_initialisation_error;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Used in modules only */

struct direct_draw_data
{

	LPDIRECTDRAWX
		ddraw;

	BOOL
		use_double_buffer,
		use_full_screen,
		use_software_driver,		// Set if you want default graphics card
		use_system_memory,		// Set if you want to debug graphics routines
		use_z_buffer;

	LPDIRECTDRAWSURFACEX
		lpFrontBuffer,
		lpBackBuffer,
		lpRenderBuffer,
		lpZBuffer;

	LPDIRECTDRAWCLIPPER
		lpClipper;

	BOOL
		application_windowed;	//

	int
		windows_width,
		windows_height,
		windows_depth;

	int
		application_display_depth;

	int
		ddraw_valid;
};

extern struct direct_draw_data ddraw;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Used in aphavoc/source tree */

struct DISPLAY_DEVICE
{

	char
		*name;

	int
		assessment,
		is_primary,
		is_nondisplay;

	GUID
		guid;

	struct DISPLAY_DEVICE
		*succ;
};

typedef struct DISPLAY_DEVICE display_device;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Called by aphavoc/source/project.c */

extern BOOL initialise_graphics_system ( GUID *device_guid );
extern void set_SDL_use_double_buffering ( int flag );
extern void set_SDL_use_software_driver ( int flag );
extern void set_SDL_use_system_memory ( int flag );
extern void set_SDL_use_z_buffer ( int flag );
extern void set_SDL_use_full_screen ( int flag );
extern void get_SDL_device_guid ( GUID *guid );
/* and this file */
extern BOOL SDL_set_display_resolution ( int width, int height, int depth, display_types display_type );


/* Called by various files in aphavoc/source tree (and modules as well) */

extern BOOL ddraw_change_display_resolution ( int width, int height, int depth );
extern BOOL ddraw_flip_surface ( void );
extern char *get_ddraw_error_message ( HRESULT error );
extern void blit_front_buffer_to_render_buffer ( void );


/* Used in modules/graphics only */

extern int get_graphics_system_initialised ( void );
extern BOOL ddraw_release_objects ( void );
extern BOOL ddraw_attach_palette ( void );
extern BOOL ddraw_lock_surface ( LPDIRECTDRAWSURFACEX surface, unsigned char **ptr, int *pitch );
extern BOOL ddraw_unlock_surface ( LPDIRECTDRAWSURFACEX surface, unsigned char *memory );
extern BOOL ddraw_set_palette ( void );
extern LPDIRECTDRAWSURFACEX ddraw_create_surface ( int width, int height, int video_memory );
extern BOOL ddraw_destroy_surface ( LPDIRECTDRAWSURFACEX surface );
extern BOOL ddraw_set_cooperative_level ( ddraw_cooperative_level level );
extern void ddraw_validate_display_devices ( void );
extern int ddraw_internal_set_display_mode ( void *data );
extern void get_ddraw_zbuffer_pixel_format ( DDPIXELFORMAT *format );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Used in aphavoc/source tree */

extern display_device
	*display_devices;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Only used in modules/graphics */

extern int
	zbuffer_on_video,
	number_of_display_devices;

extern int
	number_display_modes;

extern display_device
	*best_display_device,
	*current_display_device;

extern display_format
	display_modes[];

extern LPDIRECTDRAWSURFACEX
	zbuffer_target_surface;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

