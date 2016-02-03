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

enum DISPLAY_3D_TINTS
{
	DISPLAY_3D_TINT_CLEAR,
	DISPLAY_3D_TINT_AMBER,
	DISPLAY_3D_TINT_AMBER_VISUAL,
	DISPLAY_3D_TINT_GREEN,         // green tint IR
	DISPLAY_3D_TINT_GREEN_VISUAL,  // green tint, but visual
	DISPLAY_3D_TINT_ORANGE,
	DISPLAY_3D_TINT_ORANGE_VISUAL,
	DISPLAY_3D_TINT_FLIR,          // grey tint IR
	DISPLAY_3D_TINT_LLLTV,   // grey tint, but visual
	DISPLAY_3D_TINT_BLUE,
	DISPLAY_3D_TINT_BLUE_HAZE, // Jabberwock 031009 Satellite mode
	DISPLAY_3D_TINT_BLUEGREEN,
	NUM_DISPLAY_3D_MODES
};

typedef enum DISPLAY_3D_TINTS display_3d_tints;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum DISPLAY_3D_LIGHT_LEVELS
{
	DISPLAY_3D_LIGHT_LEVEL_LOW,
	DISPLAY_3D_LIGHT_LEVEL_MEDIUM,
	DISPLAY_3D_LIGHT_LEVEL_HIGH,
	NUM_DISPLAY_3D_LIGHT_LEVELS
};

typedef enum DISPLAY_3D_LIGHT_LEVELS display_3d_light_levels;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum DISPLAY_3D_NOISE_LEVELS
{
	DISPLAY_3D_NOISE_LEVEL_NONE,
	DISPLAY_3D_NOISE_LEVEL_LOW,
	DISPLAY_3D_NOISE_LEVEL_MEDIUM,
	DISPLAY_3D_NOISE_LEVEL_HIGH,
	NUM_DISPLAY_3D_NOISE_LEVELS
};

typedef enum DISPLAY_3D_NOISE_LEVELS display_3d_noise_levels;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float
	full_screen_width,
	full_screen_height,
	full_screen_x_min,
	full_screen_y_min,
	full_screen_x_mid,
	full_screen_y_mid,
	full_screen_x_max,
	full_screen_y_max,
	full_screen_virtual_fov,
	full_screen_aspect_ratio,
	full_screen_width_view_angle,
	full_screen_height_view_angle;

extern int
	int_full_screen_width,
	int_full_screen_height;

extern int
	full_screen_3d_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE
extern env_3d
	*main_3d_env,
	*main_3d_single_light_env;
#endif

extern viewpoint
	main_vp;

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern display_3d_tints
	current_3d_display_tint;

extern display_3d_light_levels
	current_3d_light_level;

extern display_3d_noise_levels
	current_3d_noise_level;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

extern void set_3d_resolutions (float width, float height);

extern void increase_3d_resolutions ( event *ev );

extern void decrease_3d_resolutions ( event *ev );

#ifndef OGRE_EE
extern void toggle_3d_information ( event *ev );

extern void toggle_3d_object_lod_calculations ( event *ev );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int get_integer_screen_width (void);
extern int get_integer_screen_height (void);
extern int get_integer_screen_x_min (void);
extern int get_integer_screen_y_min (void);
extern int get_integer_screen_x_mid (void);
extern int get_integer_screen_y_mid (void);
extern int get_integer_screen_x_max (void);
extern int get_integer_screen_y_max (void);
#endif


// 13JUL2011 Casm corrected vertical view angle calculations
// 28MAY2014 Casm virtual FOV
extern void calc_view_angles ( float virtual_width_view_angle, float *width_view_angle, float *height_view_angle );
extern void set_view_angles ( float virtual_width_view_angle );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
