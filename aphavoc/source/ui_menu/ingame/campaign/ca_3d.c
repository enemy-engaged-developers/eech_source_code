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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_campaign_screen_3d_scene (ui_object *obj, viewpoint *vp)
{
#ifndef OGRE_EE
	float
		x,
		y,
		width,
		height;

	int
		ix,
		iy,
		iwidth,
		iheight;

	display_3d_tints
		tint;

	day_segment_types
		day_segment_type;

	ASSERT (vp);

	ASSERT (obj);

	memcpy (&main_vp, vp, sizeof (viewpoint));

	x = get_ui_object_x (obj);
	y = get_ui_object_y (obj);

	width = get_ui_object_x_size (obj);
	height = get_ui_object_y_size (obj);

	convert_float_to_int ( x, &ix );
	convert_float_to_int ( y, &iy );

	convert_float_to_int ( width, &iwidth );
	convert_float_to_int ( height, &iheight );

	x = ix;
	y = iy;
	width = iwidth;
	height = iheight;

	day_segment_type = (day_segment_types) get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	if (day_segment_type == DAY_SEGMENT_TYPE_NIGHT)
	{
		tint = DISPLAY_3D_TINT_GREEN_VISUAL;
	}
	else
	{
		tint = DISPLAY_3D_TINT_CLEAR;
	}

	set_main_3d_params
	(
		tint,
		DISPLAY_3D_LIGHT_LEVEL_HIGH,
		DISPLAY_3D_NOISE_LEVEL_NONE,
		x,
		y,
		width,
		height,
		full_screen_width_view_angle,
		full_screen_height_view_angle
	);

	draw_application_ui_3d_scene ();
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_campaign_screen_3d_scene_to_texture (screen *scr, viewpoint *vp, float size)
{
#ifndef OGRE_EE
	float
		x1,
		y1,
		width,
		height;

	display_3d_tints
		tint;

	day_segment_types
		day_segment_type;

	ASSERT (vp);

	ASSERT (scr);

	memcpy (&main_vp, vp, sizeof (viewpoint));

	x1 = 0.0;

	y1 = 0.0;

	width = size;

	height = size;

	day_segment_type = (day_segment_types) get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	if (day_segment_type == DAY_SEGMENT_TYPE_NIGHT)
	{
		tint = DISPLAY_3D_TINT_GREEN_VISUAL;
	}
	else
	{
		tint = DISPLAY_3D_TINT_CLEAR;
	}

	set_main_3d_params
	(
		tint,
		DISPLAY_3D_LIGHT_LEVEL_HIGH,
		DISPLAY_3D_NOISE_LEVEL_NONE,
		x1,
		y1,
		width,
		height,
		full_screen_width_view_angle,
		full_screen_height_view_angle
	);

	draw_application_3d_scene_to_texture (scr, size);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_campaign_screen_entity_3d_scene (ui_object *obj, float distance, vec3d *direction)
{
	entity
		*en;

	vec3d
		*pos,
		temp;

	viewpoint
		vp;

	ASSERT (obj);

	ASSERT (direction);

	en = get_local_entity_safe_ptr (get_ui_object_item_number (obj));

	ASSERT (en);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	//
	// set camera position
	//

	vp.x = pos->x + (direction->x * distance);
	vp.y = pos->y + (direction->y * distance);
	vp.z = pos->z + (direction->z * distance);

	//
	// set camera attitude
	//

	temp.x = -(direction->x);
	temp.y = -(direction->y);
	temp.z = -(direction->z);

	get_matrix3x3_from_unit_vec3d (vp.attitude, &temp);

	draw_campaign_screen_3d_scene (obj, &vp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_campaign_screen_texture_to_object (screen *scr, ui_object *obj)
{
#ifndef OGRE_EE
	vertex
		quad[4];

	real_colour
		colour,
		specular;

	float
		x1,
		y1,
		x2,
		y2;

	ASSERT (scr);

	ASSERT (obj);

	x1 = get_ui_object_x (obj);

	y1 = get_ui_object_y (obj);

	x2 = x1 + get_ui_object_x_size (obj);

	y2 = y1 + get_ui_object_y_size (obj);

	{
		set_d3d_flat_shaded_textured_renderstate (scr);

		colour.red = 255;
		colour.green = 255;
		colour.blue = 255;
		colour.alpha = 255;

		specular.red = 0;
		specular.green = 0;
		specular.blue = 0;
		specular.alpha = 255;

		quad[0].i = x1;
		quad[0].j = y1;
		quad[0].z = 0.5;
		quad[0].q = 0.5;
		quad[0].u = 0;
		quad[0].v = 0;

		quad[1].i = x2;
		quad[1].j = y1;
		quad[1].z = 0.5;
		quad[1].q = 0.5;
		quad[1].u = 1;
		quad[1].v = 0;

		quad[2].i = x2;
		quad[2].j = y2;
		quad[2].z = 0.5;
		quad[2].q = 0.5;
		quad[2].u = 1;
		quad[2].v = 1;

		quad[3].i = x1;
		quad[3].j = y2;
		quad[3].z = 0.5;
		quad[3].q = 0.5;
		quad[3].u = 0;
		quad[3].v = 1;

		quad[0].next_vertex = &quad[1];
		quad[1].next_vertex = &quad[2];
		quad[2].next_vertex = &quad[3];
		quad[3].next_vertex = NULL;

		draw_wbuffered_flat_shaded_textured_polygon ( quad, colour, specular );
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


