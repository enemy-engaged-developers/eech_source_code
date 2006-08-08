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

#include "graphics.h"

#include "2d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

env_2d
	*active_2d_environment;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

env_2d *create_2d_environment (void)
{
	env_2d
		*env;

	env = safe_malloc (sizeof (env_2d));

	//
	// initialise 'safe' values
	//

	env->vp.x_min = 0.0;
	env->vp.y_min = 0.0;
	env->vp.x_max = 639.999;
	env->vp.y_max = 479.999;

	env->window_x_min = -1.0;
	env->window_y_min = -1.0;
	env->window_x_max = 1.0;
	env->window_y_max = 1.0;
	
	env->offset_x = env->offset_y = 0.0;

	get_identity_matrix3x3 (env->instance_scaling);
	get_identity_matrix3x3 (env->instance_rotation);
	get_identity_matrix3x3 (env->instance_translation);
	get_identity_matrix3x3 (env->instance_transformation);
	get_identity_matrix3x3 (env->window_translation);
	get_identity_matrix3x3 (env->window_scaling);
	get_identity_matrix3x3 (env->window_rotation);
	get_identity_matrix3x3 (env->viewport_translation);
	get_identity_matrix3x3 (env->composite_transformation);

	get_identity_matrix3x3 (env->inverse_viewport_translation);
	get_identity_matrix3x3 (env->inverse_window_rotation);
	get_identity_matrix3x3 (env->inverse_window_scaling);
	get_identity_matrix3x3 (env->inverse_window_translation);
	get_identity_matrix3x3 (env->inverse_composite_transformation);

	env->instance_transformation_matrix_valid = TRUE;
	env->composite_transformation_matrix_valid = TRUE;
	env->inverse_composite_transformation_matrix_valid = TRUE;

	return (env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_2d_environment (env_2d *env)
{
	ASSERT (env);

	if (env == active_2d_environment)
	{
		active_2d_environment = NULL;
	}

	safe_free (env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_active_environment (env_2d *env)
{
	ASSERT (env);

	active_2d_environment = env;

	set_viewport (env->vp.x_min, env->vp.y_min, env->vp.x_max, env->vp.y_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_viewport (env_2d *env, const float x_min, const float y_min, const float x_max, const float y_max)
{
	float
		x_translate,
		y_translate,
		x_scale,
		y_scale;

	ASSERT (env);

	env->vp.x_min = x_min;
	env->vp.y_min = y_min;
	env->vp.x_max = x_max;
	env->vp.y_max = y_max;

	//
	// set viewport origin (centre of viewport)
	//

	x_translate = (env->vp.x_min + env->vp.x_max) / 2.0;
	y_translate = (env->vp.y_min + env->vp.y_max) / 2.0;

	env->viewport_translation[2][0] = x_translate;
	env->viewport_translation[2][1] = y_translate;

	env->inverse_viewport_translation[2][0] = -x_translate;
	env->inverse_viewport_translation[2][1] = -y_translate;

	//
	// calc window to viewport scaling
	//

	x_scale = (env->vp.x_max - env->vp.x_min) / (env->window_x_max - env->window_x_min);
	y_scale = (env->vp.y_max - env->vp.y_min) / (env->window_y_max - env->window_y_min);

	env->window_scaling[0][0] = x_scale;
	env->window_scaling[1][1] = y_scale;

	env->inverse_window_scaling[0][0] = 1.0 / x_scale;
	env->inverse_window_scaling[1][1] = 1.0 / y_scale;

	//
	// flags
	//

	env->composite_transformation_matrix_valid = FALSE;
	env->inverse_composite_transformation_matrix_valid = FALSE;

	//
	// set graphics system viewport
	//

	if (env == active_2d_environment)
	{
		set_viewport (env->vp.x_min, env->vp.y_min, env->vp.x_max, env->vp.y_max);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_viewport_origin (env_2d *env, const float x_org, const float y_org)
{
	float
		x_translate,
		y_translate;

	ASSERT (env);

	//
	// set viewport origin, relative to top left hand corner of viewport
	//

	x_translate = env->vp.x_min + x_org;
	y_translate = env->vp.y_min + y_org;

	env->viewport_translation[2][0] = x_translate;
	env->viewport_translation[2][1] = y_translate;

	env->inverse_viewport_translation[2][0] = -x_translate;
	env->inverse_viewport_translation[2][1] = -y_translate;

	//
	// flags
	//

	env->composite_transformation_matrix_valid = FALSE;
	env->inverse_composite_transformation_matrix_valid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_window (env_2d *env, const float x_min, const float y_min, const float x_max, const float y_max)
{
	float
		x_translate,
		y_translate,
		x_scale,
		y_scale;

	ASSERT (env);

	env->window_x_min = x_min;
	env->window_y_min = y_min;
	env->window_x_max = x_max;
	env->window_y_max = y_max;

	//
	// set window origin (centre of window)
	//

	x_translate = -(env->window_x_min + env->window_x_max) / 2.0;
	y_translate = -(env->window_y_min + env->window_y_max) / 2.0;

	env->window_translation[2][0] = x_translate;
	env->window_translation[2][1] = y_translate;

	env->inverse_window_translation[2][0] = -x_translate;
	env->inverse_window_translation[2][1] = -y_translate;

	//
	// calc window to viewport scaling
	//

	x_scale = (env->vp.x_max - env->vp.x_min) / (env->window_x_max - env->window_x_min);
	y_scale = (env->vp.y_max - env->vp.y_min) / (env->window_y_max - env->window_y_min);

	env->window_scaling[0][0] = x_scale;
	env->window_scaling[1][1] = y_scale;

	env->inverse_window_scaling[0][0] = 1.0 / x_scale;
	env->inverse_window_scaling[1][1] = 1.0 / y_scale;

	//
	// flags
	//

	env->composite_transformation_matrix_valid = FALSE;
	env->inverse_composite_transformation_matrix_valid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_window_rotation (env_2d *env, const float theta)
{
	float
		sin_theta,
		cos_theta;

	ASSERT (env);

	sine_cosine (theta, &sin_theta, &cos_theta);

	env->window_rotation[0][0] = cos_theta;
	env->window_rotation[0][1] = sin_theta;
	env->window_rotation[1][0] = -sin_theta;
	env->window_rotation[1][1] = cos_theta;

	sine_cosine (-theta, &sin_theta, &cos_theta);

	env->inverse_window_rotation[0][0] = cos_theta;
	env->inverse_window_rotation[0][1] = sin_theta;
	env->inverse_window_rotation[1][0] = -sin_theta;
	env->inverse_window_rotation[1][1] = cos_theta;

	//
	// flags
	//

	env->composite_transformation_matrix_valid = FALSE;
	env->inverse_composite_transformation_matrix_valid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_instance_scaling (env_2d *env, const float x_scale, const float y_scale)
{
	ASSERT (env);

	env->instance_scaling[0][0] = x_scale;
	env->instance_scaling[1][1] = y_scale;

	//
	// flags
	//

	env->instance_transformation_matrix_valid = FALSE;
	env->composite_transformation_matrix_valid = FALSE;
	env->inverse_composite_transformation_matrix_valid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_instance_rotation (env_2d *env, const float theta)
{
	float
		sin_theta,
		cos_theta;

	ASSERT (env);

	sine_cosine (theta, &sin_theta, &cos_theta);

	env->instance_rotation[0][0] = cos_theta;
	env->instance_rotation[0][1] = sin_theta;
	env->instance_rotation[1][0] = -sin_theta;
	env->instance_rotation[1][1] = cos_theta;

	//
	// flags
	//

	env->instance_transformation_matrix_valid = FALSE;
	env->composite_transformation_matrix_valid = FALSE;
	env->inverse_composite_transformation_matrix_valid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_instance_position (env_2d *env, const float x, const float y)
{
	ASSERT (env);

	env->instance_translation[2][0] = x;
	env->instance_translation[2][1] = y;

	//
	// flags
	//

	env->instance_transformation_matrix_valid = FALSE;
	env->composite_transformation_matrix_valid = FALSE;
	env->inverse_composite_transformation_matrix_valid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_2d_instance (env_2d *env)
{
	ASSERT (env);

	env->instance_rotation[0][0] = 1.0;
	env->instance_rotation[0][1] = 0.0;
	env->instance_rotation[1][0] = 0.0;
	env->instance_rotation[1][1] = 1.0;

	env->instance_scaling[0][0] = 1.0;
	env->instance_scaling[1][1] = 1.0;

	env->instance_translation[2][0] = 0.0;
	env->instance_translation[2][1] = 0.0;

	//
	// flags
	//

	env->instance_transformation_matrix_valid = FALSE;
	env->composite_transformation_matrix_valid = FALSE;
	env->inverse_composite_transformation_matrix_valid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_composite_transformation_matrix (env_2d *env)
{
	matrix3x3
		m1,
		m2,
		m3;

	if (!env->instance_transformation_matrix_valid)
	{
		multiply_matrix3x3_matrix3x3_2d (m1, env->instance_scaling, env->instance_rotation);

		multiply_matrix3x3_matrix3x3_2d (env->instance_transformation, m1, env->instance_translation);

		env->instance_transformation_matrix_valid = TRUE;
	}

	multiply_matrix3x3_matrix3x3_2d (m1, env->instance_transformation, env->window_translation);

	multiply_matrix3x3_matrix3x3_2d (m2, m1, env->window_scaling);

	multiply_matrix3x3_matrix3x3_2d (m3, m2, env->window_rotation);

	//
	// mirror about x axis (flip y)
	//

	m3[0][1] = -m3[0][1];
	m3[1][1] = -m3[1][1];
	m3[2][1] = -m3[2][1];

	multiply_matrix3x3_matrix3x3_2d (env->composite_transformation, m3, env->viewport_translation);

	env->composite_transformation_matrix_valid = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_inverse_composite_transformation_matrix (env_2d *env)
{
	matrix3x3
		m1,
		m2,
		m3;

	memcpy (m1, env->inverse_viewport_translation, sizeof (matrix3x3));

	//
	// mirror about x axis (flip y)
	//

	m1[0][1] = -m1[0][1];
	m1[1][1] = -m1[1][1];
	m1[2][1] = -m1[2][1];

	multiply_matrix3x3_matrix3x3_2d (m2, m1, env->inverse_window_rotation);

	multiply_matrix3x3_matrix3x3_2d (m3, m2, env->inverse_window_scaling);

	multiply_matrix3x3_matrix3x3_2d (env->inverse_composite_transformation, m3, env->inverse_window_translation);

	env->inverse_composite_transformation_matrix_valid = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_view_offset (env_2d* env, float dx, float dy)
{
	ASSERT(env);
	
	env->offset_x = dx;
	env->offset_y = dy;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_2d_view_offset (env_2d* env)
{
	ASSERT(env);
	
	env->offset_x = 0.0;
	env->offset_y = 0.0;
}
