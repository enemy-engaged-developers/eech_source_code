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

int
	object_3d_points_current_base,
	object_3d_object_current_base,
	object_3d_light_3d_current_base,
	object_3d_perform_lod_calculations = TRUE;

object_3d_info
	*current_object_3d_object_base,
	object_3d_object_base[512];							// Allow 512 objects in one object ( z-sorted only )

vec3d
	object_3d_scale;

int
	object_3d_approximation_level,
	current_3d_object_is_flat;

int
	specular_rendering_enabled = TRUE,
	textured_object_rendering_enabled = FALSE;

face_surface_description
	*current_object_3d_surface;

point_3d_plain_reference
	*current_object_3d_gouraud_list,
	*current_object_3d_face_normal_list;

point_3d_short_reference
	*current_object_3d_point_list;

object_3d_short_textured_point
	*current_object_3d_texture_list;

object_3d_transformed_point_normal
	*current_object_3d_transformed_normals;

int
	current_object_3d_specular,
	current_object_3d_outcode;

float
	current_object_3d_dissolve_factor,
	current_object_3d_diffuse_factor;

unsigned char
	current_object_3d_dissolve_value;

int
	current_object_3d_light_maps_enabled;

screen
	*object_3d_sprite_flare_texture,
	*current_object_3d_texture,
	*current_object_3d_luminosity_texture,
	*current_object_3d_reflection_texture_map;

static int
	current_object_3d_reflection_texture_map_index;

int
	current_object_3d_texture_u_address,
	current_object_3d_texture_v_address,
	current_object_3d_texture_filter,
	current_object_3d_texture_mipmap,
	current_object_3d_luminosity_texture_u_address,
	current_object_3d_luminosity_texture_v_address,
	current_object_3d_luminosity_texture_filter,
	current_object_3d_luminosity_texture_mipmap,
	current_object_3d_surface_point_index;

object_3d_short_textured_point
	*current_object_3d_surface_point_texture_list;

point_3d_plain_reference
	*current_object_3d_surface_point_list,
	*current_object_3d_surface_point_normal_list;

object_3d_face
	*current_object_3d_faces;

LPTLVERTEX
	current_object_3d_surface_vertices;

unsigned char
	current_object_3d_surface_vertices_used[256];

int
	object_3d_transparent_surface_index;

translucent_object_surface
	object_3d_translucent_surfaces[MAXIMUM_TRANLUCENT_SURFACES];

float
	object_3d_sin_heading[256],
	object_3d_cos_heading[256],
	object_3d_sin_pitch[256],
	object_3d_cos_pitch[256];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void pre_render_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene );

static void pre_render_object_faces ( int object_number );

float current_3d_object_face_facing ( void );

void process_object_faces_visible ( int object_number );

void transform_object_3d_points ( vertex *points, vec3d *object_relative_position, int number_of_points );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_object_3d_lookup_tables ( void )
{

	int
		count;

	for ( count = 0; count < 256; count++ )
	{

		float
			heading,
			pitch;

		heading = count;
		pitch = count;

		heading /= 256.0;
		pitch /= 256.0;

		heading *= PI2;
		pitch *= PI;

		heading -= PI;
		pitch -= ( PI/2 );

		object_3d_sin_heading[count] = sin ( heading );
		object_3d_cos_heading[count] = cos ( heading );

		object_3d_sin_pitch[count] = sin ( pitch );
		object_3d_cos_pitch[count] = cos ( pitch );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_object_3d_reflection_texture_map ( int texture_index )
{
	current_object_3d_reflection_texture_map_index = texture_index;
}

void apply_object_3d_reflection_texture_map ( void )
{
	current_object_3d_reflection_texture_map = get_system_texture_ptr ( current_object_3d_reflection_texture_map_index );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_3d_object_approximation_number ( object_3d_instance *obj )
{

	vec3d
		*pos;

	//
	// Calculate the object's position relative to the view.
	//

	pos = &obj->view_position;	//rel_vp.position;

	//
	// Get the object number
	//

	get_object_approximation_number ( obj->object_number, pos->z, &object_3d_approximation_level );

	return ( object_3d_approximation_level );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pre_render_3d_object ( object_3d_instance *obj )
{

	int
		object_number;

	object_3d_scene_database_entry
		*scene;

	//
	// Go through the object pre-loading the textures
	//

	//
	// Set the scene pointer
	//

	scene = &objects_3d_scene_database[obj->object_number];

	//
	// Set up the texture animations for this object.
	//

	initialise_object_texture_animations ( obj );

	//
	// Set up the object drawing global variables
	//

	current_object_3d_light_maps_enabled = obj->object_internal_lighting;

	//
	// Get the object number
	//

	object_number = get_object_approximation_number ( obj->object_number, obj->view_position.z, &object_3d_approximation_level );

	if ( objects_3d_data[object_number].number_of_points )
	{

		pre_render_object_faces ( object_number );
	}

	//
	// Recurse down any sub objects
	//

	if ( scene->number_of_sub_objects )
	{

		int
			count;

		for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
		{

			if (	( obj->sub_objects[count].visible_object ) &&
					( scene->sub_objects[count].sub_object_approximation_in_level <= object_3d_approximation_level ) &&
					( scene->sub_objects[count].sub_object_approximation_out_level >= object_3d_approximation_level ) )
			{

				pre_render_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count] );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pre_render_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene )
{

	int
		count,
		object_number;

	object_number = scene->index;

	if ( object_number )
	{

		pre_render_object_faces ( object_number );
	}

	//
	// Recurse down any sub objects
	//

	if ( scene->number_of_sub_objects )
	{

		for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
		{

			if (	( obj->sub_objects[count].visible_object ) &&
					( scene->sub_objects[count].sub_object_approximation_in_level <= object_3d_approximation_level ) &&
					( scene->sub_objects[count].sub_object_approximation_out_level >= object_3d_approximation_level ) )
			{

				pre_render_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count] );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pre_render_object_faces ( int object_number )
{

	int
		surfaces_left;

	surfaces_left = objects_3d_data[object_number].number_of_surfaces;

	current_object_3d_surface = objects_3d_data[object_number].surfaces;

	for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
	{

		if ( current_object_3d_surface->textured )
		{

			if ( current_object_3d_surface->texture_animation )
			{

				int
					frame;

				frame = texture_animations[current_object_3d_surface->texture_index].current_frame;

				current_object_3d_texture = system_textures[ texture_animations[current_object_3d_surface->texture_index].texture_indices[frame] ];
			}
			else
			{

				current_object_3d_texture = system_textures[current_object_3d_surface->texture_index];
			}

			current_object_3d_texture;

			if ( current_object_3d_surface->has_luminosity_texture )
			{

				if ( current_object_3d_surface->luminosity_texture_animation )
				{

					int
						frame;

					frame = texture_animations[current_object_3d_surface->luminosity_texture_index].current_frame;

					current_object_3d_luminosity_texture = system_textures[ texture_animations[current_object_3d_surface->luminosity_texture_index].texture_indices[frame] ];
				}
				else
				{

					current_object_3d_luminosity_texture = system_textures[current_object_3d_surface->luminosity_texture_index];
				}

				current_object_3d_luminosity_texture;
			}
		}

		current_object_3d_surface++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_object_bounding_box ( object_3d_instance *obj )
{

	vec3d
		*object_relative_position;

	object_3d_scene_database_entry
		*scene;

	real_colour
		white_colour,
		red_colour;


	//
	// Set the scene pointer
	//

	scene = &objects_3d_scene_database[obj->object_number];

	//
	// Get the object's position relative to the camera
	//

	object_relative_position = &obj->view_position;

	//
	// Set the main objects' scaling values
	//

	object_3d_scale.x = obj->relative_scale.x;
	object_3d_scale.y = obj->relative_scale.y;
	object_3d_scale.z = obj->relative_scale.z;

	//
	// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
	//

	rotation_3d[0][0] = ( obj->vp.xv.x * visual_3d_vp->xv.x + obj->vp.xv.y * visual_3d_vp->xv.y + obj->vp.xv.z * visual_3d_vp->xv.z );
	rotation_3d[0][1] = ( obj->vp.xv.x * visual_3d_vp->yv.x + obj->vp.xv.y * visual_3d_vp->yv.y + obj->vp.xv.z * visual_3d_vp->yv.z );
	rotation_3d[0][2] = ( obj->vp.xv.x * visual_3d_vp->zv.x + obj->vp.xv.y * visual_3d_vp->zv.y + obj->vp.xv.z * visual_3d_vp->zv.z );

	rotation_3d[1][0] = ( obj->vp.yv.x * visual_3d_vp->xv.x + obj->vp.yv.y * visual_3d_vp->xv.y + obj->vp.yv.z * visual_3d_vp->xv.z );
	rotation_3d[1][1] = ( obj->vp.yv.x * visual_3d_vp->yv.x + obj->vp.yv.y * visual_3d_vp->yv.y + obj->vp.yv.z * visual_3d_vp->yv.z );
	rotation_3d[1][2] = ( obj->vp.yv.x * visual_3d_vp->zv.x + obj->vp.yv.y * visual_3d_vp->zv.y + obj->vp.yv.z * visual_3d_vp->zv.z );

	rotation_3d[2][0] = ( obj->vp.zv.x * visual_3d_vp->xv.x + obj->vp.zv.y * visual_3d_vp->xv.y + obj->vp.zv.z * visual_3d_vp->xv.z );
	rotation_3d[2][1] = ( obj->vp.zv.x * visual_3d_vp->yv.x + obj->vp.zv.y * visual_3d_vp->yv.y + obj->vp.zv.z * visual_3d_vp->yv.z );
	rotation_3d[2][2] = ( obj->vp.zv.x * visual_3d_vp->zv.x + obj->vp.zv.y * visual_3d_vp->zv.y + obj->vp.zv.z * visual_3d_vp->zv.z );

	rotation_3d[0][0] *= object_3d_scale.x;
	rotation_3d[1][0] *= object_3d_scale.y;
	rotation_3d[2][0] *= object_3d_scale.z;

	rotation_3d[0][1] *= object_3d_scale.x;
	rotation_3d[1][1] *= object_3d_scale.y;
	rotation_3d[2][1] *= object_3d_scale.z;

	rotation_3d[0][2] *= object_3d_scale.x;
	rotation_3d[1][2] *= object_3d_scale.y;
	rotation_3d[2][2] *= object_3d_scale.z;

	white_colour.red = 255;
	white_colour.green = 255;
	white_colour.blue = 255;
	white_colour.alpha = 255;

	red_colour.red = 255;
	red_colour.green = 0;
	red_colour.blue = 0;
	red_colour.alpha = 255;

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture ( 0, NULL );
	set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_FLAT );


	{

		vertex
			points[8];

		points[0].x = scene->bounding_box2.xmin;
		points[0].y = scene->bounding_box2.ymin;
		points[0].z = scene->bounding_box2.zmin;

		points[1].x = scene->bounding_box2.xmax;
		points[1].y = scene->bounding_box2.ymin;
		points[1].z = scene->bounding_box2.zmin;

		points[3].x = scene->bounding_box2.xmin;
		points[3].y = scene->bounding_box2.ymax;
		points[3].z = scene->bounding_box2.zmin;

		points[2].x = scene->bounding_box2.xmax;
		points[2].y = scene->bounding_box2.ymax;
		points[2].z = scene->bounding_box2.zmin;

		points[4].x = scene->bounding_box2.xmin;
		points[4].y = scene->bounding_box2.ymin;
		points[4].z = scene->bounding_box2.zmax;

		points[5].x = scene->bounding_box2.xmax;
		points[5].y = scene->bounding_box2.ymin;
		points[5].z = scene->bounding_box2.zmax;

		points[7].x = scene->bounding_box2.xmin;
		points[7].y = scene->bounding_box2.ymax;
		points[7].z = scene->bounding_box2.zmax;

		points[6].x = scene->bounding_box2.xmax;
		points[6].y = scene->bounding_box2.ymax;
		points[6].z = scene->bounding_box2.zmax;

		transform_object_3d_points ( points, object_relative_position, 8 );

		//
		// Render the 12 lines
		//

		render_bounding_box_line ( points, 0, 1, white_colour );
		render_bounding_box_line ( points, 1, 2, white_colour );
		render_bounding_box_line ( points, 2, 3, white_colour );
		render_bounding_box_line ( points, 3, 0, white_colour );

		render_bounding_box_line ( points, 4, 5, white_colour );
		render_bounding_box_line ( points, 5, 6, white_colour );
		render_bounding_box_line ( points, 6, 7, white_colour );
		render_bounding_box_line ( points, 7, 4, white_colour );

		render_bounding_box_line ( points, 0, 4, white_colour );
		render_bounding_box_line ( points, 1, 5, white_colour );
		render_bounding_box_line ( points, 2, 6, white_colour );
		render_bounding_box_line ( points, 3, 7, white_colour );

		//
		// Render the other bounding box
		//

		points[0].x = scene->bounding_box.xmin;
		points[0].y = scene->bounding_box.ymin;
		points[0].z = scene->bounding_box.zmin;

		points[1].x = scene->bounding_box.xmax;
		points[1].y = scene->bounding_box.ymin;
		points[1].z = scene->bounding_box.zmin;

		points[3].x = scene->bounding_box.xmin;
		points[3].y = scene->bounding_box.ymax;
		points[3].z = scene->bounding_box.zmin;

		points[2].x = scene->bounding_box.xmax;
		points[2].y = scene->bounding_box.ymax;
		points[2].z = scene->bounding_box.zmin;

		points[4].x = scene->bounding_box.xmin;
		points[4].y = scene->bounding_box.ymin;
		points[4].z = scene->bounding_box.zmax;

		points[5].x = scene->bounding_box.xmax;
		points[5].y = scene->bounding_box.ymin;
		points[5].z = scene->bounding_box.zmax;

		points[7].x = scene->bounding_box.xmin;
		points[7].y = scene->bounding_box.ymax;
		points[7].z = scene->bounding_box.zmax;

		points[6].x = scene->bounding_box.xmax;
		points[6].y = scene->bounding_box.ymax;
		points[6].z = scene->bounding_box.zmax;

		transform_object_3d_points ( points, object_relative_position, 8 );

		//
		// Render the 12 lines
		//

		render_bounding_box_line ( points, 0, 1, red_colour );
		render_bounding_box_line ( points, 1, 2, red_colour );
		render_bounding_box_line ( points, 2, 3, red_colour );
		render_bounding_box_line ( points, 3, 0, red_colour );

		render_bounding_box_line ( points, 4, 5, red_colour );
		render_bounding_box_line ( points, 5, 6, red_colour );
		render_bounding_box_line ( points, 6, 7, red_colour );
		render_bounding_box_line ( points, 7, 4, red_colour );

		render_bounding_box_line ( points, 0, 4, red_colour );
		render_bounding_box_line ( points, 1, 5, red_colour );
		render_bounding_box_line ( points, 2, 6, red_colour );
		render_bounding_box_line ( points, 3, 7, red_colour );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_object_3d_points ( vertex *points, vec3d *object_relative_position, int number_of_points )
{

	int
		count;

	float
		pos_x,
		pos_y,
		pos_z,
		oxmax,
		oxmin,
		oymax,
		oymin;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	pos_x = object_relative_position->x * active_3d_environment->screen_i_scale;
	pos_y = object_relative_position->y * active_3d_environment->screen_j_scale;
	pos_z = object_relative_position->z;

	scaled_rotation[0][0] = rotation_3d[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = rotation_3d[0][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[0][2] = rotation_3d[0][2];

	scaled_rotation[1][0] = rotation_3d[1][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[1][1] = rotation_3d[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = rotation_3d[1][2];

	scaled_rotation[2][0] = rotation_3d[2][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[2][1] = rotation_3d[2][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[2][2] = rotation_3d[2][2];

	for ( count = 0; count < number_of_points; count++ )
	{

		float
			x,
			y,
			z;

		x = pos_x + points[count].x * scaled_rotation[0][0] + points[count].y * scaled_rotation[1][0] + points[count].z * scaled_rotation[2][0];
		y = pos_y + points[count].x * scaled_rotation[0][1] + points[count].y * scaled_rotation[1][1] + points[count].z * scaled_rotation[2][1];
		z = pos_z + points[count].x * scaled_rotation[0][2] + points[count].y * scaled_rotation[1][2] + points[count].z * scaled_rotation[2][2];

		points[count].x = x;
		points[count].y = y;
		points[count].z = z;

		if ( *( ( int * ) &points[count].z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			q = 1.0 / points[count].z;


			i = ( points[count].x * q );
			j = ( points[count].y * q );

			points[count].q = q;

			points[count].j = active_3d_environment->y_origin - j;
			points[count].i = active_3d_environment->x_origin + i;

			oxmax = active_viewport.x_max - points[count].i;
			oxmin = points[count].i - active_viewport.x_min;
			oymax = active_viewport.y_max - points[count].j;
			oymin = points[count].j - active_viewport.y_min;

			ixmax = *( ( unsigned int * ) &oxmax );
			ixmin = *( ( unsigned int * ) &oxmin );
			iymax = *( ( unsigned int * ) &oymax );
			iymin = *( ( unsigned int * ) &oymin );

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
			points[count].outcode = ( ixmin | ixmax );
		}
		else
		{

			points[count].outcode = CLIP_HITHER;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_bounding_box_line ( vertex *points, int pt1, int pt2, real_colour col )
{

	int
		outcode,
		outcode2;

	vertex
		*line;

	points[pt1].next_vertex = &points[pt2];
	points[pt2].next_vertex = NULL;

	outcode = points[pt1].outcode;
	outcode2 = points[pt1].outcode;

	outcode |= points[pt2].outcode;
	outcode2 &= points[pt2].outcode;

	line = &points[pt1];

	if ( outcode2 == 0 )
	{

		clip_3d_coord = 0;

		if ( outcode & CLIP_HITHER )
		{

			line = hither_clip_3d_polygon ( line, &outcode );

			if ( !line )
			{

				return;
			}
		}

		if ( outcode )
		{

			line = clip_3d_polygon ( line, outcode );

			if ( !line )
			{

				return;
			}
		}

		{

			draw_wbuffered_plain_line ( line, col );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_luminous_colour ( real_colour *colour )
{

	if (active_3d_environment->render_filter != RENDER_CLEAR)
	{


		float
			red,
			green,
			blue,
			alpha;

		int
			ired,
			igreen,
			iblue,
			ialpha;

		if ( current_object_3d_surface->additive )
		{

			float
				grey;

			red = current_object_3d_surface->red;
			green = current_object_3d_surface->green;
			blue = current_object_3d_surface->blue;

			grey = red * 0.3 + green * 0.59 + blue * 0.11;
			grey *= current_object_3d_dissolve_factor;

			asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.red ), &ired );
			asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.green ), &igreen );
			asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.blue ), &iblue );

			colour->red = ired;
			colour->green = igreen;
			colour->blue = iblue;
		}
		else
		{

			red = current_object_3d_surface->red;
			green = current_object_3d_surface->green;
			blue = current_object_3d_surface->blue;

			asm_convert_float_to_int ( ( red * ambient_3d_light.colour.red ), &ired );
			asm_convert_float_to_int ( ( green * ambient_3d_light.colour.green ), &igreen );
			asm_convert_float_to_int ( ( blue * ambient_3d_light.colour.blue ), &iblue );

			colour->red = ired;
			colour->green = igreen;
			colour->blue = iblue;

			if ( current_object_3d_surface->translucent )
			{

				alpha = current_object_3d_surface->alpha;

				asm_convert_float_to_int ( ( alpha * current_object_3d_dissolve_factor ), &ialpha );

				colour->alpha = ialpha;
			}
			else
			{

				colour->alpha = current_object_3d_dissolve_value;
			}
		}
	}
	else
	{

		if ( current_object_3d_surface->additive )
		{

			float
				red,
				green,
				blue;

			int
				ired,
				igreen,
				iblue;

			red = current_object_3d_surface->red;
			green = current_object_3d_surface->green;
			blue = current_object_3d_surface->blue;

			asm_convert_float_to_int ( ( red * current_object_3d_dissolve_factor ), &ired );
			asm_convert_float_to_int ( ( green * current_object_3d_dissolve_factor ), &igreen );
			asm_convert_float_to_int ( ( blue * current_object_3d_dissolve_factor ), &iblue );

			colour->red = ired;
			colour->green = igreen;
			colour->blue = iblue;
		}
		else
		{

			float
				alpha;

			int
				ialpha;

			colour->red = current_object_3d_surface->red;
			colour->green = current_object_3d_surface->green;
			colour->blue = current_object_3d_surface->blue;

			if ( current_object_3d_surface->translucent )
			{

				alpha = current_object_3d_surface->alpha;

				asm_convert_float_to_int ( ( alpha * current_object_3d_dissolve_factor ), &ialpha );

				colour->alpha = ialpha;
			}
			else
			{

				colour->alpha = current_object_3d_dissolve_value;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_lightmap_luminous_colour ( real_colour *colour )
{

	float
		red,
		green,
		blue;

	int
		ired,
		igreen,
		iblue;

	if (active_3d_environment->render_filter != RENDER_CLEAR )
	{

		float
			grey;

		red = current_object_3d_surface->red;
		green = current_object_3d_surface->green;
		blue = current_object_3d_surface->blue;

		grey = red * 0.3 + green * 0.59 + blue * 0.11;
		grey *= current_object_3d_dissolve_factor;

		asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.red ), &ired );
		asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.green ), &igreen );
		asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.blue ), &iblue );

		colour->red = ired;
		colour->green = igreen;
		colour->blue = iblue;
	}
	else
	{

		red = current_object_3d_surface->red;
		green = current_object_3d_surface->green;
		blue = current_object_3d_surface->blue;

		asm_convert_float_to_int ( ( red * current_object_3d_dissolve_factor ), &ired );
		asm_convert_float_to_int ( ( green * current_object_3d_dissolve_factor ), &igreen );
		asm_convert_float_to_int ( ( blue * current_object_3d_dissolve_factor ), &iblue );

		colour->red = ired;
		colour->green = igreen;
		colour->blue = iblue;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

real_colour calculate_line_colour ( struct OBJECT_3D_INFO *object_base )
{

	float
		red,
		green,
		blue,
		ndotp1,
		ndotn,
		ndotcamera,
		direction_factor;

	light_3d_source
		*this_light;

	vec3d
		point1,
		point2,
		line_normal,
		plane_normal;

	int
		pt1,
		pt2,
		ired,
		igreen,
		iblue;

	real_colour
		colour;

	//
	// Calculate a normal between the line & camera & light positions
	//

	pt1 = current_object_3d_surface_point_list[ current_object_3d_point_list[0].point ].point;
	pt2 = current_object_3d_surface_point_list[ current_object_3d_point_list[1].point ].point;

	point1.x = objects_3d_data[object_base->object_number].points[pt1].x;
	point1.y = objects_3d_data[object_base->object_number].points[pt1].y;
	point1.z = objects_3d_data[object_base->object_number].points[pt1].z;

	point2.x = objects_3d_data[object_base->object_number].points[pt2].x;
	point2.y = objects_3d_data[object_base->object_number].points[pt2].y;
	point2.z = objects_3d_data[object_base->object_number].points[pt2].z;

	point1.x = ( ( point2.x - point1.x ) / 2 ) + point1.x;
	point1.y = ( ( point2.y - point1.y ) / 2 ) + point1.y;
	point1.z = ( ( point2.z - point1.z ) / 2 ) + point1.z;

	plane_normal.x = point2.x - point1.x;
	plane_normal.y = point2.y - point1.y;
	plane_normal.z = point2.z - point1.z;

	ndotn = (	( plane_normal.x * plane_normal.x ) +
					( plane_normal.y * plane_normal.y ) +
					( plane_normal.z * plane_normal.z ) );

	ndotp1 = (	( point1.x * plane_normal.x ) +
					( point1.y * plane_normal.y ) +
					( point1.z * plane_normal.z ) );

	ndotcamera = (	( object_base->camera_position.x * plane_normal.x ) +
						( object_base->camera_position.y * plane_normal.y ) +
						( object_base->camera_position.z * plane_normal.z ) );

	direction_factor = ( ( ndotp1 - ndotcamera ) / ndotn );

	line_normal.x = object_base->camera_position.x + direction_factor * ( plane_normal.x );
	line_normal.y = object_base->camera_position.y + direction_factor * ( plane_normal.y );
	line_normal.z = object_base->camera_position.z + direction_factor * ( plane_normal.z );

	line_normal.x = line_normal.x - point1.x;
	line_normal.y = line_normal.y - point1.y;
	line_normal.z = line_normal.z - point1.z;

	normalise_any_3d_vector ( &line_normal );

	//
	// Illuminate the normal
	//

	this_light = object_base->lights;

	red = ambient_3d_light.colour.red;
	green = ambient_3d_light.colour.green;
	blue = ambient_3d_light.colour.blue;

	while ( this_light )
	{

		float
			intensity;

		intensity = ( ( line_normal.x * this_light->lx ) +
						  ( line_normal.y * this_light->ly ) +
						  ( line_normal.z * this_light->lz ) );

		if ( ( *( int * ) &intensity ) > ( *( int * ) &float_value_zero ) )
		{

			red += intensity * this_light->colour.red;
			green += intensity * this_light->colour.green;
			blue += intensity * this_light->colour.blue;
		}

		this_light = this_light->succ;
	}

	red = bound ( red, 0, 1 );
	green = bound ( green, 0, 1 );
	blue = bound ( blue, 0, 1 );

	red *= current_object_3d_surface->red;
	green *= current_object_3d_surface->green;
	blue *= current_object_3d_surface->blue;

	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	ired = ( *( int * ) &red ) - INTEGER_FLOAT_FACTOR;
	igreen = ( *( int * ) &green ) - INTEGER_FLOAT_FACTOR;
	iblue = ( *( int * ) &blue ) - INTEGER_FLOAT_FACTOR;

	colour.red = ired;
	colour.green = igreen;
	colour.blue = iblue;
	colour.alpha = 0;

	return ( colour );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_line_normal ( struct OBJECT_3D_INFO *object_base, vec3d *result_normal )
{

	float
		ndotp1,
		ndotn,
		ndotcamera,
		direction_factor;

	vec3d
		point1,
		point2,
		line_normal,
		plane_normal;

	int
		pt1,
		pt2;

	//
	// Calculate a normal between the line & camera & light positions
	//

	pt1 = current_object_3d_surface_point_list[ current_object_3d_point_list[0].point ].point;
	pt2 = current_object_3d_surface_point_list[ current_object_3d_point_list[1].point ].point;

	point1.x = objects_3d_data[object_base->object_number].points[pt1].x;
	point1.y = objects_3d_data[object_base->object_number].points[pt1].y;
	point1.z = objects_3d_data[object_base->object_number].points[pt1].z;

	point2.x = objects_3d_data[object_base->object_number].points[pt2].x;
	point2.y = objects_3d_data[object_base->object_number].points[pt2].y;
	point2.z = objects_3d_data[object_base->object_number].points[pt2].z;

	point1.x = ( ( point2.x - point1.x ) / 2 ) + point1.x;
	point1.y = ( ( point2.y - point1.y ) / 2 ) + point1.y;
	point1.z = ( ( point2.z - point1.z ) / 2 ) + point1.z;

	plane_normal.x = point2.x - point1.x;
	plane_normal.y = point2.y - point1.y;
	plane_normal.z = point2.z - point1.z;

	ndotn = (	( plane_normal.x * plane_normal.x ) +
					( plane_normal.y * plane_normal.y ) +
					( plane_normal.z * plane_normal.z ) );

	ndotp1 = (	( point1.x * plane_normal.x ) +
					( point1.y * plane_normal.y ) +
					( point1.z * plane_normal.z ) );

	ndotcamera = (	( object_base->camera_position.x * plane_normal.x ) +
						( object_base->camera_position.y * plane_normal.y ) +
						( object_base->camera_position.z * plane_normal.z ) );

	direction_factor = ( ( ndotp1 - ndotcamera ) / ndotn );

	line_normal.x = object_base->camera_position.x + direction_factor * ( plane_normal.x );
	line_normal.y = object_base->camera_position.y + direction_factor * ( plane_normal.y );
	line_normal.z = object_base->camera_position.z + direction_factor * ( plane_normal.z );

	result_normal->x = line_normal.x - point1.x;
	result_normal->y = line_normal.y - point1.y;
	result_normal->z = line_normal.z - point1.z;

	normalise_any_3d_vector ( result_normal );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_environment_coordinates ( int object_index, object_short_3d_point *point, vec3d *normal, vec3d *camera_position, matrix3x3 attitude, float *u, float*v )
{

	vec3d
		reflected_ray,
		ray;

	float
		xmax,
		ymax,
		zmax,
		x,
		y,
		z,
		denominator,
		ndotr;

	xmax = max ( fabs ( objects_3d_data[object_index].bounding_box.xmin ), fabs ( objects_3d_data[object_index].bounding_box.xmax ) );
	ymax = max ( fabs ( objects_3d_data[object_index].bounding_box.ymin ), fabs ( objects_3d_data[object_index].bounding_box.ymax ) );
	zmax = max ( fabs ( objects_3d_data[object_index].bounding_box.zmin ), fabs ( objects_3d_data[object_index].bounding_box.zmax ) );
	xmax /= 32767.0;
	ymax /= 32767.0;
	zmax /= 32767.0;

	x = ( float ) point->x * xmax;
	y = ( float ) point->y * ymax;
	z = ( float ) point->z * zmax;

	ray.x = - camera_position->x + x;
	ray.y = - camera_position->y + y;
	ray.z = - camera_position->z + z;

//	normalise_any_3d_vector ( &ray );

	//
	// Reflection = 2.0 * ( Normal . Ray ) * Normal - Ray
	//

	ndotr = ( ray.x * normal->x + ray.y * normal->y + ray.z * normal->z ) * 2.0;

	reflected_ray.x = ndotr * normal->x - ray.x;
	reflected_ray.y = ndotr * normal->y - ray.y;
	reflected_ray.z = ndotr * normal->z - ray.z;

	//
	// Rotate the reflected ray back into world coordinates
	//

	multiply_matrix3x3_vec3d ( &ray, attitude, &reflected_ray );

	normalise_any_3d_vector ( &ray );

	denominator = get_inverse_square_root ( ray.z + 1 );
	denominator *= ( 1 / ( 1.4142135623730904880 * 2 ) );

	*u = 0.5 + ( ray.x * denominator );
	*v = 0.5 + ( ray.y * denominator );

//	*u = 0.5 + ( ray.x * denominator );
//	*v = 0.5 + ( ray.y * denominator );

	//
	// Test code
	//

//	ray.x = camera_position->x - point->x;
//	ray.y = camera_position->y - point->y;
//	ray.z = camera_position->z - point->z;

//	multiply_matrix3x3_vec3d ( normal, attitude, &reflected_ray );

//	normalise_any_3d_vector ( &reflected_ray );

//	*u = ( 0.5 + 0.5 * reflected_ray.x ) / point->z;
//	*u = ( 0.5 + 0.5 * reflected_ray.y ) / point->z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_new_environment_coordinates ( int point_index, vec3d *normal, matrix3x3 attitude, float *texture_u, float *texture_v )
{

	float
		p,
		ndotu;

	vec3d
		u,
		n,
		r;

	u.x = transformed_3d_3d_points[point_index].x;
	u.y = transformed_3d_3d_points[point_index].y;
	u.z = transformed_3d_2d_points[point_index].z;

	normalise_any_3d_vector ( &u );

	n.x = normal->x * object_to_eye_attitude[0][0] + normal->x * object_to_eye_attitude[0][1] + normal->x * object_to_eye_attitude[0][2];
	n.y = normal->y * object_to_eye_attitude[1][0] + normal->y * object_to_eye_attitude[1][1] + normal->y * object_to_eye_attitude[1][2];
	n.z = normal->z * object_to_eye_attitude[2][0] + normal->z * object_to_eye_attitude[2][1] + normal->z * object_to_eye_attitude[2][2];

	normalise_any_3d_vector ( &n );

	ndotu = 2.0 * ( n.x * u.x + n.y * u.y + n.z * u.z );

	r.x = u.x - ( ndotu * n.x );
	r.y = u.y - ( ndotu * n.y );
	r.z = u.z - ( ndotu * n.z );
//	r.x = ( ndotu * n.x ) - u.x;
//	r.y = ( ndotu * n.y ) - u.y;
//	r.z = ( ndotu * n.z ) - u.z;

	p = ( r.x * r.x ) + ( r.y * r.y ) + ( ( r.z + 1 ) * ( r.z + 1 ) );
	p = sqrt ( p );

	*texture_v = 0.5 + ( r.x / ( 2.0 * p ) );
	*texture_u = 0.5 + ( r.y / ( 2.0 * p ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_textured_surface_face_colour ( real_colour *colour, real_colour *specular_colour )
{

	colour->alpha = current_object_3d_dissolve_value;

	specular_colour->colour = d3d_fog_intensity;

	if ( current_object_3d_surface->luminous )
	{

		calculate_luminous_colour ( colour );
	}
	else
	{

		//
		// Look up the colour of the face normal
		//

		colour->colour = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].colour;

		if ( current_object_3d_specular )
		{

			int
				ispecular;

			float
				specular;

			specular = current_object_3d_surface->specularity * current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].specular;

			asm_convert_float_to_int ( specular, &ispecular );

			specular_colour->red = ispecular;
			specular_colour->green = ispecular;
			specular_colour->blue = ispecular;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_surface_face_colour ( real_colour *colour, real_colour *specular_colour )
{

	if ( current_object_3d_surface->luminous )
	{

		calculate_luminous_colour ( colour );

		specular_colour->colour = d3d_fog_intensity;
	}
	else
	{

		float
			red,
			green,
			blue,
			specular;

		int
			ir,
			ig,
			ib,
			ispecular;

		//
		// Look up the colour of the face normal
		//

		red = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].r;
		green = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].g;
		blue = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].b;
		specular = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].specular;

		red /= 255.0;
		green /= 255.0;
		blue /= 255.0;

		asm_convert_float_to_int ( ( red * current_object_3d_surface->red ), &ir );
		asm_convert_float_to_int ( ( green * current_object_3d_surface->green ), &ig );
		asm_convert_float_to_int ( ( blue * current_object_3d_surface->blue ), &ib );
		asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );

		colour->red = ir;
		colour->green = ig;
		colour->blue = ib;

		specular_colour->colour = d3d_fog_intensity;
		specular_colour->red = ispecular;
		specular_colour->green = ispecular;
		specular_colour->blue = ispecular;
	}

	{

		int
			imixed_dissolve;

		asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &imixed_dissolve );

		colour->alpha = imixed_dissolve;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

light_3d_source *generate_relative_lights ( viewpoint *vp, vec3d *object_unit_pos, light_3d_source *lights )
{

	light_3d_source
		*light_ptr,
		*prev_light,
		*this_light,
		*light;

	light_ptr = lights;

	prev_light = NULL;

	light = NULL;

	if ( light_ptr )
	{

		int
			light_count;

		light_count = 0;

		light = &light_3d_array[object_3d_light_3d_current_base];

		while ( light_ptr )
		{

			float
				lx,
				ly,
				lz;

			light_count++;

			if ( light_ptr->type == LIGHT_3D_TYPE_POINT )
			{

				vec3d
					vector;

				float
					distance;

				//
				// Work out the distance from object to light source
				//

				vector.x = light_ptr->light_position.x - vp->x;
				vector.y = light_ptr->light_position.y - vp->y;
				vector.z = light_ptr->light_position.z - vp->z;

				lx = vector.x * vector.x;
				ly = vector.y * vector.y;
				lz = vector.z * vector.z;

				distance = ( lx + ly + lz );

				if ( distance < light_ptr->radius )
				{

					distance = 1 - ( distance / light_ptr->radius );

					this_light = &light_3d_array[object_3d_light_3d_current_base];

					object_3d_light_3d_current_base++;

					if ( prev_light )
					{

						prev_light->succ = this_light;
					}

					this_light->pred = prev_light;
					this_light->succ = NULL;

					this_light->type = light_ptr->type;

					this_light->colour.red = light_ptr->colour.red * distance;
					this_light->colour.green = light_ptr->colour.green * distance;
					this_light->colour.blue = light_ptr->colour.blue * distance;
					this_light->intensity = this_light->colour.red * 0.30 + this_light->colour.green * 0.59 + this_light->colour.blue * 0.11;

					normalise_any_3d_vector ( &vector );

					lx = ( vector.x * vp->attitude[0][0] );
					lx += ( vector.y * vp->attitude[0][1] );
					lx += ( vector.z * vp->attitude[0][2] );

					ly = ( vector.x * vp->attitude[1][0] );
					ly += ( vector.y * vp->attitude[1][1] );
					ly += ( vector.z * vp->attitude[1][2] );

					lz = ( vector.x * vp->attitude[2][0] );
					lz += ( vector.y * vp->attitude[2][1] );
					lz += ( vector.z * vp->attitude[2][2] );

					this_light->lx = lx;
					this_light->ly = ly;
					this_light->lz = lz;

					prev_light = this_light;
				}
			}
			else
			{

				this_light = &light_3d_array[object_3d_light_3d_current_base];

				object_3d_light_3d_current_base++;

				if ( prev_light )
				{

					prev_light->succ = this_light;
				}

				this_light->pred = prev_light;
				this_light->succ = NULL;

				this_light->type = light_ptr->type;

				this_light->colour.red = light_ptr->colour.red;
				this_light->colour.green = light_ptr->colour.green;
				this_light->colour.blue = light_ptr->colour.blue;
				this_light->intensity = this_light->intensity;	//this_light->colour.red * 0.30 + this_light->colour.green * 0.59 + this_light->colour.blue * 0.11;

				lx = ( light_ptr->lx * vp->attitude[0][0] );
				lx +=  ( light_ptr->ly * vp->attitude[0][1] );
				lx += ( light_ptr->lz * vp->attitude[0][2] );

				ly = ( light_ptr->lx * vp->attitude[1][0] );
				ly += ( light_ptr->ly * vp->attitude[1][1] );
				ly += ( light_ptr->lz * vp->attitude[1][2] );


				lz = ( light_ptr->lx * vp->attitude[2][0] );
				lz += ( light_ptr->ly * vp->attitude[2][1] );
				lz += ( light_ptr->lz * vp->attitude[2][2] );

				this_light->lx = lx;
				this_light->ly = ly;
				this_light->lz = lz;

				//
				// Generate a highlight vector
				//

				this_light->highlight_vector.x = ( lx - object_unit_pos->x );
				this_light->highlight_vector.y = ( ly - object_unit_pos->y );
				this_light->highlight_vector.z = ( lz - object_unit_pos->z );

				normalise_any_3d_vector ( &this_light->highlight_vector );

				prev_light = this_light;
			}

			light_ptr = light_ptr->succ;
		}
	}

	return ( light );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_object_3d_point_normal ( object_3d_heading_pitch_normal *normal, vec3d *result )
{

	float
		sin_heading,
		cos_heading,
		sin_pitch,
		cos_pitch;

	sin_heading = object_3d_sin_heading[normal->heading];
	cos_heading = object_3d_cos_heading[normal->heading];

	sin_pitch = object_3d_sin_pitch[normal->pitch];
	cos_pitch = object_3d_cos_pitch[normal->pitch];
/*
		object_3d_sin_heading = sin ( heading );
		object_3d_cos_heading = cos ( heading );

		object_3d_sin_pitch = sin ( pitch );
		object_3d_cos_pitch = cos ( pitch );
	heading = normal->heading;
	pitch = normal->pitch;

	heading /= 256.0;
	pitch /= 256.0;

	heading *= PI2;
	pitch *= PI;

	heading -= PI;
	pitch -= ( PI/2 );
*/
	result->x = cos_pitch * sin_heading;
	result->y = sin_pitch;
	result->z = cos_pitch * cos_heading;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


