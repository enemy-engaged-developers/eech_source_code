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

#define MAX_SCREEN_HEIGHT 1024

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct SCREEN screen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern screen
	*video_screen,
	*display_screen,
	*active_screen;

extern int
	 active_screen_red_mask,
	 active_screen_red_shift,
	 active_screen_green_mask,
	 active_screen_green_shift,
	 active_screen_blue_mask,
	 active_screen_blue_shift,
	 active_screen_alpha_mask,
	 active_screen_alpha_shift,
	 user_screen_red_mask,
	 user_screen_red_shift,
	 user_screen_green_mask,
	 user_screen_green_shift,
	 user_screen_blue_mask,
	 user_screen_blue_shift,
	 user_screen_alpha_mask,
	 user_screen_alpha_shift;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_system_graphics_screens ( void );

extern screen * create_screen ( int width, int height, int video_memory );

extern screen * get_free_screen ( void );

extern screen * create_user_texture_screen ( int width, int height, int type, int number_of_mipmaps );

extern screen * create_system_texture_screen ( int width, int height, int texture_index, int type );

extern screen * create_screen_for_system_texture ( int texture_index );

extern screen * create_user_3dvisual_texture_screen ( int width, int height, int type );

extern void set_system_texture_screen ( screen *this_screen, int texture_index );

extern BOOL destroy_screen ( screen *this_screen );

extern void create_video_screen ( int width, int height, LPDIRECTDRAWSURFACEX surface4 );

extern void get_screen_pixel_format ( int *red_mask, int *green_mask, int *blue_mask, int *alpha_mask );

extern int get_screen_pixel_width ( struct SCREEN *this_screen );

extern void get_screen_rgba_masks ( struct SCREEN *this_screen, unsigned int *rm, unsigned int *gm, unsigned int *bm, unsigned int *am );

extern BOOL lock_screen ( screen *this_screen );

extern BOOL unlock_screen ( screen *this_screen );

extern HDC get_screen_dc ( screen *this_screen );

extern void release_screen_dc ( screen *this_screen, HDC dc );

extern void set_user_screen_pixel_format ( screen *scr );

extern BOOL set_active_screen ( screen *this_screen );

extern screen * get_active_screen ( void );

extern unsigned char * get_screen_data ( screen *this_screen );

extern int get_screen_pitch ( screen *this_screen );

extern int get_screen_pixel_length ( screen *this_screen );

extern int get_screen_width ( screen *this_screen );

extern int get_screen_height ( screen *this_screen );

extern int get_screen_locked ( screen *this_screen );

extern void clear_screen ( void );

extern int set_3d_render_target ( screen *this_screen );

extern void finalise_3d_render_target_texture ( screen *this_screen );

extern void set_block ( int x1, int y1, int x2, int y2, rgb_colour colour );

extern void blit_screens ( screen *source, screen *destination, int sx1, int sy1, int sx2, int sy2, int dx1, int dy1, int dx2, int dy2 );

extern void set_video_screen_edge ( int x, int y, int width, int height );

extern void check_video_screen_edge ( void );

extern void restore_graphics_screens ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


