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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_STATS 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

matrix3x3
	rotation_3d,
	scaled_rotation;

static float
	environment_x_origin,
	environment_y_origin;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex
	transformed_3d_points[MAX_POINTS];

object_3d_transformed_point_normal
	transformed_3d_normals[MAX_POINTS];

float
	transformed_3d_normal_factors[MAX_POINTS];

unsigned char
	transformed_3d_normal_visibilities[MAX_POINTS];

object_transformed_3d_point
	transformed_3d_3d_points[MAX_POINTS];

object_transformed_2d_point
	transformed_3d_2d_points[MAX_POINTS];

unsigned char
	transformed_3d_point_outcodes[MAX_POINTS],
	transformed_3d_points_needed[MAX_POINTS];

int
	total_number_of_3d_points_transformed = 0,
	current_number_of_3d_points_transformed = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_transformation_arrays ( void )
{

	memset ( transformed_3d_points_needed, 0, MAX_POINTS );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_transformation_stats ( void )
{

#if DEBUG_STATS

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Number of 3D Object points transformed: %d", MT_INT, &total_number_of_3d_points_transformed );

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_transformation_stats ( void )
{

	total_number_of_3d_points_transformed = current_number_of_3d_points_transformed;

	current_number_of_3d_points_transformed = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	int_light_bounds[6] =
	{

		0,
		255,
		0,
		255,
		0,
		255
	};

float
	float_light_bounds[2] =
	{

		0,
		1
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void illuminate_object_point_normals ( object_3d_heading_pitch_normal *normals, int number_of_normals, light_3d_source *lights, int points_base )
{

	int
		count;

	vec3d
		normal;

	object_3d_transformed_point_normal
		*result_normals;

	ASSERT ( ( number_of_normals + points_base ) < MAX_POINTS );

	result_normals = &transformed_3d_normals[points_base];

	if ( !lights )
	{

		int
			ir,
			ig,
			ib;

		real_colour
			normal_colour;

		asm_convert_float_to_int (  ( ambient_3d_light.colour.red * 255 * current_object_3d_diffuse_factor ), &ir );
		asm_convert_float_to_int (  ( ambient_3d_light.colour.green * 255 * current_object_3d_diffuse_factor ), &ig );
		asm_convert_float_to_int (  ( ambient_3d_light.colour.blue * 255 * current_object_3d_diffuse_factor ), &ib );

		if (active_3d_environment->render_filter == RENDER_INFRARED) // FLIR objects SW
			ir = ig = ib = 255 * current_object_3d_diffuse_factor;

		normal_colour.red = ir;
		normal_colour.green = ig;
		normal_colour.blue = ib;
		normal_colour.alpha = current_object_3d_dissolve_value;

		for ( count = number_of_normals; count > 0; count-- )
		{

			result_normals->colour = normal_colour.colour;
			result_normals->specular = 0;

			result_normals++;
		}
	}
	else if ( !lights->succ )
	{

		vec3d
			light_vector,
			highlight_vector;

		light_vector.x = lights->lx;
		light_vector.y = lights->ly;
		light_vector.z = lights->lz;

		highlight_vector.x = lights->highlight_vector.x;
		highlight_vector.y = lights->highlight_vector.y;
		highlight_vector.z = lights->highlight_vector.z;

		for ( count = number_of_normals; count > 0; count-- )
		{

			float
				r,
				g,
				b,
				s,
				d_intensity,
				s_intensity;

			int
				ir,
				ig,
				ib;

			//
			// Set the light levels
			//

			r = ambient_3d_light.colour.red * current_object_3d_diffuse_factor;
			g = ambient_3d_light.colour.green * current_object_3d_diffuse_factor;
			b = ambient_3d_light.colour.blue * current_object_3d_diffuse_factor;

			if (active_3d_environment->render_filter == RENDER_INFRARED) // FLIR objects SW
				r = g = b = 1 * current_object_3d_diffuse_factor;

			s = 0;

			//
			// Calculate normal
			//

			generate_object_3d_point_normal ( normals, &normal );

			//
			// Calculate diffuse colour intensities
			//

			d_intensity = normal.x * lights->lx + normal.y * lights->ly + normal.z * lights->lz;
			d_intensity *= current_object_3d_diffuse_factor;
			
			s_intensity = normal.x * lights->highlight_vector.x + normal.y * lights->highlight_vector.y + normal.z * lights->highlight_vector.z;

//			d_intensity *= 1.0 / 32767.0;
//			s_intensity *= 1.0 / 32767.0;

			if ( *( ( int *) &d_intensity ) > *( ( int *) &float_value_zero ) )
			{

				d_intensity *= d_intensity;

				r += d_intensity * lights->colour.red;
				g += d_intensity * lights->colour.green;
				b += d_intensity * lights->colour.blue;
			}

			//
			// Calculate specular colour intensities
			//

			if ( *( ( int *) &s_intensity ) > *( ( int *) &float_value_zero ) )
			{

				s_intensity *= s_intensity;
				s_intensity *= s_intensity;
				s_intensity *= s_intensity;
				s_intensity *= s_intensity;
				s_intensity *= s_intensity;

				s += s_intensity * lights->intensity;
			}

			asm_convert_float_to_int ( ( r * 255 ), &int_light_bounds[0] );
			asm_convert_float_to_int ( ( g * 255 ), &int_light_bounds[2] );
			asm_convert_float_to_int ( ( b * 255 ), &int_light_bounds[4] );
			float_light_bounds[0] = s;

			{

				float
					s_test;

				unsigned int
					is_test;

				ir = int_light_bounds[ (((unsigned int) ( 255 - int_light_bounds[0] )) >> 31) + 0];
				ig = int_light_bounds[ (((unsigned int) ( 255 - int_light_bounds[2] )) >> 31) + 2];
				ib = int_light_bounds[ (((unsigned int) ( 255 - int_light_bounds[4] )) >> 31) + 4];

				s_test = 1.0 - s;
				is_test = *( ( int * ) &s_test );

				s = float_light_bounds[ (((unsigned int) is_test) >> 31) ];
			}

			result_normals->r = ir;
			result_normals->g = ig;
			result_normals->b = ib;
			result_normals->alpha = current_object_3d_dissolve_value;
			result_normals->specular = s;

			normals++;

			result_normals++;
		}
	}
	else
	{

		for ( count = number_of_normals; count > 0; count-- )
		{

			float
				r,
				g,
				b,
				specular;

			int
				ir,
				ig,
				ib;

			light_3d_source
				*this_light;

			//
			// Set the light levels
			//

			r = ambient_3d_light.colour.red * current_object_3d_diffuse_factor;
			g = ambient_3d_light.colour.green * current_object_3d_diffuse_factor;
			b = ambient_3d_light.colour.blue * current_object_3d_diffuse_factor;

			if (active_3d_environment->render_filter == RENDER_INFRARED) // FLIR objects SW
				r = g = b = 1 * current_object_3d_diffuse_factor;

			specular = 0;

			//
			// Calculate normal
			//

			generate_object_3d_point_normal ( normals, &normal );

			this_light = lights;

			while ( this_light )
			{

				float
					temp_intensity;

				//
				// Calculate diffuse colour intensities
				//

				temp_intensity = normal.x * this_light->lx + normal.y * this_light->ly + normal.z * this_light->lz;
				temp_intensity *= current_object_3d_diffuse_factor;
//				temp_intensity *= 1.0 / 32767.0;

				if ( *( ( int *) &temp_intensity ) > *( ( int *) &float_value_zero ) )
				{

					temp_intensity *= temp_intensity;

					r += temp_intensity * this_light->colour.red;
					g += temp_intensity * this_light->colour.green;
					b += temp_intensity * this_light->colour.blue;
				}

				//
				// Calculate specular colour intensities
				//

				temp_intensity = normal.x * this_light->highlight_vector.x +
										normal.y * this_light->highlight_vector.y +
										normal.z * this_light->highlight_vector.z;

//				temp_intensity *= 1.0 / 32767.0;

				if ( *( ( int *) &temp_intensity ) > *( ( int *) &float_value_zero ) )
				{

					temp_intensity *= temp_intensity;
					temp_intensity *= temp_intensity;
					temp_intensity *= temp_intensity;
					temp_intensity *= temp_intensity;
					temp_intensity *= temp_intensity;

					specular += temp_intensity * this_light->intensity;
				}

				this_light = this_light->succ;
			}

			asm_convert_float_to_int ( ( r * 255 ), &int_light_bounds[0] );
			asm_convert_float_to_int ( ( g * 255 ), &int_light_bounds[2] );
			asm_convert_float_to_int ( ( b * 255 ), &int_light_bounds[4] );
			float_light_bounds[0] = specular;

			{

				float
					s_test;

				unsigned int
					is_test;

				ir = int_light_bounds[ (((unsigned int) ( 255 - int_light_bounds[0] )) >> 31) + 0];
				ig = int_light_bounds[ (((unsigned int) ( 255 - int_light_bounds[2] )) >> 31) + 2];
				ib = int_light_bounds[ (((unsigned int) ( 255 - int_light_bounds[4] )) >> 31) + 4];

				s_test = 1.0 - specular;
				is_test = *( ( int * ) &s_test );

				specular = float_light_bounds[ (is_test >> 31) ];
			}

			result_normals->r = ir;
			result_normals->g = ig;
			result_normals->b = ib;
			result_normals->alpha = current_object_3d_dissolve_value;
			result_normals->specular = specular;

			normals++;

			result_normals++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void calculate_object_normal_factors ( object_3d_heading_pitch_normal *normals, int number_of_normals, vec3d *camera, object_3d_bounds *bounds, int points_base )
{

	int
		count;

	float
		xmin,
		xmax,
		ymin,
		ymax,
		zmin,
		zmax,
		*result_factors;

	unsigned char
		*result_visibilities;

	vec3d
		normalised_camera;

	ASSERT ( ( number_of_normals + points_base ) < MAX_POINTS );

	result_factors = &transformed_3d_normal_factors[points_base];
	result_visibilities = &transformed_3d_normal_visibilities[points_base];

	normalised_camera = *camera;

	normalised_camera.x *= 1.0 / 32767.0;
	normalised_camera.y *= 1.0 / 32767.0;
	normalised_camera.z *= 1.0 / 32767.0;

	xmin = bounds->xmin * ( 1.0 / 32767.0 );
	xmax = bounds->xmax * ( 1.0 / 32767.0 );
	ymin = bounds->ymin * ( 1.0 / 32767.0 );
	ymax = bounds->ymax * ( 1.0 / 32767.0 );
	zmin = bounds->zmin * ( 1.0 / 32767.0 );
	zmax = bounds->zmax * ( 1.0 / 32767.0 );

	for ( count = number_of_normals; count > 0; count-- )
	{

		float
			nx_xmax,
			nx_xmin,
			ny_ymax,
			ny_ymin,
			nz_zmax,
			nz_zmin,
			a,
			b,
			c,
			d,
			e,
			f,
			g,
			h,
			cdotn;

		cdotn = normals->x * normalised_camera.x + normals->y * normalised_camera.y + normals->z * normalised_camera.z;

		nx_xmin = normals->x * xmin;
		nx_xmax = normals->x * xmax;
		ny_ymin = normals->y * ymin;
		ny_ymax = normals->y * ymax;
		nz_zmin = normals->z * zmin;
		nz_zmax = normals->z * zmax;

		a = - cdotn + ( nx_xmin + ny_ymin + nz_zmin );
		b = - cdotn + ( nx_xmax + ny_ymin + nz_zmin );
		c = - cdotn + ( nx_xmin + ny_ymax + nz_zmin );
		d = - cdotn + ( nx_xmax + ny_ymax + nz_zmin );
		e = - cdotn + ( nx_xmin + ny_ymin + nz_zmax );
		f = - cdotn + ( nx_xmax + ny_ymin + nz_zmax );
		g = - cdotn + ( nx_xmin + ny_ymax + nz_zmax );
		h = - cdotn + ( nx_xmax + ny_ymax + nz_zmax );

		*result_factors = cdotn;	//normals->x * normalised_camera.x + normals->y * normalised_camera.y + normals->z * normalised_camera.z;

		if ( ( a <= 0 ) || ( b <= 0 ) || ( c <= 0 ) || ( d <= 0 ) || ( e <= 0 ) || ( f <= 0 ) || ( g <= 0 ) || ( h <= 0 ) )
		{
			*result_visibilities = TRUE;
		}
		else
		{
//			*result_visibilities = FALSE;
			*result_visibilities = TRUE;
		}

		normals++;

		result_factors++;

		result_visibilities++;
	}
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void illuminate_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base )
{

	illuminate_object_point_normals ( object->point_normals, object->number_of_lighting_normals, lights, points_base );
/*
	if ( camera_direction )
	{

		calculate_object_normal_factors ( object->point_normals + object->culling_normals_offset,
														object->number_of_point_normals - object->culling_normals_offset,
														camera_direction, &object->bounding_box, points_base + object->culling_normals_offset );
	}*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		*result_2d_points,
		*last_transformed_point,
		temp_last_transformed_point;

	unsigned char
		*result_outcode,
		*last_transformed_point_outcode,
		temp_last_transformed_point_outcode;

	float
		pos_x,
		pos_y,
		pos_z,
		xmax,
		ymax,
		zmax,
		oxmax,
		oxmin,
		oymax,
		oymin;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	//
	// We only need the fpu to be in single precision mode
	//

	set_fpu_precision_mode_single ();

	number_of_points = object->number_of_points;

	ASSERT ( ( number_of_points + points_base ) < MAX_POINTS );

	points = object->points;

	result_3d_points = &transformed_3d_3d_points[points_base];

	result_2d_points = &transformed_3d_2d_points[points_base];

	result_outcode = &transformed_3d_point_outcodes[points_base];

	last_transformed_point = &temp_last_transformed_point;

	last_transformed_point_outcode = &temp_last_transformed_point_outcode;

	environment_x_origin = active_3d_environment->x_origin;
	environment_y_origin = active_3d_environment->y_origin;

	pos_x = pos->x * active_3d_environment->screen_i_scale;
	pos_y = pos->y * active_3d_environment->screen_j_scale;
	pos_z = pos->z;

	xmax = max ( fabs ( object->bounding_box.xmin ), fabs ( object->bounding_box.xmax ) );
	ymax = max ( fabs ( object->bounding_box.ymin ), fabs ( object->bounding_box.ymax ) );
	zmax = max ( fabs ( object->bounding_box.zmin ), fabs ( object->bounding_box.zmax ) );

	scaled_rotation[0][0] = rotation_3d[0][0] * active_3d_environment->screen_i_scale * ( xmax / 32767.0 );
	scaled_rotation[0][1] = rotation_3d[0][1] * active_3d_environment->screen_j_scale * ( xmax / 32767.0 );
	scaled_rotation[0][2] = rotation_3d[0][2] * ( xmax / 32767.0 );

	scaled_rotation[1][0] = rotation_3d[1][0] * active_3d_environment->screen_i_scale * ( ymax / 32767.0 );
	scaled_rotation[1][1] = rotation_3d[1][1] * active_3d_environment->screen_j_scale * ( ymax / 32767.0 );
	scaled_rotation[1][2] = rotation_3d[1][2] * ( ymax / 32767.0 );

	scaled_rotation[2][0] = rotation_3d[2][0] * active_3d_environment->screen_i_scale * ( zmax / 32767.0 );
	scaled_rotation[2][1] = rotation_3d[2][1] * active_3d_environment->screen_j_scale * ( zmax / 32767.0 );
	scaled_rotation[2][2] = rotation_3d[2][2] * ( zmax / 32767.0 );

	for ( count = number_of_points; count > 0; count-- )
	{

		{

			float
				point_x,
				point_y,
				point_z,
				x,
				y,
				z;

			point_x = points->x;
			point_y = points->y;
			point_z = points->z;

			x = pos_x + point_x * scaled_rotation[0][0] + point_y * scaled_rotation[1][0] + point_z * scaled_rotation[2][0];
			y = pos_y + point_x * scaled_rotation[0][1] + point_y * scaled_rotation[1][1] + point_z * scaled_rotation[2][1];
			z = pos_z + point_x * scaled_rotation[0][2] + point_y * scaled_rotation[1][2] + point_z * scaled_rotation[2][2];

			result_3d_points->x = x;
			result_3d_points->y = y;
			result_2d_points->z = z;

			if ( *( ( int * ) &result_2d_points->z ) >= *( ( int * ) &clip_hither ) )
			{

				float
					q,
					i,
					j;

				oxmax = active_viewport.x_max - last_transformed_point->i;
				oxmin = last_transformed_point->i - active_viewport.x_min;
				oymax = active_viewport.y_max - last_transformed_point->j;
				oymin = last_transformed_point->j - active_viewport.y_min;

				ixmax = *( ( unsigned int * ) &oxmax );
				ixmin = *( ( unsigned int * ) &oxmin );
				iymax = *( ( unsigned int * ) &oymax );
				iymin = *( ( unsigned int * ) &oymin );

				q = 1.0 / result_2d_points->z;

				ixmin >>= 31;
				iymin &= 0x80000000;
				ixmax >>= 29;
				iymax &= 0x80000000;
				iymin >>= 30;
				ixmin &= 0x00000001;
				iymax >>= 28;
				ixmax &= 0x00000004;
				ixmin |= iymin;
				ixmax |= iymax;
				*last_transformed_point_outcode = ( ixmin | ixmax );

//				start_float_divide ( result_2d_points->z, 1.0 );

//				*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				last_transformed_point = result_2d_points;

				last_transformed_point_outcode = result_outcode;

//				q = end_float_divide ();

				i = ( result_3d_points->x * q );
				j = ( result_3d_points->y * q );

				result_2d_points->q = q;
				result_2d_points->j = environment_y_origin - j;
				result_2d_points->i = environment_x_origin + i;

#if DEBUG_STATS
				current_number_of_3d_points_transformed++;
#endif
			}
			else
			{

				*result_outcode = CLIP_HITHER;
			}
		}

		result_3d_points++;
		result_2d_points++;
		result_outcode++;
		points++;
	}

	oxmax = active_viewport.x_max - last_transformed_point->i;
	oxmin = last_transformed_point->i - active_viewport.x_min;
	oymax = active_viewport.y_max - last_transformed_point->j;
	oymin = last_transformed_point->j - active_viewport.y_min;

	ixmax = *( ( int * ) &oxmax );
	ixmin = *( ( int * ) &oxmin );
	iymax = *( ( int * ) &oymax );
	iymin = *( ( int * ) &oymin );

	*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

	//
	// Set back the fpu precision mode.
	//

	set_fpu_precision_mode_double ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_flat_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		*result_2d_points,
		*last_transformed_point,
		temp_last_transformed_point;

	unsigned char
		*result_outcode,
		*last_transformed_point_outcode,
		temp_last_transformed_point_outcode;

	float
		pos_x,
		pos_y,
		pos_z,
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;

	//
	// We only need the fpu to be in single precision mode
	//

	set_fpu_precision_mode_single ();

	number_of_points = object->number_of_points;

	ASSERT ( ( number_of_points + points_base ) < MAX_POINTS );

	points = object->points;

	result_3d_points = &transformed_3d_3d_points[points_base];

	result_2d_points = &transformed_3d_2d_points[points_base];

	result_outcode = &transformed_3d_point_outcodes[points_base];

	last_transformed_point = &temp_last_transformed_point;

	last_transformed_point_outcode = &temp_last_transformed_point_outcode;

	pos_x = pos->x;
	pos_y = pos->y;
	pos_z = pos->z;

	for ( count = number_of_points; count > 0; count-- )
	{

		{

			float
				x,
				y,
				z;

			x = pos_x;
			x += points->x * rotation_3d[0][0];
			x += points->z * rotation_3d[2][0];

			y = pos_y;
			y += points->x * rotation_3d[0][1];
			y += points->z * rotation_3d[2][1];

			z = pos_z;
			z += points->x * rotation_3d[0][2];
			z += points->z * rotation_3d[2][2];

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{

				float
					q,
					i,
					j;

				oxmax = active_viewport.x_max - last_transformed_point->i;
				oxmin = last_transformed_point->i - active_viewport.x_min;
				oymax = active_viewport.y_max - last_transformed_point->j;
				oymin = last_transformed_point->j - active_viewport.y_min;

				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );

				q = 1.0 / z;

//				start_float_divide ( z, 1.0 );

				*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				result_3d_points->x = x;

				result_3d_points->y = y;

				last_transformed_point = result_2d_points;

				last_transformed_point_outcode = result_outcode;

//				q = end_float_divide ();

				i = ( active_3d_environment->screen_i_scale * x * q );

				j = ( active_3d_environment->screen_j_scale * y * q );

				result_2d_points->j = active_3d_environment->y_origin - j;

				result_2d_points->i = active_3d_environment->x_origin + i;

				result_2d_points->q = q;

				result_2d_points->z = z;
			}
			else
			{

				*result_outcode = CLIP_HITHER;

				result_2d_points->z = z;

				result_3d_points->x = x;

				result_3d_points->y = y;
			}

#if DEBUG_STATS
			current_number_of_3d_points_transformed++;
#endif
		}

		result_3d_points++;
		result_2d_points++;
		result_outcode++;
		points++;
	}

	oxmax = active_viewport.x_max - last_transformed_point->i;
	oxmin = last_transformed_point->i - active_viewport.x_min;
	oymax = active_viewport.y_max - last_transformed_point->j;
	oymin = last_transformed_point->j - active_viewport.y_min;

	ixmax = *( ( int * ) &oxmax );
	ixmin = *( ( int * ) &oxmin );
	iymax = *( ( int * ) &oymax );
	iymin = *( ( int * ) &oymin );

	*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

	//
	// Set back the fpu precision mode.
	//

	set_fpu_precision_mode_double ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_unclipped_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	object_transformed_2d_point
		*result_2d_points;

	float
		xmax,
		ymax,
		zmax,
		pos_x,
		pos_y,
		pos_z;

	//
	// We only need the fpu to be in single precision mode
	//

	set_fpu_precision_mode_single ();

	number_of_points = object->number_of_points;

	ASSERT ( ( number_of_points + points_base ) < MAX_POINTS );

	points = object->points;

	result_2d_points = &transformed_3d_2d_points[points_base];

	environment_x_origin = active_3d_environment->x_origin;
	environment_y_origin = active_3d_environment->y_origin;

	pos_x = pos->x * active_3d_environment->screen_i_scale;
	pos_y = pos->y * active_3d_environment->screen_j_scale;
	pos_z = pos->z;

	xmax = max ( fabs ( object->bounding_box.xmin ), fabs ( object->bounding_box.xmax ) );
	ymax = max ( fabs ( object->bounding_box.ymin ), fabs ( object->bounding_box.ymax ) );
	zmax = max ( fabs ( object->bounding_box.zmin ), fabs ( object->bounding_box.zmax ) );

	scaled_rotation[0][0] = rotation_3d[0][0] * active_3d_environment->screen_i_scale * ( xmax / 32767.0 );
	scaled_rotation[0][1] = rotation_3d[0][1] * active_3d_environment->screen_j_scale * ( xmax / 32767.0 );
	scaled_rotation[0][2] = rotation_3d[0][2] * ( xmax / 32767.0 );

	scaled_rotation[1][0] = rotation_3d[1][0] * active_3d_environment->screen_i_scale * ( ymax / 32767.0 );
	scaled_rotation[1][1] = rotation_3d[1][1] * active_3d_environment->screen_j_scale * ( ymax / 32767.0 );
	scaled_rotation[1][2] = rotation_3d[1][2] * ( ymax / 32767.0 );

	scaled_rotation[2][0] = rotation_3d[2][0] * active_3d_environment->screen_i_scale * ( zmax / 32767.0 );
	scaled_rotation[2][1] = rotation_3d[2][1] * active_3d_environment->screen_j_scale * ( zmax / 32767.0 );
	scaled_rotation[2][2] = rotation_3d[2][2] * ( zmax / 32767.0 );

	for ( count = number_of_points; count > 0; count-- )
	{

		{

			float
				point_x,
				point_y,
				point_z,
				x,
				y;

			point_x = points->x;
			point_y = points->y;
			point_z = points->z;

			x = pos_x;
			x += point_x * scaled_rotation[0][0];
			x += point_y * scaled_rotation[1][0];
			x += point_z * scaled_rotation[2][0];

			y = pos_y;
			y += point_x * scaled_rotation[0][1];
			y += point_y * scaled_rotation[1][1];
			y += point_z * scaled_rotation[2][1];

			result_2d_points->z = pos_z +
											 point_x * scaled_rotation[0][2] +
											 point_y * scaled_rotation[1][2] +
											 point_z * scaled_rotation[2][2];

			result_2d_points->q = ( 1.0 / result_2d_points->z );

			result_2d_points->j = environment_y_origin - ( y * result_2d_points->q );
			result_2d_points->i = environment_x_origin + ( x * result_2d_points->q );

#if DEBUG_STATS
			current_number_of_3d_points_transformed++;
#endif
		}

		result_2d_points++;
		points++;
	}

	//
	// Set back the fpu precision mode.
	//

	set_fpu_precision_mode_double ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_unclipped_flat_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	object_transformed_2d_point
		*result_2d_points;

	float
		pos_x,
		pos_y,
		pos_z;

	//
	// We only need the fpu to be in single precision mode
	//

	set_fpu_precision_mode_single ();

	number_of_points = object->number_of_points;

	ASSERT ( ( number_of_points + points_base ) < MAX_POINTS );

	points = object->points;

	result_2d_points = &transformed_3d_2d_points[points_base];

	pos_x = pos->x;
	pos_y = pos->y;
	pos_z = pos->z;

	for ( count = number_of_points; count > 0; count-- )
	{

		{

			float
				pointx,
				pointz,
				x,
				y,
				z,
				q,
				i,
				j;

			pointx = points->x;
			pointz = points->z;

			x = pointx * rotation_3d[0][0];
			y = pointx * rotation_3d[0][1];
			z = pointx * rotation_3d[0][2];

			x += pointz * rotation_3d[2][0];
			y += pointz * rotation_3d[2][1];
			z += pointz * rotation_3d[2][2];

			x += pos_x;
			y += pos_y;
			z += pos_z;

			q = 1.0 / z;

			i = ( active_3d_environment->screen_i_scale * x * q );
			j = ( active_3d_environment->screen_j_scale * y * q );

			result_2d_points->j = active_3d_environment->y_origin - j;
			result_2d_points->i = active_3d_environment->x_origin + i;

			result_2d_points->q = q;
			result_2d_points->z = z;

#if DEBUG_STATS
			current_number_of_3d_points_transformed++;
#endif
		}

		result_2d_points++;
		points++;
	}

	//
	// Set back the fpu precision mode.
	//

	set_fpu_precision_mode_double ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void illuminate_3d_object_surface ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base )
{

	int
		number_of_points,
		point_index,
		count;

	object_3d_transformed_point_normal
		*result_normals;

	point_3d_plain_reference
		*point_list;

	object_3d_heading_pitch_normal
		*normals;

	vec3d
		normal;

	if ( !object->number_of_lighting_normals )
	{

		return;
	}

	result_normals = &transformed_3d_normals[points_base];

	normals = object->point_normals;

	if ( current_object_3d_surface->smoothed )
	{

		point_list = current_object_3d_surface_point_normal_list;

		number_of_points = current_object_3d_surface->number_of_points;

		if ( number_of_points == 0 )
		{

			number_of_points = 256;
		}

		ASSERT ( ( number_of_points + points_base ) < MAX_POINTS );

		if ( !lights )
		{

			int
				ir,
				ig,
				ib;

			real_colour
				normal_colour;

			asm_convert_float_to_int (  ( ambient_3d_light.colour.red * 255 ), &ir );
			asm_convert_float_to_int (  ( ambient_3d_light.colour.green * 255 ), &ig );
			asm_convert_float_to_int (  ( ambient_3d_light.colour.blue * 255 ), &ib );

			normal_colour.red = ir;
			normal_colour.green = ig;
			normal_colour.blue = ib;
			normal_colour.alpha = current_object_3d_dissolve_value;

			for ( count = number_of_points; count > 0; count-- )
			{

				point_index = point_list->point;

				result_normals[point_index].colour = normal_colour.colour;
				result_normals[point_index].specular = 0;

				point_list++;
			}
		}
		else if ( !lights->succ )
		{

			vec3d
				light_vector,
				highlight_vector;

			light_vector.x = lights->lx;
			light_vector.y = lights->ly;
			light_vector.z = lights->lz;

			highlight_vector.x = lights->highlight_vector.x;
			highlight_vector.y = lights->highlight_vector.y;
			highlight_vector.z = lights->highlight_vector.z;

			for ( count = number_of_points; count > 0; count-- )
			{

				float
					r,
					g,
					b,
					s,
					d_intensity,
					s_intensity;

				int
					ir,
					ig,
					ib;

				//
				// Set the light levels
				//

				r = ambient_3d_light.colour.red;
				g = ambient_3d_light.colour.green;
				b = ambient_3d_light.colour.blue;

				s = 0;

				point_index = point_list->point;

				generate_object_3d_point_normal ( &normals[point_index], &normal );

				//
				// Calculate diffuse colour intensities
				//

				d_intensity = normal.x * lights->lx + normal.y * lights->ly + normal.z * lights->lz;
				s_intensity =	normal.x * lights->highlight_vector.x +
									normal.y * lights->highlight_vector.y +
									normal.z * lights->highlight_vector.z;

//				d_intensity *= 1.0 / 32767.0;
//				s_intensity *= 1.0 / 32767.0;

				if ( *( ( int *) &d_intensity ) > *( ( int *) &float_value_zero ) )
				{

					d_intensity *= d_intensity;

					r += d_intensity * lights->colour.red;
					g += d_intensity * lights->colour.green;
					b += d_intensity * lights->colour.blue;
				}

				//
				// Calculate specular colour intensities
				//

				if ( *( ( int *) &s_intensity ) > *( ( int *) &float_value_zero ) )
				{

					s_intensity *= s_intensity;
					s_intensity *= s_intensity;
					s_intensity *= s_intensity;
					s_intensity *= s_intensity;
					s_intensity *= s_intensity;

					s += s_intensity * lights->intensity;
				}

				if ( *( ( int *) &r ) > *( ( int *) &float_value_one ) )	{ r = 1.0; }
				if ( *( ( int *) &g ) > *( ( int *) &float_value_one ) )	{ g = 1.0; }
				if ( *( ( int *) &b ) > *( ( int *) &float_value_one ) )	{ b = 1.0; }
				if ( *( ( int *) &s ) > *( ( int *) &float_value_one ) )	{ s = 1.0; }

				asm_convert_float_to_int ( ( r * 255 ), &ir );
				asm_convert_float_to_int ( ( g * 255 ), &ig );
				asm_convert_float_to_int ( ( b * 255 ), &ib );

				result_normals[point_index].r = ir;
				result_normals[point_index].g = ig;
				result_normals[point_index].b = ib;
				result_normals[point_index].alpha = current_object_3d_dissolve_value;
				result_normals[point_index].specular = s;

				point_list++;
			}
		}
		else
		{

			for ( count = number_of_points; count > 0; count-- )
			{

				float
					r,
					g,
					b,
					specular;

				int
					ir,
					ig,
					ib;

				light_3d_source
					*this_light;

				//
				// Set the light levels
				//

				r = ambient_3d_light.colour.red;
				g = ambient_3d_light.colour.green;
				b = ambient_3d_light.colour.blue;

				specular = 0;

				point_index = point_list->point;

				generate_object_3d_point_normal ( &normals[point_index], &normal );

				this_light = lights;

				while ( this_light )
				{

					float
						temp_intensity;

					//
					// Calculate diffuse colour intensities
					//

					temp_intensity = normal.x * this_light->lx + normal.y * this_light->ly + normal.z * this_light->lz;
//					temp_intensity *= 1.0 / 32767.0;

					if ( *( ( int *) &temp_intensity ) > *( ( int *) &float_value_zero ) )
					{

						temp_intensity *= temp_intensity;

						r += temp_intensity * this_light->colour.red;
						g += temp_intensity * this_light->colour.green;
						b += temp_intensity * this_light->colour.blue;
					}

					//
					// Calculate specular colour intensities
					//

					temp_intensity = normal.x * this_light->highlight_vector.x +
											normal.y * this_light->highlight_vector.y +
											normal.z * this_light->highlight_vector.z;

//					temp_intensity *= 1.0 / 32767.0;

					if ( *( ( int *) &temp_intensity ) > *( ( int *) &float_value_zero ) )
					{

						temp_intensity *= temp_intensity;
						temp_intensity *= temp_intensity;
						temp_intensity *= temp_intensity;
						temp_intensity *= temp_intensity;
						temp_intensity *= temp_intensity;

						specular += temp_intensity * this_light->intensity;
					}

					this_light = this_light->succ;
				}

				if ( *( ( int *) &r ) > *( ( int *) &float_value_one ) )	{ r = 1.0; }
				if ( *( ( int *) &g ) > *( ( int *) &float_value_one ) )	{ g = 1.0; }
				if ( *( ( int *) &b ) > *( ( int *) &float_value_one ) )	{ b = 1.0; }
				if ( *( ( int *) &specular ) > *( ( int *) &float_value_one ) )	{ specular = 1.0; }

				asm_convert_float_to_int ( ( r * 255 ), &ir );
				asm_convert_float_to_int ( ( g * 255 ), &ig );
				asm_convert_float_to_int ( ( b * 255 ), &ib );

				result_normals[point_index].r = ir;
				result_normals[point_index].g = ig;
				result_normals[point_index].b = ib;
				result_normals[point_index].alpha = current_object_3d_dissolve_value;
				result_normals[point_index].specular = specular;

				point_list++;
			}
		}
	}
	else
	{
		ASSERT ( current_object_3d_surface->polygons );

		point_list = current_object_3d_face_normal_list;

		number_of_points = current_object_3d_surface->number_of_faces;

		if ( !lights )
		{

			int
				ir,
				ig,
				ib;

			real_colour
				normal_colour;

			asm_convert_float_to_int (  ( ambient_3d_light.colour.red * 255 ), &ir );
			asm_convert_float_to_int (  ( ambient_3d_light.colour.green * 255 ), &ig );
			asm_convert_float_to_int (  ( ambient_3d_light.colour.blue * 255 ), &ib );

			normal_colour.red = ir;
			normal_colour.green = ig;
			normal_colour.blue = ib;
			normal_colour.alpha = current_object_3d_dissolve_value;

			for ( count = number_of_points; count > 0; count-- )
			{

				point_index = point_list->point;

				result_normals[point_index].colour = normal_colour.colour;
				result_normals[point_index].specular = 0;

				point_list++;
			}
		}
		else if ( !lights->succ )
		{

			vec3d
				light_vector,
				highlight_vector;

			light_vector.x = lights->lx;
			light_vector.y = lights->ly;
			light_vector.z = lights->lz;

			highlight_vector.x = lights->highlight_vector.x;
			highlight_vector.y = lights->highlight_vector.y;
			highlight_vector.z = lights->highlight_vector.z;

			for ( count = number_of_points; count > 0; count-- )
			{

				float
					r,
					g,
					b,
					s,
					d_intensity,
					s_intensity;

				int
					ir,
					ig,
					ib;

				//
				// Set the light levels
				//

				r = ambient_3d_light.colour.red;
				g = ambient_3d_light.colour.green;
				b = ambient_3d_light.colour.blue;

				s = 0;

				point_index = point_list->point;

				generate_object_3d_point_normal ( &normals[point_index], &normal );

				//
				// Calculate diffuse colour intensities
				//

				d_intensity = normal.x * lights->lx + normal.y * lights->ly + normal.z * lights->lz;
				s_intensity =	normal.x * lights->highlight_vector.x +
									normal.y * lights->highlight_vector.y +
									normal.z * lights->highlight_vector.z;

//				d_intensity *= 1.0 / 32767.0;
//				s_intensity *= 1.0 / 32767.0;

				if ( *( ( int *) &d_intensity ) > *( ( int *) &float_value_zero ) )
				{

					d_intensity *= d_intensity;

					r += d_intensity * lights->colour.red;
					g += d_intensity * lights->colour.green;
					b += d_intensity * lights->colour.blue;
				}

				//
				// Calculate specular colour intensities
				//

				if ( *( ( int *) &s_intensity ) > *( ( int *) &float_value_zero ) )
				{

					s_intensity *= s_intensity;
					s_intensity *= s_intensity;
					s_intensity *= s_intensity;
					s_intensity *= s_intensity;
					s_intensity *= s_intensity;

					s += s_intensity * lights->intensity;
				}

				if ( *( ( int *) &r ) > *( ( int *) &float_value_one ) )	{ r = 1.0; }
				if ( *( ( int *) &g ) > *( ( int *) &float_value_one ) )	{ g = 1.0; }
				if ( *( ( int *) &b ) > *( ( int *) &float_value_one ) )	{ b = 1.0; }
				if ( *( ( int *) &s ) > *( ( int *) &float_value_one ) )	{ s = 1.0; }

				asm_convert_float_to_int ( ( r * 255 ), &ir );
				asm_convert_float_to_int ( ( g * 255 ), &ig );
				asm_convert_float_to_int ( ( b * 255 ), &ib );

				result_normals[point_index].r = ir;
				result_normals[point_index].g = ig;
				result_normals[point_index].b = ib;
				result_normals[point_index].alpha = current_object_3d_dissolve_value;
				result_normals[point_index].specular = s;

				point_list++;
			}
		}
		else
		{

			for ( count = number_of_points; count > 0; count-- )
			{

				float
					r,
					g,
					b,
					specular;

				int
					ir,
					ig,
					ib;

				light_3d_source
					*this_light;

				//
				// Set the light levels
				//

				r = ambient_3d_light.colour.red;
				g = ambient_3d_light.colour.green;
				b = ambient_3d_light.colour.blue;

				specular = 0;

				point_index = point_list->point;

				generate_object_3d_point_normal ( &normals[point_index], &normal );

				this_light = lights;

				while ( this_light )
				{

					float
						temp_intensity;

					//
					// Calculate diffuse colour intensities
					//

					temp_intensity = normal.x * this_light->lx + normal.y * this_light->ly + normal.z * this_light->lz;
//					temp_intensity *= 1.0 / 32767.0;

					if ( *( ( int *) &temp_intensity ) > *( ( int *) &float_value_zero ) )
					{

						temp_intensity *= temp_intensity;

						r += temp_intensity * this_light->colour.red;
						g += temp_intensity * this_light->colour.green;
						b += temp_intensity * this_light->colour.blue;
					}

					//
					// Calculate specular colour intensities
					//

					temp_intensity = normal.x * this_light->highlight_vector.x +
											normal.y * this_light->highlight_vector.y +
											normal.z * this_light->highlight_vector.z;

//					temp_intensity *= 1.0 / 32767.0;

					if ( *( ( int *) &temp_intensity ) > *( ( int *) &float_value_zero ) )
					{

						temp_intensity *= temp_intensity;
						temp_intensity *= temp_intensity;
						temp_intensity *= temp_intensity;
						temp_intensity *= temp_intensity;
						temp_intensity *= temp_intensity;

						specular += temp_intensity * this_light->intensity;
					}

					this_light = this_light->succ;
				}

				if ( *( ( int *) &r ) > *( ( int *) &float_value_one ) )	{ r = 1.0; }
				if ( *( ( int *) &g ) > *( ( int *) &float_value_one ) )	{ g = 1.0; }
				if ( *( ( int *) &b ) > *( ( int *) &float_value_one ) )	{ b = 1.0; }
				if ( *( ( int *) &specular ) > *( ( int *) &float_value_one ) )	{ specular = 1.0; }

				asm_convert_float_to_int ( ( r * 255 ), &ir );
				asm_convert_float_to_int ( ( g * 255 ), &ig );
				asm_convert_float_to_int ( ( b * 255 ), &ib );

				result_normals[point_index].r = ir;
				result_normals[point_index].g = ig;
				result_normals[point_index].b = ib;
				result_normals[point_index].alpha = current_object_3d_dissolve_value;
				result_normals[point_index].specular = specular;

				point_list++;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_object_surface ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		*result_2d_points,
		*last_transformed_point,
		temp_last_transformed_point;

	unsigned char
		*result_outcode,
		*last_transformed_point_outcode,
		temp_last_transformed_point_outcode;

	float
		pos_x,
		pos_y,
		pos_z,
		xmax,
		ymax,
		zmax,
		oxmax,
		oxmin,
		oymax,
		oymin;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	point_3d_plain_reference
		*point_list;

	point_list = current_object_3d_surface_point_list;

	number_of_points = current_object_3d_surface->number_of_points;

	if ( number_of_points == 0 )
	{

		number_of_points = 256;
	}

	ASSERT ( ( number_of_points + points_base ) < MAX_POINTS );

	points = object->points;

	result_3d_points = &transformed_3d_3d_points[points_base];

	result_2d_points = &transformed_3d_2d_points[points_base];

	result_outcode = &transformed_3d_point_outcodes[points_base];

	last_transformed_point = &temp_last_transformed_point;

	last_transformed_point_outcode = &temp_last_transformed_point_outcode;

	environment_x_origin = active_3d_environment->x_origin;
	environment_y_origin = active_3d_environment->y_origin;

	pos_x = pos->x * active_3d_environment->screen_i_scale;
	pos_y = pos->y * active_3d_environment->screen_j_scale;
	pos_z = pos->z;

	xmax = max ( fabs ( object->bounding_box.xmin ), fabs ( object->bounding_box.xmax ) );
	ymax = max ( fabs ( object->bounding_box.ymin ), fabs ( object->bounding_box.ymax ) );
	zmax = max ( fabs ( object->bounding_box.zmin ), fabs ( object->bounding_box.zmax ) );

	scaled_rotation[0][0] = rotation_3d[0][0] * active_3d_environment->screen_i_scale * ( xmax / 32767.0 );
	scaled_rotation[0][1] = rotation_3d[0][1] * active_3d_environment->screen_j_scale * ( xmax / 32767.0 );
	scaled_rotation[0][2] = rotation_3d[0][2] * ( xmax / 32767.0 );

	scaled_rotation[1][0] = rotation_3d[1][0] * active_3d_environment->screen_i_scale * ( ymax / 32767.0 );
	scaled_rotation[1][1] = rotation_3d[1][1] * active_3d_environment->screen_j_scale * ( ymax / 32767.0 );
	scaled_rotation[1][2] = rotation_3d[1][2] * ( ymax / 32767.0 );

	scaled_rotation[2][0] = rotation_3d[2][0] * active_3d_environment->screen_i_scale * ( zmax / 32767.0 );
	scaled_rotation[2][1] = rotation_3d[2][1] * active_3d_environment->screen_j_scale * ( zmax / 32767.0 );
	scaled_rotation[2][2] = rotation_3d[2][2] * ( zmax / 32767.0 );

	for ( count = number_of_points; count > 0; count-- )
	{

		{

			float
				point_x,
				point_y,
				point_z,
				x,
				y,
				z;

			int
				point_index;

			point_index = point_list->point;
			point_x = points[point_index].x;
			point_y = points[point_index].y;
			point_z = points[point_index].z;

			x = pos_x + point_x * scaled_rotation[0][0] + point_y * scaled_rotation[1][0] + point_z * scaled_rotation[2][0];
			y = pos_y + point_x * scaled_rotation[0][1] + point_y * scaled_rotation[1][1] + point_z * scaled_rotation[2][1];
			z = pos_z + point_x * scaled_rotation[0][2] + point_y * scaled_rotation[1][2] + point_z * scaled_rotation[2][2];

			result_3d_points[point_index].x = x;
			result_3d_points[point_index].y = y;
			result_2d_points[point_index].z = z;

			if ( *( ( int * ) &result_2d_points[point_index].z ) >= *( ( int * ) &clip_hither ) )
			{

				float
					q,
					i,
					j;

				oxmax = active_viewport.x_max - last_transformed_point->i;
				oxmin = last_transformed_point->i - active_viewport.x_min;
				oymax = active_viewport.y_max - last_transformed_point->j;
				oymin = last_transformed_point->j - active_viewport.y_min;

				ixmax = *( ( unsigned int * ) &oxmax );
				ixmin = *( ( unsigned int * ) &oxmin );
				iymax = *( ( unsigned int * ) &oymax );
				iymin = *( ( unsigned int * ) &oymin );

				q = 1.0 / result_2d_points[point_index].z;

				ixmin >>= 31;
				iymin &= 0x80000000;
				ixmax >>= 29;
				iymax &= 0x80000000;
				iymin >>= 30;
				ixmin &= 0x00000001;
				iymax >>= 28;
				ixmax &= 0x00000004;
				ixmin |= iymin;
				ixmax |= iymax;
				*last_transformed_point_outcode = ( ixmin | ixmax );

				last_transformed_point = &result_2d_points[point_index];

				last_transformed_point_outcode = &result_outcode[point_index];

				i = ( result_3d_points[point_index].x * q );
				j = ( result_3d_points[point_index].y * q );

				result_2d_points[point_index].q = q;
				result_2d_points[point_index].j = environment_y_origin - j;
				result_2d_points[point_index].i = environment_x_origin + i;

#if DEBUG_STATS
				current_number_of_3d_points_transformed++;
#endif
			}
			else
			{

				result_outcode[point_index] = CLIP_HITHER;
			}
		}

		point_list++;
	}

	oxmax = active_viewport.x_max - last_transformed_point->i;
	oxmin = last_transformed_point->i - active_viewport.x_min;
	oymax = active_viewport.y_max - last_transformed_point->j;
	oymin = last_transformed_point->j - active_viewport.y_min;

	ixmax = *( ( int * ) &oxmax );
	ixmin = *( ( int * ) &oxmin );
	iymax = *( ( int * ) &oymax );
	iymin = *( ( int * ) &oymin );

	*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_unclipped_3d_object_surface ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		*result_2d_points;

	float
		pos_x,
		pos_y,
		pos_z,
		xmax,
		ymax,
		zmax;

	point_3d_plain_reference
		*point_list;

	point_list = current_object_3d_surface_point_list;

	number_of_points = current_object_3d_surface->number_of_points;

	if ( number_of_points == 0 )
	{

		number_of_points = 256;
	}

	ASSERT ( ( number_of_points + points_base ) < MAX_POINTS );

	points = object->points;

	result_3d_points = &transformed_3d_3d_points[points_base];

	result_2d_points = &transformed_3d_2d_points[points_base];

	environment_x_origin = active_3d_environment->x_origin;
	environment_y_origin = active_3d_environment->y_origin;

	pos_x = pos->x * active_3d_environment->screen_i_scale;
	pos_y = pos->y * active_3d_environment->screen_j_scale;
	pos_z = pos->z;

	xmax = max ( fabs ( object->bounding_box.xmin ), fabs ( object->bounding_box.xmax ) );
	ymax = max ( fabs ( object->bounding_box.ymin ), fabs ( object->bounding_box.ymax ) );
	zmax = max ( fabs ( object->bounding_box.zmin ), fabs ( object->bounding_box.zmax ) );

	scaled_rotation[0][0] = rotation_3d[0][0] * active_3d_environment->screen_i_scale * ( xmax / 32767.0 );
	scaled_rotation[0][1] = rotation_3d[0][1] * active_3d_environment->screen_j_scale * ( xmax / 32767.0 );
	scaled_rotation[0][2] = rotation_3d[0][2] * ( xmax / 32767.0 );

	scaled_rotation[1][0] = rotation_3d[1][0] * active_3d_environment->screen_i_scale * ( ymax / 32767.0 );
	scaled_rotation[1][1] = rotation_3d[1][1] * active_3d_environment->screen_j_scale * ( ymax / 32767.0 );
	scaled_rotation[1][2] = rotation_3d[1][2] * ( ymax / 32767.0 );

	scaled_rotation[2][0] = rotation_3d[2][0] * active_3d_environment->screen_i_scale * ( zmax / 32767.0 );
	scaled_rotation[2][1] = rotation_3d[2][1] * active_3d_environment->screen_j_scale * ( zmax / 32767.0 );
	scaled_rotation[2][2] = rotation_3d[2][2] * ( zmax / 32767.0 );

	for ( count = number_of_points; count > 0; count-- )
	{

		float
			point_x,
			point_y,
			point_z,
			x,
			y,
			z,
			q,
			i,
			j;

		int
			point_index;

		point_index = point_list->point;
		point_x = points[point_index].x;
		point_y = points[point_index].y;
		point_z = points[point_index].z;

		x = pos_x + point_x * scaled_rotation[0][0] + point_y * scaled_rotation[1][0] + point_z * scaled_rotation[2][0];
		y = pos_y + point_x * scaled_rotation[0][1] + point_y * scaled_rotation[1][1] + point_z * scaled_rotation[2][1];
		z = pos_z + point_x * scaled_rotation[0][2] + point_y * scaled_rotation[1][2] + point_z * scaled_rotation[2][2];

		q = 1.0 / z;

		result_3d_points[point_index].x = x;
		result_3d_points[point_index].y = y;
		result_2d_points[point_index].z = z;

		i = ( x * q );
		j = ( y * q );

		result_2d_points[point_index].q = q;
		result_2d_points[point_index].j = environment_y_origin - j;
		result_2d_points[point_index].i = environment_x_origin + i;

#if DEBUG_STATS
		current_number_of_3d_points_transformed++;
#endif

		point_list++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
