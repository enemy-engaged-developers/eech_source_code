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

//#define TERRAIN_TEXTURE_FILTER		D3DTFG_LINEAR
//#define TERRAIN_TEXTURE_MIN_FILTER	D3DTFN_LINEAR
//#define TERRAIN_TEXTURE_MIP_FILTER	D3DTFP_POINT

#define TERRAIN_TEXTURE_FILTER		D3DTFG_POINT
#define TERRAIN_TEXTURE_MIN_FILTER	D3DTFN_POINT
#define TERRAIN_TEXTURE_MIP_FILTER	D3DTFP_POINT

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TERRAIN_3D_TRANSFORMED_POINT_NORMAL
{

	float
		r,
		g,
		b;

	real_colour
		colour;
};

typedef struct TERRAIN_3D_TRANSFORMED_POINT_NORMAL terrain_3d_transformed_point_normal;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TERRAIN_3D_TRANSFORMED_POINT_COLOUR
{

	//
	// The following union makes copying between a D3DCOLOR structure a simple memory move.
	//

	union
	{
	
		struct
		{
		
			unsigned char
				blue,
				green,
				red,
				alpha;
		};

		unsigned int
			colour;
	};

	unsigned char
		fog,
		normal_index,
		pad1,
		pad2;
};

typedef struct TERRAIN_3D_TRANSFORMED_POINT_COLOUR terrain_3d_transformed_point_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_terrain_3d_sector_scan_radius ( int radius );

extern int get_terrain_3d_sector_scan_radius ( void );

extern void initialise_3d_terrain_normals ( void );

extern void scan_3d_terrain ( void );

extern void draw_3d_terrain_tree_object ( scene_slot_drawing_list *slot );

extern void draw_3d_terrain_3d_clipped_sector ( scene_slot_drawing_list *slot );

extern void draw_3d_terrain_2d_clipped_sector ( scene_slot_drawing_list *slot );

extern void draw_3d_terrain_unclipped_sector ( scene_slot_drawing_list *slot );

extern void draw_3d_terrain_3d_clipped_bw_sector ( scene_slot_drawing_list *slot );

extern void draw_3d_terrain_2d_clipped_bw_sector ( scene_slot_drawing_list *slot );

extern void draw_3d_terrain_unclipped_bw_sector ( scene_slot_drawing_list *slot );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// All the global variables which are used in rendering the terrain
//

extern terrain_3d_point_byte_reference
	*terrain_3d_sector_point_byte_references;

extern terrain_3d_point_word_reference
	*terrain_3d_sector_point_word_references;

extern terrain_types
	current_terrain_type;

extern terrain_type_info
	*current_terrain_type_class;

extern terrain_3d_sector
	*current_terrain_sector;

extern terrain_3d_point_xz
	*current_terrain_points_xz;

extern terrain_3d_point_y
	*current_terrain_points_y;

extern float
	current_terrain_sector_xz_texture_scale,
	current_terrain_sector_y_texture_scale;

extern terrain_3d_transformed_point_colour
	transformed_3d_point_colours[];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern terrain_3d_transformed_point_normal
	terrain_3d_transformed_point_normals[];

extern vertex
	terrain_transformed_3d_point_normals[];

extern struct VEC3D
	terrain_3d_face_normal;

extern int
	terrain_3d_face_outcode;

extern float
	terrain_3d_xz_scale,
	terrain_3d_y_scale;

extern int
	terrain_object_rendering_enabled;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	terrain_texture_mag_filter,
	terrain_texture_min_filter,
	terrain_texture_mip_filter,
	total_number_of_terrain_points,
	total_number_of_terrain_points_transformed,
	terrain_3d_faces_considered,
	terrain_3d_faces_outcoded,
	terrain_3d_faces_hither_clipped,
	terrain_3d_faces_screen_clipped,
	terrain_3d_faces_constructed,
	terrain_3d_faces_rejected,
	terrain_3d_sectors_inserted,
	terrain_3d_sectors_totally_visible,
	terrain_3d_sectors_trivially_culled,
	terrain_3d_sectors_complex_culled,
	final_total_number_of_terrain_points,
	final_total_number_of_terrain_points_transformed,
	final_terrain_3d_faces_considered,
	final_terrain_3d_faces_outcoded,
	final_terrain_3d_faces_hither_clipped,
	final_terrain_3d_faces_screen_clipped,
	final_terrain_3d_faces_constructed,
	final_terrain_3d_faces_rejected,
	final_terrain_3d_sectors_inserted,
	final_terrain_3d_sectors_totally_visible,
	final_terrain_3d_sectors_trivially_culled,
	final_terrain_3d_sectors_complex_culled;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WATCOM

int get_3d_terrain_face_surface_change ( terrain_3d_face *face );

#pragma aux get_3d_terrain_face_surface_change =	\
	"xor	eax, eax"							\
	"mov	al, [ esi ]"						\
	"shr	eax, 7"								\
parm [ esi ]									\
value [ eax ]									\
modify exact [ eax esi ];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_3d_terrain_face_number_of_points ( terrain_3d_face *face );

#pragma aux get_3d_terrain_face_number_of_points =	\
	"xor	eax, eax"								\
	"mov	al, [ esi ]"							\
	"and	eax, 0x7f"								\
parm [ esi ]										\
value [ eax ]										\
modify exact [ eax esi ];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_3d_terrain_point_y_normal_change ( terrain_3d_point_y *point );

#pragma aux get_3d_terrain_point_y_normal_change =	\
	"xor	eax, eax"								\
	"mov	al, [ esi + 1 ]"						\
	"shr	eax, 7"									\
parm [ esi ]										\
value [ eax ]										\
modify exact [ eax esi ];

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

