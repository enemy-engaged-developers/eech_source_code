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



#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER 16384

#define MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER 655536

#define MAXIMUM_TRIANGLE_BUFFERS 32

#define MAXIMUM_LINE_BUFFERS 2

#define MAX_ALPHA_VERTEX_BUFFERS 16

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SCREEN;

struct VERTEX_BUFFER_TEXTURE_DATA
{

	struct SCREEN
		*texture;

	union
	{

		struct
		{

			unsigned char
				mipmap_filter,
				linear_filter,
				clamp_u,
				clamp_v;
		};

		unsigned int
			texture_settings;
	};
};

typedef struct VERTEX_BUFFER_TEXTURE_DATA vertex_buffer_texture_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _TLVERTEX {
	float sx;
	float sy;
	float sz;
	float rhw;
	D3DCOLOR color;
	D3DCOLOR specular;
	float tu;
	float tv;
} TLVERTEX;
typedef TLVERTEX *LPTLVERTEX;

typedef struct _NTVERTEX {
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
	float tu;
	float tv;
} NTVERTEX;
typedef NTVERTEX *LPNTVERTEX;

struct VERTEX_BUFFER_HEADER
{

	struct VERTEX_BUFFER_HEADER
		*pred,
		*succ;

	vertex_buffer_texture_data
		texture;

	int
		vertices_used,
		indices_index;

	TLVERTEX
		*vertices;

	LPDIRECT3DVERTEXBUFFER9
		buffer;

	WORD
		*indices;

	LPDIRECT3DINDEXBUFFER9
		ibuffer;
};

typedef struct VERTEX_BUFFER_HEADER vertex_buffer_header;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{
	D3D_MAIN,
	D3D_MFD,
	NUMBER_OF_D3D
};

enum
{
	MFD_NONE,
	MFD_WINDOW,
	MFD_FULLSCREEN,
	MFD_MULTIHEAD,
	NUMBER_OF_MFD
};

struct DIRECT_3D
{
	LPDIRECT3D9
		d3d;

	int
		recreate_d3d,
		mfd;
};

struct DIRECT_3D_DATA
{
	D3DPRESENT_PARAMETERS
		d3dpp[NUMBER_OF_D3D];

	LPDIRECT3DDEVICE9
		device[NUMBER_OF_D3D];

	int
		selected_adapter[NUMBER_OF_D3D],
		x[NUMBER_OF_D3D],
		y[NUMBER_OF_D3D];
};

struct DIRECT_3D_EXPORT_MFD
{
	int
		width,
		height,
		updated;

	LPDIRECT3DTEXTURE9
		texture;
};

struct DIRECT_3D_VECTORS
{
	vertex_buffer_header
		triangle_buffers[MAXIMUM_TRIANGLE_BUFFERS],
		line_buffers[MAXIMUM_LINE_BUFFERS],
		*triangle_buffer,
		*free_triangle_buffers,
		*inuse_triangle_buffers,
		*line_buffer,
		*free_line_buffer,
		*inuse_line_buffer;

	LPDIRECT3DVERTEXBUFFER9
//		primary_triangle_vertex_buffer,
//		secondary_triangle_vertex_buffer,
//		current_triangle_vertex_buffer,
//		primary_line_vertex_buffer,
//		secondary_line_vertex_buffer,
//		current_line_vertex_buffer,
		point_vertex_buffer,
		hardware_untransformed_buffer,
		alpha_vertex_buffer[MAX_ALPHA_VERTEX_BUFFERS];

	LPDIRECT3DINDEXBUFFER9
		alpha_index_buffer;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern struct DIRECT_3D
	d3d_common;
extern struct DIRECT_3D_DATA
	d3d_data;
extern struct DIRECT_3D_EXPORT_MFD
	d3d_export_mfd[2];
extern struct DIRECT_3D_VECTORS
	d3d;

extern int
	d3d_initialised,
	d3d_valid,
	d3d_in_3d_scene,
	d3d_maximum_texture_width,
	d3d_maximum_texture_height,
	d3d_use_dx_pipeline,
	d3d_using_hardware_tnl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int initialise_direct_3d ( void );

extern void set_d3d_capabilities ( D3DCAPS9* capabilities );

extern void d3d_release_objects ( void );

extern void d3d_restore_objects ( int activate );

extern void create_d3d_vertex_buffers ( void );

extern void destroy_d3d_vertex_buffers ( void );

extern void recreate_d3d ( void );

extern const char * get_d3d_error_message ( HRESULT error );

extern BOOL d3d_begin_scene ( void );

extern BOOL d3d_end_scene ( void );

extern void register_restore_vb_routine ( void ( *function ) ( void ) );

void d3d_color_fill(unsigned int colour, int x1, int y1, int x2, int y2);

void d3d_texture_draw(struct SCREEN *texture, int x, int y);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
