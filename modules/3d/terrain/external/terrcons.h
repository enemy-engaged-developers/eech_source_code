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

extern int outcode_3d_terrain_word_polygon ( int num_points, terrain_3d_point_word_reference *reference_points, int *polygon_outcode );

extern int outcode_3d_terrain_byte_polygon ( int num_points, terrain_3d_point_byte_reference *reference_points, int *polygon_outcode );

extern int outcode_3d_terrain_triangle ( int *reference_points, int *polygon_outcode );


extern int terrain_alpha_visible_word ( int number_of_points, terrain_3d_point_word_reference *reference_points );

extern int terrain_alpha_visible_byte ( int number_of_points, terrain_3d_point_byte_reference *reference_points );


extern void construct_3d_terrain_word_clipping_primitive ( int number_of_points, struct TERRAIN_3D_POINT_WORD_REFERENCE *reference_points );

extern void construct_3d_terrain_byte_clipping_primitive ( int number_of_points, struct TERRAIN_3D_POINT_BYTE_REFERENCE *reference_points );


extern vertex *construct_3d_terrain_triangle ( int *reference_points );

extern vertex *construct_3d_terrain_xy_triangle ( int *reference_points );

extern vertex *construct_3d_terrain_zy_triangle ( int *reference_points );

extern vertex *construct_3d_terrain_dual_texture_triangle ( int *reference_points );

extern vertex *construct_3d_terrain_dual_texture_xy_triangle ( int *reference_points );

extern vertex *construct_3d_terrain_dual_texture_zy_triangle ( int *reference_points );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern vertex
	terrain_3d_copied_points[];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

