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

void set_object_3d_instance_relative_position ( object_3d_instance *obj )
{

	vec3d
		relative_position;

	relative_position.x = obj->vp.x - visual_3d_vp->x;
	relative_position.y = obj->vp.y - visual_3d_vp->y;
	relative_position.z = obj->vp.z - visual_3d_vp->z;

	obj->view_position.x = ( relative_position.x * visual_3d_vp->xv.x + relative_position.y * visual_3d_vp->xv.y + relative_position.z * visual_3d_vp->xv.z );
	obj->view_position.y = ( relative_position.x * visual_3d_vp->yv.x + relative_position.y * visual_3d_vp->yv.y + relative_position.z * visual_3d_vp->yv.z );
	obj->view_position.z = ( relative_position.x * visual_3d_vp->zv.x + relative_position.y * visual_3d_vp->zv.y + relative_position.z * visual_3d_vp->zv.z );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_position_3d_relative_position ( vec3d *position, vec3d *r )
{

	vec3d
		relative_position;

	relative_position.x = position->x - visual_3d_vp->x;
	relative_position.y = position->y - visual_3d_vp->y;
	relative_position.z = position->z - visual_3d_vp->z;

	r->x = ( relative_position.x * visual_3d_vp->xv.x + relative_position.y * visual_3d_vp->xv.y + relative_position.z * visual_3d_vp->xv.z );
	r->y = ( relative_position.x * visual_3d_vp->yv.x + relative_position.y * visual_3d_vp->yv.y + relative_position.z * visual_3d_vp->yv.z );
	r->z = ( relative_position.x * visual_3d_vp->zv.x + relative_position.y * visual_3d_vp->zv.y + relative_position.z * visual_3d_vp->zv.z );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum OBJECT_3D_VISIBILITY get_position_3d_screen_coordinates ( vec3d *position, float *x, float *y )
{

	vec3d
		relative_position;

	float
		q,
		i,
		j;

	get_position_3d_relative_position ( position, &relative_position );

	if ( relative_position.z < clip_hither )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}

	q = 1.0 / relative_position.z;

	i = ( active_3d_environment->screen_i_scale * relative_position.x * q );
	j = ( active_3d_environment->screen_j_scale * relative_position.y * q );

	*x = active_3d_environment->x_origin + i;
	*y = active_3d_environment->y_origin - j;

	return ( OBJECT_3D_COMPLETELY_VISIBLE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum OBJECT_3D_VISIBILITY get_object_3d_screen_coordinates ( object_3d_instance *obj, float *x, float *y )
{

	float
		radius,
		z,
		q,
		i,
		j;

	int
		object_number,
		outcode,
		outcode1,
		outcode2;

	float
		screenx,
		screeny,
		width,
		height;

	set_object_3d_instance_relative_position ( obj );

	object_number = objects_3d_scene_database[obj->object_number].index;

	radius = objects_3d_scene_database[obj->object_number].radius;

//	if ( obj->rel_vp.z < clip_hither )
	if ( obj->view_position.z < clip_hither )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}

	z = obj->view_position.z;	//rel_vp.z;

	//
	// It is possible for this object to be labelled completely visible.
	//

	q = 1.0 / z;

//	i = ( active_3d_environment->screen_i_scale * obj->rel_vp.x * q );
	i = ( active_3d_environment->screen_i_scale * obj->view_position.x * q );

//	j = ( active_3d_environment->screen_j_scale * obj->rel_vp.y * q );
	j = ( active_3d_environment->screen_j_scale * obj->view_position.y * q );

	width = active_3d_environment->screen_i_scale * radius * q;

	height = active_3d_environment->screen_j_scale * radius * q;

	screeny = ( active_3d_environment->y_origin - j );

	screenx = ( active_3d_environment->x_origin + i );

	outcode = generate_3d_outcode ( screenx, screeny );
	outcode1 = outcode;
	outcode2 = outcode;

	screenx += width;
	outcode = generate_3d_outcode ( screenx, screeny );
	outcode1 |= outcode;
	outcode2 &= outcode;

	screenx -= width;
	screeny += height;
	outcode = generate_3d_outcode ( screenx, screeny );
	outcode1 |= outcode;
	outcode2 &= outcode;

	screenx -= width;
	screeny -= height;
	outcode = generate_3d_outcode ( screenx, screeny );
	outcode1 |= outcode;
	outcode2 &= outcode;

	screenx += width;
	screeny -= height;
	outcode = generate_3d_outcode ( screenx, screeny );
	outcode1 |= outcode;
	outcode2 &= outcode;

	if ( outcode2 != 0 )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}

	if ( outcode1 == 0 )
	{

		*x = i + active_3d_environment->x_origin;

		*y = active_3d_environment->y_origin - j;
	
		return ( OBJECT_3D_COMPLETELY_VISIBLE );
	}

	*x = i + active_3d_environment->x_origin;

	*y = active_3d_environment->y_origin - j;

	return ( OBJECT_3D_PARTIALLY_VISIBLE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum OBJECT_3D_VISIBILITY get_object_3d_instance_visibility ( object_3d_instance *obj )
{

	float
		radius,
		z,
		q,
		i,
		j;

	int
		object_number,
		outcode,
		outcode1,
		outcode2;

	float
		screenx,
		screeny,
		width,
		height,
		scale;

	object_number = objects_3d_scene_database[obj->object_number].index;

	radius = objects_3d_scene_database[obj->object_number].radius;

	scale = max ( 1.0, obj->relative_scale.x );
	scale = max ( scale, obj->relative_scale.y );
	scale = max ( scale, obj->relative_scale.z );

	radius *= scale;

	if ( ( obj->view_position.z + radius ) < clip_hither )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}

	z = obj->view_position.z - radius;

	if ( z > clip_hither )
	{

		//
		// It is possible for this object to be labelled completely visible.
		//

		z += radius;

		q = 1.0 / z;
	
		i = ( active_3d_environment->screen_i_scale * obj->view_position.x * q );
	
		j = ( active_3d_environment->screen_j_scale * obj->view_position.y * q );
	
		width = active_3d_environment->screen_i_scale * radius * q;
	
		height = active_3d_environment->screen_j_scale * radius * q;
	
		screeny = ( active_3d_environment->y_origin - j );
	
		screenx = ( active_3d_environment->x_origin + i );
	
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 = outcode;
		outcode2 = outcode;

		screenx += width;
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx -= width;
		screeny += height;
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx -= width;
		screeny -= height;
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx += width;
		screeny -= height;
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		if ( outcode2 != 0 )
		{

			return ( OBJECT_3D_NOT_VISIBLE );
		}
	
		if ( outcode1 == 0 )
		{

			return ( OBJECT_3D_COMPLETELY_VISIBLE );
		}
	
		return ( OBJECT_3D_PARTIALLY_VISIBLE );
	}
	else
	{

		//
		// The object cannot be completely visible, as it intersects the eye_distance plane
		//

		return ( OBJECT_3D_PARTIALLY_VISIBLE );
/*
		z = obj->view_position.z + radius;
	
		q = 1.0 / z;
	
		i = ( active_3d_environment->screen_i_scale * obj->view_position.x * q );
	
		j = ( active_3d_environment->screen_j_scale * obj->view_position.y * q );
	
		width = active_3d_environment->screen_i_scale * radius * q;
	
		height = active_3d_environment->screen_j_scale * radius * q;
	
		screeny = ( active_3d_environment->y_origin - j );
	
		screenx = ( active_3d_environment->x_origin + i );
	
		outcode = generate_3d_outcode ( screenx, screeny );// ( *( ( int * ) &screenx ), *( ( int * ) &screeny ) ); // ( screenx, screeny )
		outcode1 = outcode;
		outcode2 = outcode;

		screenx += width;
		outcode = generate_3d_outcode ( screenx, screeny );// ( *( ( int * ) &screenx ), *( ( int * ) &screeny ) ); // ( screenx + width, screeny )
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx -= width;
		screeny += height;
		outcode = generate_3d_outcode ( screenx, screeny );// ( *( ( int * ) &screenx ), *( ( int * ) &screeny ) ); // ( screenx, screeny + height )
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx -= width;
		screeny -= height;
		outcode = generate_3d_outcode ( screenx, screeny );// ( *( ( int * ) &screenx ), *( ( int * ) &screeny ) ); // ( screenx - width, screeny )
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx += width;
		screeny -= height;
		outcode = generate_3d_outcode ( screenx, screeny );// ( *( ( int * ) &screenx ), *( ( int * ) &screeny ) ); // ( screenx, screeny - height )
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		if ( outcode2 != 0 )
		{

			return ( OBJECT_3D_NOT_VISIBLE );
		}
		else
		{

			return ( OBJECT_3D_PARTIALLY_VISIBLE );
		}
		*/
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum OBJECT_3D_VISIBILITY get_scene_3d_instance_visibility ( object_3d_index_numbers index, vec3d *view_position )
{

	float
		radius,
		z,
		q,
		i,
		j;

	int
		outcode,
		outcode1,
		outcode2;

	float
		screenx,
		screeny,
		width,
		height;

	radius = objects_3d_scene_database[index].radius;

	if ( ( view_position->z + radius ) < clip_hither )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}

	z = view_position->z - radius;

	if ( z > clip_hither )
	{

		//
		// It is possible for this object to be labelled completely visible.
		//

		z += radius;

		q = 1.0 / z;
	
		i = ( active_3d_environment->screen_i_scale * view_position->x * q );
	
		j = ( active_3d_environment->screen_j_scale * view_position->y * q );
	
		width = active_3d_environment->screen_i_scale * radius * q;
	
		height = active_3d_environment->screen_j_scale * radius * q;
	
		screeny = ( active_3d_environment->y_origin - j );
	
		screenx = ( active_3d_environment->x_origin + i );
	
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 = outcode;
		outcode2 = outcode;

		screenx += width;
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx -= width;
		screeny += height;
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx -= width;
		screeny -= height;
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;

		screenx += width;
		screeny -= height;
		outcode = generate_3d_outcode ( screenx, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		if ( outcode2 != 0 )
		{

			return ( OBJECT_3D_NOT_VISIBLE );
		}
	
		if ( outcode1 == 0 )
		{

			return ( OBJECT_3D_COMPLETELY_VISIBLE );
		}
	
		return ( OBJECT_3D_PARTIALLY_VISIBLE );
	}
	else
	{

		//
		// The object cannot be completely visible, as it intersects the eye_distance plane
		//

		return ( OBJECT_3D_PARTIALLY_VISIBLE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// NB - This routine should only ever be called from the object renderer - NOT FOR EXTERNAL USE.
//

int get_object_3d_outcode ( int object_number, vec3d *pos, int *outcode )
{

	int
		bound_count,
		object_outcode,
		object_outcode2;

	vec3d
		box[8];

	//
	// Calculate the bounding box of the object
	//

	box[0].x = objects_3d_data[object_number].bounding_box.xmin;
	box[0].y = objects_3d_data[object_number].bounding_box.ymin;
	box[0].z = objects_3d_data[object_number].bounding_box.zmin;

	box[1].x = objects_3d_data[object_number].bounding_box.xmin;
	box[1].y = objects_3d_data[object_number].bounding_box.ymin;
	box[1].z = objects_3d_data[object_number].bounding_box.zmax;

	box[2].x = objects_3d_data[object_number].bounding_box.xmin;
	box[2].y = objects_3d_data[object_number].bounding_box.ymax;
	box[2].z = objects_3d_data[object_number].bounding_box.zmin;

	box[3].x = objects_3d_data[object_number].bounding_box.xmin;
	box[3].y = objects_3d_data[object_number].bounding_box.ymax;
	box[3].z = objects_3d_data[object_number].bounding_box.zmax;

	box[4].x = objects_3d_data[object_number].bounding_box.xmax;
	box[4].y = objects_3d_data[object_number].bounding_box.ymin;
	box[4].z = objects_3d_data[object_number].bounding_box.zmin;

	box[5].x = objects_3d_data[object_number].bounding_box.xmax;
	box[5].y = objects_3d_data[object_number].bounding_box.ymin;
	box[5].z = objects_3d_data[object_number].bounding_box.zmax;

	box[6].x = objects_3d_data[object_number].bounding_box.xmax;
	box[6].y = objects_3d_data[object_number].bounding_box.ymax;
	box[6].z = objects_3d_data[object_number].bounding_box.zmin;

	box[7].x = objects_3d_data[object_number].bounding_box.xmax;
	box[7].y = objects_3d_data[object_number].bounding_box.ymax;
	box[7].z = objects_3d_data[object_number].bounding_box.zmax;

	object_outcode = 0;
	object_outcode2 = CLIP_ALL;

	for ( bound_count = 0; bound_count < 8; bound_count++ )
	{

		float
			oxmax,
			oxmin,
			oymax,
			oymin;
	
		int
			ixmax,
			ixmin,
			iymax,
			iymin;
	
		float
			x,
			y,
			z;

		x = box[bound_count].x * rotation_3d[0][0];
		y = box[bound_count].x * rotation_3d[0][1];
		z = box[bound_count].x * rotation_3d[0][2];

		x += box[bound_count].y * rotation_3d[1][0];
		y += box[bound_count].y * rotation_3d[1][1];
		z += box[bound_count].y * rotation_3d[1][2];

		x += box[bound_count].z * rotation_3d[2][0];
		y += box[bound_count].z * rotation_3d[2][1];
		z += box[bound_count].z * rotation_3d[2][2];

		x += pos->x;
		y += pos->y;
		z += pos->z;

		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			int
				this_outcode;

			q = 1.0 / z;

			i = ( active_3d_environment->screen_i_scale * x * q );
			j = ( active_3d_environment->screen_j_scale * y * q );

			j = active_3d_environment->y_origin - j;
			i = active_3d_environment->x_origin + i;

			oxmax = active_viewport.x_max - i; oxmin = i - active_viewport.x_min;
			oymax = active_viewport.y_max - j; oymin = j - active_viewport.y_min;

			ixmax = *( ( int * ) &oxmax ); ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax ); iymin = *( ( int * ) &oymin );

			this_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			object_outcode |= this_outcode;
			object_outcode2 &= this_outcode;
		}
		else
		{

			object_outcode |= CLIP_HITHER;
			object_outcode2 &= CLIP_HITHER;
		}
	}

	*outcode = object_outcode;

	return ( object_outcode2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// NB - This routine should only ever be called from the object renderer - NOT FOR EXTERNAL USE.
//

int get_scaled_object_3d_outcode ( int object_number, vec3d *pos, vec3d *scale, int *outcode )
{

	int
		bound_count,
		object_outcode,
		object_outcode2;

	vec3d
		object_centre,
		object_minimum,
		object_maximum;

	object_3d_bounds
		object_bounds;

	vec3d
		box[8];

	//
	// Calculate the bounding box of the object
	//

	object_centre.x = ( objects_3d_data[object_number].bounding_box.xmax + objects_3d_data[object_number].bounding_box.xmin ) / 2;
	object_centre.y = ( objects_3d_data[object_number].bounding_box.ymax + objects_3d_data[object_number].bounding_box.ymin ) / 2;
	object_centre.z = ( objects_3d_data[object_number].bounding_box.zmax + objects_3d_data[object_number].bounding_box.zmin ) / 2;

	object_minimum.x = ( object_centre.x - objects_3d_data[object_number].bounding_box.xmin ) * scale->x;
	object_minimum.y = ( object_centre.y - objects_3d_data[object_number].bounding_box.ymin ) * scale->y;
	object_minimum.z = ( object_centre.z - objects_3d_data[object_number].bounding_box.zmin ) * scale->z;

	object_maximum.x = ( object_centre.x + objects_3d_data[object_number].bounding_box.xmax ) * scale->x;
	object_maximum.y = ( object_centre.y + objects_3d_data[object_number].bounding_box.ymax ) * scale->y;
	object_maximum.z = ( object_centre.z + objects_3d_data[object_number].bounding_box.zmax ) * scale->z;

	object_bounds.xmin = object_centre.x + object_minimum.x;
	object_bounds.xmax = object_centre.x + object_maximum.x;
	object_bounds.ymin = object_centre.y + object_minimum.y;
	object_bounds.ymax = object_centre.y + object_maximum.y;
	object_bounds.zmin = object_centre.z + object_minimum.z;
	object_bounds.zmax = object_centre.z + object_maximum.z;


	box[0].x = object_bounds.xmin;
	box[0].y = object_bounds.ymin;
	box[0].z = object_bounds.zmin;

	box[1].x = object_bounds.xmin;
	box[1].y = object_bounds.ymin;
	box[1].z = object_bounds.zmax;

	box[2].x = object_bounds.xmin;
	box[2].y = object_bounds.ymax;
	box[2].z = object_bounds.zmin;

	box[3].x = object_bounds.xmin;
	box[3].y = object_bounds.ymax;
	box[3].z = object_bounds.zmax;

	box[4].x = object_bounds.xmax;
	box[4].y = object_bounds.ymin;
	box[4].z = object_bounds.zmin;

	box[5].x = object_bounds.xmax;
	box[5].y = object_bounds.ymin;
	box[5].z = object_bounds.zmax;

	box[6].x = object_bounds.xmax;
	box[6].y = object_bounds.ymax;
	box[6].z = object_bounds.zmin;

	box[7].x = object_bounds.xmax;
	box[7].y = object_bounds.ymax;
	box[7].z = object_bounds.zmax;

	object_outcode = 0;
	object_outcode2 = CLIP_ALL;

	for ( bound_count = 0; bound_count < 8; bound_count++ )
	{

		float
			oxmax,
			oxmin,
			oymax,
			oymin;
	
		int
			ixmax,
			ixmin,
			iymax,
			iymin;
	
		float
			x,
			y,
			z;

		x = box[bound_count].x * rotation_3d[0][0];
		y = box[bound_count].x * rotation_3d[0][1];
		z = box[bound_count].x * rotation_3d[0][2];

		x += box[bound_count].y * rotation_3d[1][0];
		y += box[bound_count].y * rotation_3d[1][1];
		z += box[bound_count].y * rotation_3d[1][2];

		x += box[bound_count].z * rotation_3d[2][0];
		y += box[bound_count].z * rotation_3d[2][1];
		z += box[bound_count].z * rotation_3d[2][2];

		x += pos->x;
		y += pos->y;
		z += pos->z;

		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			int
				this_outcode;

			q = 1.0 / z;

			i = ( active_3d_environment->screen_i_scale * x * q );
			j = ( active_3d_environment->screen_j_scale * y * q );

			j = active_3d_environment->y_origin - j;
			i = active_3d_environment->x_origin + i;

			oxmax = active_viewport.x_max - i; oxmin = i - active_viewport.x_min;
			oymax = active_viewport.y_max - j; oymin = j - active_viewport.y_min;

			ixmax = *( ( int * ) &oxmax ); ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax ); iymin = *( ( int * ) &oymin );

			this_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			object_outcode |= this_outcode;
			object_outcode2 &= this_outcode;
		}
		else
		{

			object_outcode |= CLIP_HITHER;
			object_outcode2 &= CLIP_HITHER;
		}
	}

	*outcode = object_outcode;

	return ( object_outcode2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_BOUNDS * get_object_3d_bounding_box ( object_3d_index_numbers object )
{

	return ( &objects_3d_scene_database[object].bounding_box );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_BOUNDS * get_object_3d_bounding_box_without_lines ( object_3d_index_numbers object )
{

	return ( &objects_3d_scene_database[object].bounding_box2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_object_3d_radius ( object_3d_index_numbers object )
{

	return ( objects_3d_scene_database[object].radius );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

