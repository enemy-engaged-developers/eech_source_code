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

extern struct SCREEN
	*current_object_3d_luminosity_texture;

extern int
	current_object_3d_luminosity_texture_u_address,
	current_object_3d_luminosity_texture_v_address,
	current_object_3d_luminosity_texture_filter,
	current_object_3d_luminosity_texture_mipmap;

extern int
	current_object_3d_light_maps_enabled;

extern struct FACE_SURFACE_DESCRIPTION
	*current_object_3d_surface;

extern struct POINT_3D_SHORT_REFERENCE
	*current_object_3d_point_list;

extern struct POINT_3D_PLAIN_REFERENCE
	*current_object_3d_gouraud_list,
	*current_object_3d_face_normal_list;

extern struct SCREEN
	*current_object_3d_texture,
	*current_object_3d_reflection_texture_map;

extern struct OBJECT_3D_SHORT_TEXTURED_POINT
	*current_object_3d_texture_list;

extern struct OBJECT_3D_TRANSFORMED_POINT_NORMAL
	*current_object_3d_transformed_normals;

extern int
	current_object_3d_texture_u_address,
	current_object_3d_texture_v_address,
	current_object_3d_texture_filter,
	current_object_3d_texture_mipmap,
	current_object_3d_specular,
	current_object_3d_outcode;

extern float
	current_object_3d_dissolve_factor;

extern unsigned char
	current_object_3d_dissolve_value;

extern int
	specular_rendering_enabled,
	current_object_3d_light_maps_enabled,
	object_3d_approximation_level,
	current_3d_object_is_flat,
	object_3d_points_current_base,
	object_3d_object_current_base,
	object_3d_light_3d_current_base,
	object_3d_perform_lod_calculations,
	current_object_3d_surface_point_index;

extern object_3d_short_textured_point
	*current_object_3d_surface_point_texture_list;

extern point_3d_plain_reference
	*current_object_3d_surface_point_list,
	*current_object_3d_surface_point_normal_list;

extern object_3d_face
	*current_object_3d_faces;

extern float
	*current_object_3d_culling_factors;

extern unsigned char
	current_object_3d_surface_vertices_used[];

extern struct OBJECT_3D_INFO
	*global_object_3d_info,
	object_3d_object_base[];

extern light_3d_source
	ambient_3d_light,
	*current_3d_lights;

extern vec3d
	object_3d_scale;

extern int
	textured_object_rendering_enabled;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_object_3d_reflection_texture_map ( int texture_index );

extern int get_3d_object_approximation_number ( struct OBJECT_3D_INSTANCE *obj );

extern void pre_render_3d_object ( object_3d_instance *obj );

extern float current_3d_object_face_facing ( void );

extern void draw_3d_object_bounding_box ( object_3d_instance *obj );

extern void render_bounding_box_line ( vertex *points, int pt1, int pt2, real_colour col );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void add_face_to_surface_buffer ( object_3d_face *face );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void calculate_luminous_colour ( real_colour *colour );

extern void calculate_lightmap_luminous_colour ( real_colour *colour );

extern struct REAL_COLOUR calculate_line_colour ( struct OBJECT_3D_INFO *object_base );

extern void generate_environment_coordinates ( object_3d_point *point, vec3d *normal, vec3d *camera_position, matrix3x3 attitude, float *u, float*v );

extern void get_textured_surface_face_colour ( real_colour *colour, real_colour *specular_colour );

extern void get_surface_face_colour ( real_colour *colour, real_colour *specular_colour );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

