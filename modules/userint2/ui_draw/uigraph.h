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

struct RGB_DATA;

extern void ui_draw_graphic (float x1, float y1, float x2, float y2, struct RGB_DATA *graphic);

extern void ui_draw_part_graphic (float x1, float y1, float x2, float y2, int start_x, int start_y, struct RGB_DATA *graphic);

extern void ui_draw_memory_graphic (ui_object *obj, float x1, float y1, float x2, float y2, int memory_graphic_width, int memory_graphic_height, int memory_graphic_pitch, int masked);

extern void ui_draw_unscaled_memory_graphic (float x1, float y1, float x2, float y2, struct SCREEN *memory_graphic);;

extern void ui_draw_alpha_graphic (float x1, float y1, float x2, float y2, struct RGB_DATA *graphic);

extern void ui_draw_part_alpha_graphic (float x1, float y1, float x2, float y2, int start_x, int start_y, struct RGB_DATA *graphic);

extern void ui_draw_scaled_graphic (
										const int source_x1, const int source_y1, const int source_x2, const int source_y2, int source_pitch,
										const int destination_x1, const int destination_y1, const int destination_x2, const int destination_y2, int destination_pitch,
										unsigned int *source_ptr,
										unsigned int *destination_ptr);

extern void ui_draw_scaled_masked_graphic (
										const int source_x1, const int source_y1, const int source_x2, const int source_y2, int source_pitch,
										const int destination_x1, const int destination_y1, const int destination_x2, const int destination_y2, int destination_pitch,
										unsigned int *source_ptr,
										unsigned int *destination_ptr );

extern void ui_draw_masked_graphic (
										const int destination_x1, const int destination_y1, const int destination_x2, const int destination_y2,
										int destination_pitch, int source_pitch,
										unsigned int *source_ptr,
										unsigned int *destination_ptr );

extern void ui_draw_texture_graphic (float x1, float y1, float x2, float y2, texture_graphic *graphic, real_colour colour);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

