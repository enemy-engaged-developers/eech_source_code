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

#define ADDITIVE_SOURCE_BLEND					D3DBLEND_ONE

#define ADDITIVE_DESTINATION_BLEND			D3DBLEND_ONE

#define TRANSLUCENT_SOURCE_BLEND				D3DBLEND_SRCALPHA

#define TRANSLUCENT_DESTINATION_BLEND		D3DBLEND_INVSRCALPHA

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BUFFERED_POLYGON;

typedef struct BUFFERED_POLYGON buffered_polygon;


struct POLYGON_BUFFER;

typedef struct POLYGON_BUFFER polygon_buffer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void check_translucent_buffering_system ( void );

extern void reset_translucent_buffering_system ( void );

extern polygon_buffer * get_translucent_sorted_polygon_buffer ( void );

extern int finalise_translucent_sorted_polygon_buffer ( polygon_buffer *buffer );

extern void remove_translucent_polygon_buffer ( polygon_buffer *buffer );

extern void report_number_of_buffered_translucencies ( void );

extern void draw_polygon_buffer ( polygon_buffer *buffer );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern D3DTLVERTEX *get_translucent_polygon_vertices ( void );

extern buffered_polygon * add_buffered_processed_polygon ( int number_of_vertices, float distance, int shading, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, int specular, int additive );

extern buffered_polygon * buffer_wbuffered_plain_polygon ( vertex *polygon, struct REAL_COLOUR colour, struct REAL_COLOUR specular, int additive );

extern buffered_polygon * buffer_wbuffered_gouraud_shaded_polygon ( vertex *polygon, float red, float green, float blue, int alpha, float specularity, int additive );

extern buffered_polygon * buffer_wbuffered_flat_shaded_textured_polygon ( vertex *polygon, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, struct REAL_COLOUR colour, struct REAL_COLOUR specular, int additive );

extern buffered_polygon * buffer_wbuffered_gouraud_shaded_textured_polygon ( vertex *polygon, struct SCREEN *texture, int filter, int mipmap, int u, int v, int specular, int additive, int alpha );

extern buffered_polygon * buffer_wbuffered_flat_shaded_textured_line ( vertex *polygon, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, struct REAL_COLOUR colour, int additive );

extern buffered_polygon * buffer_wbuffered_gouraud_shaded_textured_line ( vertex *polygon, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, int additive );


extern buffered_polygon * buffer_zbuffered_plain_polygon ( vertex *polygon, struct REAL_COLOUR colour, struct REAL_COLOUR specular, int additive );

extern buffered_polygon * buffer_zbuffered_gouraud_shaded_polygon ( vertex *polygon, float red, float green, float blue, int alpha, float specularity, int additive );

extern buffered_polygon * buffer_zbuffered_flat_shaded_textured_polygon ( vertex *polygon, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, struct REAL_COLOUR colour, struct REAL_COLOUR specular, int additive );

extern buffered_polygon * buffer_zbuffered_gouraud_shaded_textured_polygon ( vertex *polygon, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, int specular, int additive );

extern buffered_polygon * buffer_zbuffered_flat_shaded_textured_line ( vertex *polygon, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, struct REAL_COLOUR colour, int additive );

extern buffered_polygon * buffer_zbuffered_gouraud_shaded_textured_line ( vertex *polygon, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, int additive );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

