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

extern vertex * construct_3d_vertex_polygon ( int num_points, struct POINT_3D_PLAIN_REFERENCE *points, int base_point );

extern vertex * construct_3d_vertex_line ( struct POINT_3D_PLAIN_REFERENCE *points, int base_point, int *polygon_outcode );

extern vertex * construct_3d_vertex_unclipped_line ( struct POINT_3D_PLAIN_REFERENCE *points, int base_point );

extern vertex * construct_3d_vertex_dual_textured_triangle_fan ( int triangle_index, struct POINT_3D_PLAIN_REFERENCE const *points, struct OBJECT_3D_SHORT_TEXTURED_POINT const *texture_points, struct OBJECT_3D_SHORT_TEXTURED_POINT const *lightmap_points, int base_point, int *outcode );

extern vertex * construct_3d_vertex_textured_line ( struct POINT_3D_PLAIN_REFERENCE *points, struct OBJECT_3D_SHORT_TEXTURED_POINT *texture_points, int base_point, int *polygon_outcode );

extern vertex * construct_3d_vertex_unclipped_textured_line ( struct POINT_3D_PLAIN_REFERENCE *points, struct OBJECT_3D_SHORT_TEXTURED_POINT *texture_points, int base_point );

extern vertex * construct_3d_vertex_triangle_fan ( int triangle_index, struct POINT_3D_PLAIN_REFERENCE *points, int base_point, int *polygon_outcode );

extern vertex * construct_3d_vertex_gouraud_triangle_fan ( int triangle_index, float specular, struct POINT_3D_PLAIN_REFERENCE *points, struct POINT_3D_PLAIN_REFERENCE *gouraud_points, int base_point, int *polygon_outcode );

extern vertex * construct_3d_vertex_textured_triangle_fan ( int triangle_index, struct POINT_3D_PLAIN_REFERENCE *polygon_points, struct OBJECT_3D_SHORT_TEXTURED_POINT *texture_points, int base_point, int *polygon_outcode );

extern vertex * construct_3d_vertex_gouraud_textured_triangle_fan ( int triangle_index, float specular, struct POINT_3D_PLAIN_REFERENCE *polygon_points, struct POINT_3D_PLAIN_REFERENCE *gouraud_points, struct OBJECT_3D_SHORT_TEXTURED_POINT *texture_points, int base_point, int *polygon_outcode );

extern vertex * construct_3d_vertex_gouraud_dual_textured_triangle_fan ( int triangle_index, float specular, struct POINT_3D_PLAIN_REFERENCE *polygon_points, struct POINT_3D_PLAIN_REFERENCE *gouraud_points, struct OBJECT_3D_SHORT_TEXTURED_POINT *texture_points, struct OBJECT_3D_SHORT_TEXTURED_POINT *lightmap_points, int base_point, int *polygon_outcode );

extern vertex * construct_3d_vertex_gouraud_coloured_textured_triangle_fan ( int triangle_index, struct POINT_3D_PLAIN_REFERENCE *points, struct POINT_3D_PLAIN_REFERENCE *gouraud_points, struct OBJECT_3D_SHORT_TEXTURED_POINT *texture_points, int base_point, int *polygon_outcode, float red, float green, float blue, unsigned char alpha );

extern vertex * construct_3d_vertex_unclipped_triangle_fan ( int triangle_index, struct POINT_3D_PLAIN_REFERENCE *points, int base_point );

extern vertex * construct_3d_vertex_unclipped_gouraud_triangle_fan ( int triangle_index, float specular, struct POINT_3D_PLAIN_REFERENCE *points, struct POINT_3D_PLAIN_REFERENCE *gouraud_points, int base_point );

extern vertex * construct_3d_vertex_unclipped_textured_triangle_fan ( int triangle_index, struct POINT_3D_PLAIN_REFERENCE *polygon_points, struct OBJECT_3D_SHORT_TEXTURED_POINT *texture_points, int base_point );

extern vertex * construct_3d_vertex_unclipped_gouraud_textured_triangle_fan ( int triangle_index, struct POINT_3D_PLAIN_REFERENCE *polygon_points, struct POINT_3D_PLAIN_REFERENCE *gouraud_points, struct OBJECT_3D_SHORT_TEXTURED_POINT *texture_points, int base_point );

extern int outcode_3d_object_polygon ( int num_points, struct POINT_3D_SHORT_REFERENCE *points, int base_point, int *polygon_outcode );

//
// Surface stuff
//

extern int outcode_3d_object_surface_polygon ( int num_points, int base_point, int *polygon_outcode );

extern vertex *construct_3d_surface_polygon ( int num_points, int base_point );

extern vertex * construct_3d_surface_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode );

extern vertex * construct_3d_surface_gouraud_triangle_fan ( int triangle_index, float specular, int base_point, int *polygon_outcode );

extern vertex * construct_3d_surface_unclipped_gouraud_triangle_fan ( int triangle_index, float specular, int base_point );

extern vertex * construct_3d_surface_textured_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode );

extern vertex * construct_3d_surface_gouraud_textured_triangle_fan ( int triangle_index, float specular, int base_point, int *polygon_outcode );

extern vertex * construct_3d_surface_dual_textured_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode );

extern vertex * construct_3d_surface_gouraud_dual_textured_triangle_fan ( int triangle_index, float specular, int base_point, int *polygon_outcode );

extern vertex * construct_3d_surface_line ( int base_point, int *polygon_outcode );

extern vertex * construct_3d_surface_unclipped_line ( int base_point );

extern vertex * construct_3d_surface_textured_line ( int base_point, int *polygon_outcode );

extern vertex * construct_3d_surface_unclipped_textured_line ( int base_point );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern vertex
	polygon_3d_vertices[];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

