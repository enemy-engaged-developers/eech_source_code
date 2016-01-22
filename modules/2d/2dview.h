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

#ifndef OGRE_EE
struct ENV_2D
{
	viewport
		vp;

	float
		window_x_min,
		window_y_min,
		window_x_max,
		window_y_max,
		offset_x,
		offset_y;

	//
	// transformation matrices (in order applied)
	//

	matrix3x3
		instance_scaling,
		instance_rotation,
		instance_translation,
		instance_transformation,
		window_translation,
		window_scaling,
		window_rotation,
		viewport_translation,
		composite_transformation;

	//
	// inverse transformation matrices (in order applied)
	//

	matrix3x3
		inverse_viewport_translation,
		inverse_window_rotation,
		inverse_window_scaling,
		inverse_window_translation,
		inverse_composite_transformation;

	int
		instance_transformation_matrix_valid,
		composite_transformation_matrix_valid,	 			// always FALSE if instance_transformation_matrix_valid == FALSE
		inverse_composite_transformation_matrix_valid;
};
#else
struct ENV_2D;
#endif

typedef struct ENV_2D env_2d;

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern env_2d
	*active_2d_environment;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define validate_2d_composite_transformation_matrix(ENV)	\
{																			\
	if (!((ENV)->composite_transformation_matrix_valid))	\
	{																		\
		get_2d_composite_transformation_matrix ((ENV));		\
	}																		\
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define validate_2d_inverse_composite_transformation_matrix(ENV)	\
{																						\
	if (!((ENV)->inverse_composite_transformation_matrix_valid))	\
	{																					\
		get_2d_inverse_composite_transformation_matrix ((ENV));		\
	}																					\
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern env_2d *create_2d_environment (void);

extern void destroy_2d_environment (env_2d *env);

extern void set_2d_active_environment (env_2d *env);

extern void set_2d_viewport (env_2d *env, const float x_min, const float y_min, const float x_max, const float y_max);

extern void set_2d_viewport_origin (env_2d *env, const float x_org, const float y_org);

extern void set_2d_window (env_2d *env, const float x_min, const float y_min, const float x_max, const float y_max);

extern void set_2d_window_rotation (env_2d *env, const float theta);

extern void set_2d_instance_scaling (env_2d *env, const float x_scale, const float y_scale);

extern void set_2d_instance_rotation (env_2d *env, const float theta);

extern void set_2d_instance_position (env_2d *env, const float x, const float y);

extern void reset_2d_instance (env_2d *env);

extern void get_2d_composite_transformation_matrix (env_2d *env);

extern void get_2d_inverse_composite_transformation_matrix (env_2d *env);

extern void set_2d_view_offset (env_2d* env, float dx, float dy);

extern void reset_2d_view_offset (env_2d* env);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
