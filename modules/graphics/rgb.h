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



#if 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
struct RGB_ALPHA_MASKED_SPRITE_DATA
{
	int
		x,
		y,
		u,
		v,
		width,
		height;

	unsigned char
		mask_value;
};

typedef struct RGB_ALPHA_MASKED_SPRITE_DATA rgb_alpha_masked_sprite_data;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0

extern void blit_rgb_graphic (const unsigned char *rgb_graphic, const int x, const int y);

extern void blit_rgb_clipped_graphic (const unsigned char *rgb_graphic, int x, int y);

extern void blit_rgb_centralised_clipped_graphic (const unsigned char *rgb_graphic, int x, int y);

extern void blit_rgb_alpha_centralised_clipped_graphic (const unsigned char *rgb_graphic, const unsigned char *alpha, int alpha_value, int x, int y);

extern void blit_rgb_alpha_masked_sprite (const unsigned char *rgb_data, const unsigned char *mask_data, const rgb_alpha_masked_sprite_data *sprite_data);

extern void blit_rgb_alpha_masked_sprite_zero_mask_value (const unsigned char *rgb_data, const unsigned char *mask_data, const rgb_alpha_masked_sprite_data *sprite_data);

extern void blit_rgb_alpha_masked_sprite_zero_mask_value_onto_texture (const unsigned char *rgb_data, const unsigned char *mask_data, const rgb_alpha_masked_sprite_data *sprite_data, screen *user_screen);

extern void blit_rgb_alpha_masked_sprite_zero_mask_value_scaled (const unsigned char *rgb_data, const unsigned char *mask_data, int t_x, int t_y, int t_dx, int t_dy, int s_x, int s_y, int s_dx, int s_dy, unsigned char mask_value);

extern void convert_tga_to_rgb (const char *tga_filename, const char *rgb_filename);

extern void convert_tga_to_rgb_alpha (const char *tga_filename, const char *rgb_alpha_filename);

extern void convert_tga_to_alpha_mask (const char *tga_filename, const char *alpha_mask_filename);

extern void convert_psd_to_rgb (const char *psd_filename, const char *rgb_filename);

extern void convert_psd_to_rgb_alpha (const char *psd_filename, const char *rgb_alpha_filename);

extern void convert_psd_to_alpha_mask (const char *psd_filename, const char *alpha_mask_filename);

extern void convert_and_dither_psd_to_rgb_alpha ( const char *psd_filename, const char *rgb_alpha_filename );

extern void convert_and_dither_psd_to_rgb ( const char *psd_filename, const char *rgb_filename );

#else

struct RGB_DATA
{
	unsigned short int
		width,
		height;

	rgb_colour
		image[1];
};
typedef struct RGB_DATA rgb_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void convert_psd_to_rgbx (const char *psd_filename, const char *rgbx_filename);

extern void convert_psd_to_rgba (const char *psd_filename, const char *rgba_filename);

extern void blit_rgb_clipped_graphic (const rgb_data *rgb_graphic, int x, int y);
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
