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
//
// OBJECTS.C
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"cars.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static	face_list						face_order_list[MAX_FACES];

static	object_drawing_list			object_order_list[MAX_OBJECTS];

static	int								face_order_index;

static	int								object_order_index;

static	int								points_current_base;

static	int								object_current_base;

int											number_of_terrain_faces;

static	object_info						object_base[256];							// Allow 256 objects in one object ( overkill )

static	face_list					*	last_insert_point;

static	object_drawing_list		*	last_object_insert_point;

static	face_list					*	list;

static	object_drawing_list		*	object_list;

int											face_checks;

static	int								this_object;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static	void	insert_face ( face * this_face, int z, object_info * this_object_info );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

view_point
	*visual_vp;

#ifdef FLOAT_LIBRARY
vec3d
	light_source = { 0, 0, 1.0 };
#else
vec3d
	light_source = { 0, 0, ONE };
#endif

vec3d				object_pos;

vec4d			*	object_points;

vec3d			*	pos;

vec3d				normal_pos;

object_info	*	global_object_info;

int
	shadow_object = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	draw_horizon ( view_point * vp )
{
	visual_vp = vp;

	horizon->vp.x = visual_vp->x;
	horizon->vp.y = visual_vp->y;
	horizon->vp.z = visual_vp->z;

	horizon->rel_vp.x = 0;
	horizon->rel_vp.y = 0;
	horizon->rel_vp.z = 0;

	draw_object ( horizon );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_objects (view_point *vp)
{
	object_drawing_list
		* object_order;

	object_order = object_list;

	visual_vp = vp;

	number_of_terrain_faces = 0;

	while (object_order)
	{
		switch ( object_order->type )
		{
			case	OBJECT_DRAW_TYPE_OBJECT:
					switch ( object_order->object->object_number )
					{
						case	ROCKET:
						case	F16:
						case	A10:
						case	APACHE:
						case	C130:
						case	MIG27:
						case	MIG29:
								draw_object_shadow ( object_order->object );
								break;
						default:
								break;
					}

					draw_object ( object_order->object );
					break;

			case	OBJECT_DRAW_TYPE_EXPLOSION:
					draw_explosion ( object_order->explosion );
					break;

			case	OBJECT_DRAW_TYPE_TERRAIN:
					number_of_terrain_faces ++;
					draw_terrain_face ( object_order );
					break;

			default:
					debug_fatal ( "Unknown object type in draw_3d_objects" );
					break;
		}

		object_order = object_order->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	draw_object ( object_instance * object )
{
	int
		obj,
		count,
		temp,
		num_faces,
		intensity,
		reflectance,
		last_z,
		rejected;

	crt_coords
		*poly;

	face
		*faces;

	face_list
		*face_order;

	vec3d
		light,
		highlight,
		view,
		rel_pos,
		*normal;

	point_reference
		*point_list;

	REAL
		tmp;

	float
		fintensity;

	double
		timing;

	object_info			*	this_object_info;


	fintensity = 0;

	rejected = 0;
	timing = 0;

	if ( check_key ( KEY_T ) )
	{
		debug_message ( "Start object %d", object->object_number );
	}

	//
	//	Quick hack to get rid of any objects behind the viewpoint. This should be removed when the object
	//		sorting is in place.
	//

	//
	// Set up the object drawing global variables
	//

	points_current_base = 0;
	object_current_base = 0;

	//
	// Get the object number
	//

	obj = object->object_number;

	this_object = obj;

	//
	// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
	//

#ifdef FLOAT_LIBRARY

	rotation.matrix[0][0] = ( object->vp.xv.x * visual_vp->xv.x + object->vp.xv.y * visual_vp->xv.y + object->vp.xv.z * visual_vp->xv.z );
	rotation.matrix[1][0] = ( object->vp.xv.x * visual_vp->yv.x + object->vp.xv.y * visual_vp->yv.y + object->vp.xv.z * visual_vp->yv.z );
	rotation.matrix[2][0] = ( object->vp.xv.x * visual_vp->zv.x + object->vp.xv.y * visual_vp->zv.y + object->vp.xv.z * visual_vp->zv.z );

	rotation.matrix[0][1] = ( object->vp.yv.x * visual_vp->xv.x + object->vp.yv.y * visual_vp->xv.y + object->vp.yv.z * visual_vp->xv.z );
	rotation.matrix[1][1] = ( object->vp.yv.x * visual_vp->yv.x + object->vp.yv.y * visual_vp->yv.y + object->vp.yv.z * visual_vp->yv.z );
	rotation.matrix[2][1] = ( object->vp.yv.x * visual_vp->zv.x + object->vp.yv.y * visual_vp->zv.y + object->vp.yv.z * visual_vp->zv.z );

	rotation.matrix[0][2] = ( object->vp.zv.x * visual_vp->xv.x + object->vp.zv.y * visual_vp->xv.y + object->vp.zv.z * visual_vp->xv.z );
	rotation.matrix[1][2] = ( object->vp.zv.x * visual_vp->yv.x + object->vp.zv.y * visual_vp->yv.y + object->vp.zv.z * visual_vp->yv.z );
	rotation.matrix[2][2] = ( object->vp.zv.x * visual_vp->zv.x + object->vp.zv.y * visual_vp->zv.y + object->vp.zv.z * visual_vp->zv.z );

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	object_pos.x = (	( visual_vp->x - object->vp.x ) * object->vp.xv.x + ( visual_vp->y - object->vp.y ) *  object->vp.xv.y +  ( visual_vp->z - object->vp.z ) *  object->vp.xv.z );
	object_pos.y = (	( visual_vp->x - object->vp.x ) * object->vp.yv.x + ( visual_vp->y - object->vp.y ) *  object->vp.yv.y +  ( visual_vp->z - object->vp.z ) *  object->vp.yv.z );
	object_pos.z = (	( visual_vp->x - object->vp.x ) * object->vp.zv.x + ( visual_vp->y - object->vp.y ) *  object->vp.zv.y +  ( visual_vp->z - object->vp.z ) *  object->vp.zv.z );

	//
	// Rotate the light source vector to be relative to the object.
	//

	light.x = ( light_source.x * object->vp.attitude[0][0] + light_source.y * object->vp.attitude[0][1] + light_source.z * object->vp.attitude[0][2] );
	light.y = ( light_source.x * object->vp.attitude[1][0] + light_source.y * object->vp.attitude[1][1] + light_source.z * object->vp.attitude[1][2] );
	light.z = ( light_source.x * object->vp.attitude[2][0] + light_source.y * object->vp.attitude[2][1] + light_source.z * object->vp.attitude[2][2] );

	//
	// Generate a unit vector in world coordinates from the user to the object
	//

	rel_pos.x = visual_vp->x - object->vp.x;
	rel_pos.y = visual_vp->y - object->vp.y;
	rel_pos.z = visual_vp->z - object->vp.z;

	normalise_vector ( & rel_pos );

	view.x = ( rel_pos.x * object->vp.attitude[0][0] + rel_pos.y * object->vp.attitude[0][1] + rel_pos.z * object->vp.attitude[0][2] );
	view.y = ( rel_pos.x * object->vp.attitude[1][0] + rel_pos.y * object->vp.attitude[1][1] + rel_pos.z * object->vp.attitude[1][2] );
	view.z = ( rel_pos.x * object->vp.attitude[2][0] + rel_pos.y * object->vp.attitude[2][1] + rel_pos.z * object->vp.attitude[2][2] );

	//
	// Generate a highlight vector which is half way between the view vector, and the light vector
	//

	highlight.x = ( light.x - view.x );
	highlight.y = ( light.y - view.y );
	highlight.z = ( light.z - view.z );

	normalise_vector ( & highlight );

#else
	rotation.matrix[0][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->xv.x, object->vp.xv.y, visual_vp->xv.y, object->vp.xv.z, visual_vp->xv.z );
	rotation.matrix[1][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->yv.x, object->vp.xv.y, visual_vp->yv.y, object->vp.xv.z, visual_vp->yv.z );
	rotation.matrix[2][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->zv.x, object->vp.xv.y, visual_vp->zv.y, object->vp.xv.z, visual_vp->zv.z );

	rotation.matrix[0][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->xv.x, object->vp.yv.y, visual_vp->xv.y, object->vp.yv.z, visual_vp->xv.z );
	rotation.matrix[1][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->yv.x, object->vp.yv.y, visual_vp->yv.y, object->vp.yv.z, visual_vp->yv.z );
	rotation.matrix[2][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->zv.x, object->vp.yv.y, visual_vp->zv.y, object->vp.yv.z, visual_vp->zv.z );

	rotation.matrix[0][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->xv.x, object->vp.zv.y, visual_vp->xv.y, object->vp.zv.z, visual_vp->xv.z );
	rotation.matrix[1][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->yv.x, object->vp.zv.y, visual_vp->yv.y, object->vp.zv.z, visual_vp->yv.z );
	rotation.matrix[2][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->zv.x, object->vp.zv.y, visual_vp->zv.y, object->vp.zv.z, visual_vp->zv.z );

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	object_pos.x = imuladdf_ab_cd_ef (	( visual_vp->x - object->vp.x ), object->vp.xv.x, ( visual_vp->y - object->vp.y ), object->vp.xv.y, ( visual_vp->z - object->vp.z ), object->vp.xv.z );
	object_pos.y = imuladdf_ab_cd_ef (	( visual_vp->x - object->vp.x ), object->vp.yv.x, ( visual_vp->y - object->vp.y ), object->vp.yv.y, ( visual_vp->z - object->vp.z ), object->vp.yv.z );
	object_pos.z = imuladdf_ab_cd_ef (	( visual_vp->x - object->vp.x ), object->vp.zv.x, ( visual_vp->y - object->vp.y ), object->vp.zv.y, ( visual_vp->z - object->vp.z ), object->vp.zv.z );

	//
	// Rotate the light source vector to be relative to the object.
	//

	light.x = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[0][0], light_source.y, object->vp.attitude[0][1], light_source.z, object->vp.attitude[0][2] );
	light.y = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[1][0], light_source.y, object->vp.attitude[1][1], light_source.z, object->vp.attitude[1][2] );
	light.z = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[2][0], light_source.y, object->vp.attitude[2][1], light_source.z, object->vp.attitude[2][2] );

	//
	// Generate a unit vector in world coordinates from the user to the object
	//

	rel_pos.x = visual_vp->x - object->vp.x;
	rel_pos.y = visual_vp->y - object->vp.y;
	rel_pos.z = visual_vp->z - object->vp.z;

	normalise_vector ( & rel_pos );

	view.x = imuladdf_ab_cd_ef ( rel_pos.x, object->vp.attitude[0][0], rel_pos.y, object->vp.attitude[0][1], rel_pos.z, object->vp.attitude[0][2] );
	view.y = imuladdf_ab_cd_ef ( rel_pos.x, object->vp.attitude[1][0], rel_pos.y, object->vp.attitude[1][1], rel_pos.z, object->vp.attitude[1][2] );
	view.z = imuladdf_ab_cd_ef ( rel_pos.x, object->vp.attitude[2][0], rel_pos.y, object->vp.attitude[2][1], rel_pos.z, object->vp.attitude[2][2] );

	//
	// Generate a highlight vector which is half way between the view vector, and the light vector
	//

	highlight.x = ( light.x - view.x );
	highlight.y = ( light.y - view.y );
	highlight.z = ( light.z - view.z );

	normalise_vector ( & highlight );

#endif

	//
	// Calculate the object's position relative to the view.
	//

	pos = & object->rel_vp.position;

	//
	//	Set up this objects' object info structure
	//

	object_base[object_current_base].ob = object;
	object_base[object_current_base].light.x = light.x;
	object_base[object_current_base].light.y = light.y;
	object_base[object_current_base].light.z = light.z;
	object_base[object_current_base].points_base = points_current_base;

	this_object_info = & object_base[object_current_base];
	global_object_info = this_object_info;

	//
	// Set up the face sorting variables
	//

	num_faces = global_objects[obj].number_of_faces;

	list = NULL;

	last_insert_point = NULL;

	face_order_index = 0;

	//
	// Insert this objects' faces into the sorted list.
	//

	faces = global_objects[obj].faces;

	object_points = global_objects[obj].points;

#if 0

	process_face_tree ( faces );

#else

	for ( count=0; count<num_faces; count++ )
	{
		normal_pos.x = faces[count].dpoint.x - object_pos.x;
		normal_pos.y = faces[count].dpoint.y - object_pos.y;
		normal_pos.z = faces[count].dpoint.z - object_pos.z;

#ifdef FLOAT_LIBRARY
		if ( (	( normal_pos.x * faces[count].normal_data.x ) +
					( normal_pos.y * faces[count].normal_data.y ) +
					( normal_pos.z * faces[count].normal_data.z ) ) > 0 )
#else
		if ( backface_check ( & normal_pos, & faces[count].normal_data ) > 0 )
#endif
		{
			point_list = faces[count].list;
			object_points [ point_list->point ].needed = TRUE; point_list++;
			object_points [ point_list->point ].needed = TRUE; point_list++;
			object_points [ point_list->point ].needed = TRUE; point_list++;

			for ( temp = 3; temp < faces[count].num_points; temp ++ )
			{
				object_points[ point_list->point ].needed = TRUE;
				point_list++;
			}

#ifdef FLOAT_LIBRARY

			tmp = (	( faces[count].dpoint.x * rotation.a02 ) +
						( faces[count].dpoint.y * rotation.a12 ) +
						( faces[count].dpoint.z * rotation.a22 ) + pos->z + FLOAT_METRES_FACTOR );
	
			temp = * ( (int*) &tmp );
			temp -= INTEGER_METRES_FACTOR;

#else

			temp = imulfastf ( faces[count].dpoint.x, rotation.a02 );
			temp += imulfastf ( faces[count].dpoint.y, rotation.a12 );
			temp += imulfastf ( faces[count].dpoint.z, rotation.a22 );
			temp += pos->z;

#endif

			insert_face ( & faces[count], temp, this_object_info );
		}
	}

#endif

	//
	// Transform the object's shape data
	//

	transform_3d_object ( & global_objects[obj], pos, & light, & highlight, points_current_base);

	//
	// Adjust the memory pointers for any sub objects
	//

	object_current_base ++;
	points_current_base += global_objects[obj].number_of_points;

	//
	// Recurse down any sub objects
	//

	if ( object->number_of_sub_objects != 0 )
	{
		for ( count=0; count<object->number_of_sub_objects; count++ )
		{
			draw_sub_object ( object->sub_objects[count], this_object_info, pos );
		}
	}

	//
	//	Ok, now we're ready to draw the actual faces.
	//

	switch ( active_screen->type )
	{
		case	8:
		{
			face_order = list;

			if ( face_order )
			{
				last_z = face_order->z;
			}
		
			while ( face_order )
			{
				clip_coord = 0;

				if ( face_order->face->flags & FACE_SHITTY )
				{
					face_order->face->flags = FACE_SHITTY | FACE_NOT_SHADED;
					face_order->face->face_colour = 64;
				}

				if ( face_order->face->flags & FACE_AFFINE_TEXTURED )
				{
					if ( global_objects[obj].light_sourced )
					{
						poly = construct_affine_textured_face (	face_order->face->num_points,
																				face_order->face->list,
																				face_order->object_base->points_base );
//						poly = construct_perspective_textured_face (	face_order->face->num_points,
//																					face_order->face->list,
//																					face_order->object_base->points_base );
//						face_order->face->flags |= FACE_PERSPECTIVE_TEXTURED;
					}
					else
					{
						poly = construct_affine_textured_face (	face_order->face->num_points,
																				face_order->face->list,
																				face_order->object_base->points_base );
					}
				}
				else
				{
					poly = construct_face (	face_order->face->num_points,
													face_order->face->list,
													face_order->object_base->points_base );
				}
		
				if ( ( poly ) && ( poly->polygon_outcode & CLIP_FRONT ) )
				{
					poly = near_clip_face ( poly, face_order->face->flags );
				}
		
//				if ( ( poly ) &&  ( get_cyclic_result ( poly->i, poly->j,
//													poly->next_vertex->i, poly->next_vertex->j,
//													poly->next_vertex->next_vertex->i, poly->next_vertex->next_vertex->j ) < 0 ) )
//				{
//					poly = NULL;
//				}
		
				if ( ( poly ) && ( poly->polygon_outcode ) )
				{
					poly = clip_polygon ( poly, face_order->face->flags );
				}
		
				if ( poly )
				{
					if ( face_order->face->flags & FACE_AFFINE_TEXTURED )
					{
						if ( global_objects[obj].light_sourced )
						{
#ifdef FLOAT_LIBRARY

							fintensity = (	( face_order->face->normal_data.x * face_order->object_base->light.x ) +
												( face_order->face->normal_data.y * face_order->object_base->light.y ) +
												( face_order->face->normal_data.z * face_order->object_base->light.z ) );
				
							fintensity += FLOAT_WHOLE_INTENSITY_FACTOR;
				
							intensity = * ( ( int * ) & fintensity );
				
							intensity -= INTEGER_WHOLE_INTENSITY_FACTOR;
				
							if ( intensity < 0 )
							{
								intensity = 0;
							}
#else
							intensity = imuladdf_ab_cd_ef (	face_order->face->normal_data.x, face_order->object_base->light.x,
																		face_order->face->normal_data.y, face_order->object_base->light.y,
																		face_order->face->normal_data.z, face_order->object_base->light.z );
							if ( intensity < 0 )
							{
								intensity = 0;
							}
			
							intensity = imulf ( intensity, 255 );
#endif
		

							intensity = 255;	// DEBUG

//							draw_perspective_textured_polygon ( poly, face_order->face->texture );
							draw_textured_shaded_polygon ( poly, face_order->face->texture, intensity );

//							draw_textured_perspective_polygon ( poly, face_order->face->texture );
						}
						else
						{
							draw_textured_polygon ( poly, face_order->face->texture );
						}
					}
					else
					{
						if ( global_objects[obj].light_sourced )
						{
							if ( face_order->face->flags & FACE_GOURAUD_SHADED )
							{
								draw_gouraud_polygon ( poly, face_order->face->face_colour );
							}
							else
							{
								if ( ! ( face_order->face->flags & FACE_NOT_SHADED ) )
								{
									//normal = & face_order->object_base->normals[face_order->face->normal];
			
#ifdef FLOAT_LIBRARY

									fintensity = (	( face_order->face->normal_data.x * face_order->object_base->light.x ) +
														( face_order->face->normal_data.y * face_order->object_base->light.y ) +
														( face_order->face->normal_data.z * face_order->object_base->light.z ) );
						
									fintensity += FLOAT_WHOLE_INTENSITY_FACTOR;
						
									intensity = * ( ( int * ) & fintensity );
						
									intensity -= INTEGER_WHOLE_INTENSITY_FACTOR;
				
									if ( intensity < 0 )
									{
										intensity = 0;
									}
#else
									intensity = imuladdf_ab_cd_ef (	face_order->face->normal_data.x, face_order->object_base->light.x,
																				face_order->face->normal_data.y, face_order->object_base->light.y,
																				face_order->face->normal_data.z, face_order->object_base->light.z );
									if ( intensity < 0 )
									{
										intensity = 0;
									}
					
									intensity = imulf ( intensity, 255 );
#endif
									draw_plain_polygon ( poly, shading_palette[face_order->face->face_colour][intensity] );
								}
								else
								{
									draw_plain_polygon ( poly, face_order->face->face_colour );
								}
							}
						}
						else
						{
							draw_plain_polygon ( poly, face_order->face->face_colour );
						}
					}
				}
		
				face_order = face_order->succ;
			}
		}
		break;

		case	16:
		{
			face_order = list;
		
			while ( face_order )
			{
				clip_coord = 0;
		
				if ( face_order->face->flags & FACE_AFFINE_TEXTURED )
				{
					poly = construct_affine_textured_face (	face_order->face->num_points,
																			face_order->face->list,
																			face_order->object_base->points_base );
				}
				else
				{
					poly = construct_face (	face_order->face->num_points,
													face_order->face->list,
													face_order->object_base->points_base );
				}
		
				if ( ( poly ) && ( poly->polygon_outcode & CLIP_FRONT ) )
				{
					poly = near_clip_face ( poly, face_order->face->flags );
				}
		
//				if ( ( poly ) &&  ( get_cyclic_result ( poly->i, poly->j,
//													poly->next_vertex->i, poly->next_vertex->j,
//													poly->next_vertex->next_vertex->i, poly->next_vertex->next_vertex->j ) < 0 ) )
//				{
//					poly = NULL;
//				}
		
				if ( ( poly ) && ( poly->polygon_outcode ) )
				{
					poly = clip_polygon ( poly, face_order->face->flags );
				}
		
				if ( poly )
				{
					if ( face_order->face->flags & FACE_AFFINE_TEXTURED )
					{
						if ( global_objects[obj].light_sourced )
						{
#ifdef FLOAT_LIBRARY

							fintensity = (	( face_order->face->normal_data.x * face_order->object_base->light.x ) +
												( face_order->face->normal_data.y * face_order->object_base->light.y ) +
												( face_order->face->normal_data.z * face_order->object_base->light.z ) );
				
							fintensity += FLOAT_WHOLE_INTENSITY_FACTOR;
				
							intensity = * ( ( int * ) & fintensity );
				
							intensity -= INTEGER_WHOLE_INTENSITY_FACTOR;
		
							if ( intensity < 0 )
							{
								intensity = 0;
							}
#else
							intensity = imuladdf_ab_cd_ef (	face_order->face->normal_data.x, face_order->object_base->light.x,
																		face_order->face->normal_data.y, face_order->object_base->light.y,
																		face_order->face->normal_data.z, face_order->object_base->light.z );
							if ( intensity < 0 )
							{
								intensity = 0;
							}
			
							intensity = imulf ( intensity, 255 );
#endif
							draw_plain_polygon15 ( poly,
															 face_order->face->red>>3,
															 face_order->face->green>>3,
															 face_order->face->blue>>3 );
		//					draw_textured_shaded_polygon ( poly, face_order->face->texture, intensity );
						}
						else
						{
							draw_plain_polygon15 ( poly,
															 face_order->face->red>>3,
															 face_order->face->green>>3,
															 face_order->face->blue>>3 );
		//					draw_textured_polygon ( poly, face_order->face->texture );
						}
					}
					else
					{
						if ( global_objects[obj].light_sourced )
						{
							if ( face_order->face->flags & FACE_GOURAUD_SHADED )
							{
		//						draw_gouraud_polygon ( poly, face_order->face->face_colour );
		
								draw_gouraud_polygon15 ( poly,
																	face_order->face->red,
																face_order->face->green,
																face_order->face->blue );
							}
							else
							{
#ifdef FLOAT_LIBRARY

								fintensity = (	( face_order->face->normal_data.x * face_order->object_base->light.x ) +
													( face_order->face->normal_data.y * face_order->object_base->light.y ) +
													( face_order->face->normal_data.z * face_order->object_base->light.z ) );
					
								fintensity += FLOAT_WHOLE_INTENSITY_FACTOR;
					
								intensity = * ( ( int * ) & fintensity );
					
								intensity -= INTEGER_WHOLE_INTENSITY_FACTOR;
			
								if ( intensity < 0 )
								{
									intensity = 0;
								}
#else
								intensity = imuladdf_ab_cd_ef (	face_order->face->normal_data.x, face_order->object_base->light.x,
																			face_order->face->normal_data.y, face_order->object_base->light.y,
																			face_order->face->normal_data.z, face_order->object_base->light.z );
								if ( intensity < 0 )
								{
									intensity = 0;
								}
				
								intensity = imulf ( intensity, 255 );
#endif

//								intensity = imuladdf_ab_cd_ef (	face_order->face->normal_data.x, face_order->object_base->light.x,
//																			face_order->face->normal_data.y, face_order->object_base->light.y,
//																			face_order->face->normal_data.z, face_order->object_base->light.z );
//								if ( intensity < 0 )
//								{
//									intensity = 0;
//								}
//
//								intensity = imulf ( intensity, 255 );
		
//								draw_plain_polygon ( poly, shading_palette[face_order->face->face_colour][intensity] );

								draw_plain_polygon15 ( poly,
																	colour_shading[face_order->face->red][intensity],
																	colour_shading[face_order->face->green][intensity],
																	colour_shading[face_order->face->blue][intensity] );
							}
						}
						else
						{
		//					draw_plain_polygon ( poly, face_order->face->face_colour );
							draw_plain_polygon15 ( poly,
															 face_order->face->red>>3,
															 face_order->face->green>>3,
															 face_order->face->blue>>3 );
						}
					}
				}
		
				face_order = face_order->succ;
			}
		}
		break;

		case	32:
		{
			face_order = list;
		
			while ( face_order )
			{
				clip_coord = 0;
		
				if ( face_order->face->flags & FACE_AFFINE_TEXTURED )
				{
					poly = construct_affine_textured_face (	face_order->face->num_points,
																			face_order->face->list,
																			face_order->object_base->points_base );
				}
				else
				{
					poly = construct_face (	face_order->face->num_points,
													face_order->face->list,
													face_order->object_base->points_base );
				}
		
				if ( ( poly ) && ( poly->polygon_outcode & CLIP_FRONT ) )
				{
					poly = near_clip_face ( poly, face_order->face->flags );
				}
		
//				if ( ( poly ) &&  ( get_cyclic_result ( poly->i, poly->j,
//													poly->next_vertex->i, poly->next_vertex->j,
//													poly->next_vertex->next_vertex->i, poly->next_vertex->next_vertex->j ) < 0 ) )
//				{
//					poly = NULL;
//				}
		
				if ( ( poly ) && ( poly->polygon_outcode ) )
				{
					poly = clip_polygon ( poly, face_order->face->flags );
				}
		
				if ( poly )
				{
					if ( face_order->face->flags & FACE_AFFINE_TEXTURED )
					{
						if ( global_objects[obj].light_sourced )
						{
							intensity = imuladdf_ab_cd_ef (	face_order->face->normal_data.x, face_order->object_base->light.x,
																		face_order->face->normal_data.y, face_order->object_base->light.y,
																		face_order->face->normal_data.z, face_order->object_base->light.z );
							if ( intensity < 0 )
							{
								intensity = 0;
							}
			
							intensity = imulf ( intensity, 255 );
		
							draw_plain_polygon24 ( poly,
															 face_order->face->red,
															 face_order->face->green,
															 face_order->face->blue );
		//					draw_textured_shaded_polygon ( poly, face_order->face->texture, intensity );
						}
						else
						{
							draw_plain_polygon24 ( poly,
															 face_order->face->red,
															 face_order->face->green,
															 face_order->face->blue );
		//					draw_textured_polygon ( poly, face_order->face->texture );
						}
					}
					else
					{
						if ( global_objects[obj].light_sourced )
						{
							if ( face_order->face->flags & FACE_GOURAUD_SHADED )
							{
		//						draw_gouraud_polygon ( poly, face_order->face->face_colour );
		
								draw_gouraud_polygon24 ( poly,
																	face_order->face->red,
																	face_order->face->green,
																	face_order->face->blue );
							}
							else
							{
								normal = & face_order->object_base->normals[face_order->face->normal];
		
								intensity = imuladdf_ab_cd_ef (	face_order->face->normal_data.x, face_order->object_base->light.x,
																			face_order->face->normal_data.y, face_order->object_base->light.y,
																			face_order->face->normal_data.z, face_order->object_base->light.z );
								if ( intensity < 0 )
								{
									intensity = 0;
								}
								else
								{
									intensity = imulf ( intensity, 255 );
								}

								{
			
//									get_arbitrary_rotation_matrix ( normal, DEG180, reflected_matrix );
//
//									ray.x = - imuladdf_ab_cd_ef ( light.x, reflected_matrix[0][0], light.y, reflected_matrix[1][0], light.z, reflected_matrix[2][0] );
//									ray.y = - imuladdf_ab_cd_ef ( light.x, reflected_matrix[0][1], light.y, reflected_matrix[1][1], light.z, reflected_matrix[2][1] );
//									ray.z = - imuladdf_ab_cd_ef ( light.x, reflected_matrix[0][2], light.y, reflected_matrix[1][2], light.z, reflected_matrix[2][2] );
//
//									reflectance = imuladdf_ab_cd_ef (	view.x, ray.x, view.y, ray.y, view.z, ray.z );
//
									reflectance = imuladdf_ab_cd_ef (	face_order->face->normal_data.x, highlight.x,
																					face_order->face->normal_data.y, highlight.y,
																					face_order->face->normal_data.z, highlight.z );

									if ( reflectance < 0 )
									{
										reflectance = imulf ( reflectance, reflectance );
										reflectance = imulf ( reflectance, reflectance );
										reflectance = imulf ( reflectance, reflectance );
										reflectance = - imulf ( reflectance, reflectance );
									}
									else
									{
										reflectance = imulf ( reflectance, reflectance );
										reflectance = imulf ( reflectance, reflectance );
										reflectance = imulf ( reflectance, reflectance );
										reflectance = imulf ( reflectance, reflectance );
									}
		//							reflectance = imulf ( reflectance, reflectance );
		//							reflectance = imulf ( reflectance, reflectance );

	
									reflectance = imulf ( reflectance, 255 );
								}
		
		//						draw_plain_polygon ( poly, shading_palette[face_order->face->face_colour][intensity] );
								draw_plain_polygon24 ( poly,
																	true_reflection_palette[ (true_colour_shading[face_order->face->red][intensity]) ][reflectance],
																	true_reflection_palette[ (true_colour_shading[face_order->face->green][intensity]) ][reflectance],
																	true_reflection_palette[ (true_colour_shading[face_order->face->blue][intensity]) ][reflectance] );
							}
						}
						else
						{
		//					draw_plain_polygon ( poly, face_order->face->face_colour );
							draw_plain_polygon24 ( poly,
															 face_order->face->red,
															 face_order->face->green,
															 face_order->face->blue );
						}
					}
				}
		
				face_order = face_order->succ;
			}
		}
		break;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	draw_object_shadow ( object_instance * object )
{
	int
		obj,
		count,
		temp,
		num_faces,
		intensity,
		reflectance,
		last_z,
		rejected;

	crt_coords
		*poly;

	face
		*faces;

	face_list
		*face_order;

	vec3d
		light,
		highlight,
		view,
		rel_pos,
		*normal;

	point_reference
		*point_list;

	REAL
		tmp;

	float
		fintensity;

	double
		timing;

	REAL
		object_height;

	object_info			*	this_object_info;


	fintensity = 0;

	rejected = 0;
	timing = 0;


	//
	//	Quick hack to get rid of any objects behind the viewpoint. This should be removed when the object
	//		sorting is in place.
	//

	//
	// Set up the object drawing global variables
	//

	points_current_base = 0;
	object_current_base = 0;
	object_height = object->vp.y;

	object->vp.y = get_terrain_elevation ( object->vp.x, object->vp.z );

	set_object_relative_position ( visual_vp, object );

	//
	// Get the object number
	//

	obj = object->object_number;

	this_object = obj;

	//
	// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
	//

#ifdef FLOAT_LIBRARY

	rotation.matrix[0][0] = ( object->vp.xv.x * visual_vp->xv.x + object->vp.xv.y * visual_vp->xv.y + object->vp.xv.z * visual_vp->xv.z );
	rotation.matrix[1][0] = 0;	//( object->vp.xv.x * visual_vp->yv.x + object->vp.xv.y * visual_vp->yv.y + object->vp.xv.z * visual_vp->yv.z );
	rotation.matrix[2][0] = ( object->vp.xv.x * visual_vp->zv.x + object->vp.xv.y * visual_vp->zv.y + object->vp.xv.z * visual_vp->zv.z );

	rotation.matrix[0][1] = ( object->vp.yv.x * visual_vp->xv.x + object->vp.yv.y * visual_vp->xv.y + object->vp.yv.z * visual_vp->xv.z );
	rotation.matrix[1][1] = 0;	//( object->vp.yv.x * visual_vp->yv.x + object->vp.yv.y * visual_vp->yv.y + object->vp.yv.z * visual_vp->yv.z );
	rotation.matrix[2][1] = ( object->vp.yv.x * visual_vp->zv.x + object->vp.yv.y * visual_vp->zv.y + object->vp.yv.z * visual_vp->zv.z );

	rotation.matrix[0][2] = ( object->vp.zv.x * visual_vp->xv.x + object->vp.zv.y * visual_vp->xv.y + object->vp.zv.z * visual_vp->xv.z );
	rotation.matrix[1][2] = 0;	//( object->vp.zv.x * visual_vp->yv.x + object->vp.zv.y * visual_vp->yv.y + object->vp.zv.z * visual_vp->yv.z );
	rotation.matrix[2][2] = ( object->vp.zv.x * visual_vp->zv.x + object->vp.zv.y * visual_vp->zv.y + object->vp.zv.z * visual_vp->zv.z );

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	object_pos.x = (	( visual_vp->x - object->vp.x ) * object->vp.xv.x + ( visual_vp->y - object->vp.y ) *  object->vp.xv.y +  ( visual_vp->z - object->vp.z ) *  object->vp.xv.z );
	object_pos.y = (	( visual_vp->x - object->vp.x ) * object->vp.yv.x + ( visual_vp->y - object->vp.y ) *  object->vp.yv.y +  ( visual_vp->z - object->vp.z ) *  object->vp.yv.z );
	object_pos.z = (	( visual_vp->x - object->vp.x ) * object->vp.zv.x + ( visual_vp->y - object->vp.y ) *  object->vp.zv.y +  ( visual_vp->z - object->vp.z ) *  object->vp.zv.z );

	//
	// Rotate the light source vector to be relative to the object.
	//

	light.x = ( light_source.x * object->vp.attitude[0][0] + light_source.y * object->vp.attitude[0][1] + light_source.z * object->vp.attitude[0][2] );
	light.y = ( light_source.x * object->vp.attitude[1][0] + light_source.y * object->vp.attitude[1][1] + light_source.z * object->vp.attitude[1][2] );
	light.z = ( light_source.x * object->vp.attitude[2][0] + light_source.y * object->vp.attitude[2][1] + light_source.z * object->vp.attitude[2][2] );

	//
	// Generate a unit vector in world coordinates from the user to the object
	//

	rel_pos.x = visual_vp->x - object->vp.x;
	rel_pos.y = visual_vp->y - object->vp.y;
	rel_pos.z = visual_vp->z - object->vp.z;

	normalise_vector ( & rel_pos );

	view.x = ( rel_pos.x * object->vp.attitude[0][0] + rel_pos.y * object->vp.attitude[0][1] + rel_pos.z * object->vp.attitude[0][2] );
	view.y = ( rel_pos.x * object->vp.attitude[1][0] + rel_pos.y * object->vp.attitude[1][1] + rel_pos.z * object->vp.attitude[1][2] );
	view.z = ( rel_pos.x * object->vp.attitude[2][0] + rel_pos.y * object->vp.attitude[2][1] + rel_pos.z * object->vp.attitude[2][2] );

	//
	// Generate a highlight vector which is half way between the view vector, and the light vector
	//

	highlight.x = ( light.x - view.x );
	highlight.y = ( light.y - view.y );
	highlight.z = ( light.z - view.z );

	normalise_vector ( & highlight );

#else
	rotation.matrix[0][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->xv.x, object->vp.xv.y, visual_vp->xv.y, object->vp.xv.z, visual_vp->xv.z );
	rotation.matrix[1][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->yv.x, object->vp.xv.y, visual_vp->yv.y, object->vp.xv.z, visual_vp->yv.z );
	rotation.matrix[2][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->zv.x, object->vp.xv.y, visual_vp->zv.y, object->vp.xv.z, visual_vp->zv.z );

	rotation.matrix[0][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->xv.x, object->vp.yv.y, visual_vp->xv.y, object->vp.yv.z, visual_vp->xv.z );
	rotation.matrix[1][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->yv.x, object->vp.yv.y, visual_vp->yv.y, object->vp.yv.z, visual_vp->yv.z );
	rotation.matrix[2][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->zv.x, object->vp.yv.y, visual_vp->zv.y, object->vp.yv.z, visual_vp->zv.z );

	rotation.matrix[0][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->xv.x, object->vp.zv.y, visual_vp->xv.y, object->vp.zv.z, visual_vp->xv.z );
	rotation.matrix[1][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->yv.x, object->vp.zv.y, visual_vp->yv.y, object->vp.zv.z, visual_vp->yv.z );
	rotation.matrix[2][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->zv.x, object->vp.zv.y, visual_vp->zv.y, object->vp.zv.z, visual_vp->zv.z );

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	object_pos.x = imuladdf_ab_cd_ef (	( visual_vp->x - object->vp.x ), object->vp.xv.x, ( visual_vp->y - object->vp.y ), object->vp.xv.y, ( visual_vp->z - object->vp.z ), object->vp.xv.z );
	object_pos.y = imuladdf_ab_cd_ef (	( visual_vp->x - object->vp.x ), object->vp.yv.x, ( visual_vp->y - object->vp.y ), object->vp.yv.y, ( visual_vp->z - object->vp.z ), object->vp.yv.z );
	object_pos.z = imuladdf_ab_cd_ef (	( visual_vp->x - object->vp.x ), object->vp.zv.x, ( visual_vp->y - object->vp.y ), object->vp.zv.y, ( visual_vp->z - object->vp.z ), object->vp.zv.z );

	//
	// Rotate the light source vector to be relative to the object.
	//

	light.x = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[0][0], light_source.y, object->vp.attitude[0][1], light_source.z, object->vp.attitude[0][2] );
	light.y = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[1][0], light_source.y, object->vp.attitude[1][1], light_source.z, object->vp.attitude[1][2] );
	light.z = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[2][0], light_source.y, object->vp.attitude[2][1], light_source.z, object->vp.attitude[2][2] );

	//
	// Generate a unit vector in world coordinates from the user to the object
	//

	rel_pos.x = visual_vp->x - object->vp.x;
	rel_pos.y = visual_vp->y - object->vp.y;
	rel_pos.z = visual_vp->z - object->vp.z;

	normalise_vector ( & rel_pos );

	view.x = imuladdf_ab_cd_ef ( rel_pos.x, object->vp.attitude[0][0], rel_pos.y, object->vp.attitude[0][1], rel_pos.z, object->vp.attitude[0][2] );
	view.y = imuladdf_ab_cd_ef ( rel_pos.x, object->vp.attitude[1][0], rel_pos.y, object->vp.attitude[1][1], rel_pos.z, object->vp.attitude[1][2] );
	view.z = imuladdf_ab_cd_ef ( rel_pos.x, object->vp.attitude[2][0], rel_pos.y, object->vp.attitude[2][1], rel_pos.z, object->vp.attitude[2][2] );

	//
	// Generate a highlight vector which is half way between the view vector, and the light vector
	//

	highlight.x = ( light.x - view.x );
	highlight.y = ( light.y - view.y );
	highlight.z = ( light.z - view.z );

	normalise_vector ( & highlight );

#endif

	//
	// Calculate the object's position relative to the view.
	//

	pos = & object->rel_vp.position;

	//
	//	Set up this objects' object info structure
	//

	object_base[object_current_base].ob = object;
	object_base[object_current_base].light.x = light.x;
	object_base[object_current_base].light.y = light.y;
	object_base[object_current_base].light.z = light.z;
	object_base[object_current_base].points_base = points_current_base;

	this_object_info = & object_base[object_current_base];
	global_object_info = this_object_info;

	//
	// Set up the face sorting variables
	//

	num_faces = global_objects[obj].number_of_faces;

	list = NULL;

	last_insert_point = NULL;

	face_order_index = 0;

	//
	// Insert this objects' faces into the sorted list.
	//

	faces = global_objects[obj].faces;

	object_points = global_objects[obj].points;

#if 0

	process_face_tree ( faces );

#else

	for ( count=0; count<num_faces; count++ )
	{
		point_list = faces[count].list;
		object_points [ point_list->point ].needed = TRUE; point_list++;
		object_points [ point_list->point ].needed = TRUE; point_list++;
		object_points [ point_list->point ].needed = TRUE; point_list++;

		for ( temp = 3; temp < faces[count].num_points; temp ++ )
		{
			object_points[ point_list->point ].needed = TRUE;
			point_list++;
		}

		insert_face ( & faces[count], 0, this_object_info );
	}

#endif

	//
	// Transform the object's shape data
	//

	shadow_object = TRUE;

	transform_3d_object ( & global_objects[obj], pos, & light, & highlight, points_current_base);

	shadow_object = FALSE;

	//
	// Adjust the memory pointers for any sub objects
	//

	object_current_base ++;
	points_current_base += global_objects[obj].number_of_points;

	//
	// Recurse down any sub objects
	//

	if ( object->number_of_sub_objects != 0 )
	{
		for ( count=0; count<object->number_of_sub_objects; count++ )
		{
			draw_sub_object ( object->sub_objects[count], this_object_info, pos );
		}
	}

	//
	//	Ok, now we're ready to draw the actual faces.
	//

	switch ( active_screen->type )
	{
		case	8:
		{
			face_order = list;

			if ( face_order )
			{
				last_z = face_order->z;
			}
		
			while ( face_order )
			{
				clip_coord = 0;

				if ( face_order->face->flags & FACE_SHITTY )
				{
					face_order->face->flags = FACE_SHITTY | FACE_NOT_SHADED;
					face_order->face->face_colour = 64;
				}

				poly = construct_face (	face_order->face->num_points,
												face_order->face->list,
												face_order->object_base->points_base );

				if ( ( poly ) && ( poly->polygon_outcode & CLIP_FRONT ) )
				{
					poly = near_clip_face ( poly, face_order->face->flags );
				}
		
				if ( ( poly ) && ( poly->polygon_outcode ) )
				{
					poly = clip_polygon ( poly, face_order->face->flags );
				}
		
				if ( poly )
				{
					draw_plain_polygon ( poly, 0 );
				}
		
				face_order = face_order->succ;
			}
		}
		break;
	}

	object->vp.y = object_height;

	set_object_relative_position ( visual_vp, object );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	draw_sub_object ( object_instance * object, object_info * parent, vec3d * position )
{
	int						count;
	int						obj;
	int						num_faces;
	face					*	faces;
	vec3d					*	pos;
	view_point			*	vp;
	object_info			*	this_object_info;
	matrix_3x3				temp_matrix;
	vec3d						object_pos;
	vec4d					*	object_points;
	vec3d						normal_pos;
	vec3d						sub_pos;
	vec3d					*	rel;
	point_reference	*	point_list;
	int						temp;
	int						tmp;

	obj	= object->object_number;
	pos	= & object->vp.position;
	rel	= & object->rel_vp.position;
	vp		= & parent->ob->vp;

#ifdef FLOAT_LIBRARY

	//
	// Calculate the object's position relative to the parent object
	//

	object->vp.x = (	( object->rel_vp.x * rotation.a00 ) +
							( object->rel_vp.y * rotation.a10 ) +
							( object->rel_vp.z * rotation.a20 ) );
	object->vp.y = (	( object->rel_vp.x * rotation.a01 ) +
							( object->rel_vp.y * rotation.a11 ) +
							( object->rel_vp.z * rotation.a21 ) );
	object->vp.z = (	( object->rel_vp.x * rotation.a02 ) +
							( object->rel_vp.y * rotation.a12 ) +
							( object->rel_vp.z * rotation.a22 ) );

	//
	// Calculate the object's real world position
	//

	sub_pos.x = (	( rel->x * parent->ob->vp.xv.x ) + ( rel->y * parent->ob->vp.xv.y ) + ( rel->z * parent->ob->vp.xv.z ) );
	sub_pos.y = (	( rel->x * parent->ob->vp.yv.x ) + ( rel->y * parent->ob->vp.yv.y ) + ( rel->z * parent->ob->vp.yv.z ) );
	sub_pos.z = (	( rel->x * parent->ob->vp.zv.x ) + ( rel->y * parent->ob->vp.zv.y ) + ( rel->z * parent->ob->vp.zv.z ) );

#else

	//
	// Calculate the object's position relative to the parent object
	//

	object->vp.x = imulfastf ( object->rel_vp.x, rotation.a00 );
	object->vp.y = imulfastf ( object->rel_vp.x, rotation.a01 );
	object->vp.z = imulfastf ( object->rel_vp.x, rotation.a02 );

	object->vp.x += imulfastf ( object->rel_vp.y, rotation.a10 );
	object->vp.y += imulfastf ( object->rel_vp.y, rotation.a11 );
	object->vp.z += imulfastf ( object->rel_vp.y, rotation.a12 );

	object->vp.x += imulfastf ( object->rel_vp.z, rotation.a20 );
	object->vp.y += imulfastf ( object->rel_vp.z, rotation.a21 );
	object->vp.z += imulfastf ( object->rel_vp.z, rotation.a22 );

	//
	// Calculate the object's real world position
	//

	sub_pos.x = imuladdf_ab_cd_ef (	rel->x, parent->ob->vp.xv.x, rel->y, parent->ob->vp.xv.y, rel->z, parent->ob->vp.xv.z );
	sub_pos.y = imuladdf_ab_cd_ef (	rel->x, parent->ob->vp.yv.x, rel->y, parent->ob->vp.yv.y, rel->z, parent->ob->vp.yv.z );
	sub_pos.z = imuladdf_ab_cd_ef (	rel->x, parent->ob->vp.zv.x, rel->y, parent->ob->vp.zv.y, rel->z, parent->ob->vp.zv.z );

#endif

	object->vp.x += position->x;
	object->vp.y += position->y;
	object->vp.z += position->z;

	sub_pos.x += parent->ob->vp.x;
	sub_pos.y += parent->ob->vp.y;
	sub_pos.z += parent->ob->vp.z;

	if ( ! object->static_object )
	{
		//
		//	Store the rotation matrix, so when we go back to the parent, other sub objects can inherit the matrix safely
		//

		memcpy ( temp_matrix, rotation.matrix, sizeof ( matrix_3x3 ) );

#ifdef FLOAT_LIBRARY

		//
		// Calculate the sub object's rotation matrix, to transform its 3d points relative to the parent object.
		//

		object->vp.xv.x = ( ( object->rel_vp.xv.x * vp->xv.x ) + ( object->rel_vp.xv.y * vp->yv.x ) + ( object->rel_vp.xv.z * vp->zv.x ) );
		object->vp.xv.y = ( ( object->rel_vp.xv.x * vp->xv.y ) + ( object->rel_vp.xv.y * vp->yv.y ) + ( object->rel_vp.xv.z * vp->zv.y ) );
		object->vp.xv.z = ( ( object->rel_vp.xv.x * vp->xv.z ) + ( object->rel_vp.xv.y * vp->yv.z ) + ( object->rel_vp.xv.z * vp->zv.z ) );
	
		object->vp.yv.x = ( ( object->rel_vp.yv.x * vp->xv.x ) + ( object->rel_vp.yv.y * vp->yv.x ) + ( object->rel_vp.yv.z * vp->zv.x ) );
		object->vp.yv.y = ( ( object->rel_vp.yv.x * vp->xv.y ) + ( object->rel_vp.yv.y * vp->yv.y ) + ( object->rel_vp.yv.z * vp->zv.y ) );
		object->vp.yv.z = ( ( object->rel_vp.yv.x * vp->xv.z ) + ( object->rel_vp.yv.y * vp->yv.z ) + ( object->rel_vp.yv.z * vp->zv.z ) );
	
		object->vp.zv.x = ( ( object->rel_vp.zv.x * vp->xv.x ) + ( object->rel_vp.zv.y * vp->yv.x ) + ( object->rel_vp.zv.z * vp->zv.x ) );
		object->vp.zv.y = ( ( object->rel_vp.zv.x * vp->xv.y ) + ( object->rel_vp.zv.y * vp->yv.y ) + ( object->rel_vp.zv.z * vp->zv.y ) );
		object->vp.zv.z = ( ( object->rel_vp.zv.x * vp->xv.z ) + ( object->rel_vp.zv.y * vp->yv.z ) + ( object->rel_vp.zv.z * vp->zv.z ) );

		//
		// Calculate the main matrix to transform the points to the screen
		//

		rotation.matrix[0][0] = ( ( object->vp.xv.x * visual_vp->xv.x ) + ( object->vp.xv.y * visual_vp->xv.y ) + ( object->vp.xv.z * visual_vp->xv.z ) );
		rotation.matrix[1][0] = ( ( object->vp.xv.x * visual_vp->yv.x ) + ( object->vp.xv.y * visual_vp->yv.y ) + ( object->vp.xv.z * visual_vp->yv.z ) );
		rotation.matrix[2][0] = ( ( object->vp.xv.x * visual_vp->zv.x ) + ( object->vp.xv.y * visual_vp->zv.y ) + ( object->vp.xv.z * visual_vp->zv.z ) );
	
		rotation.matrix[0][1] = ( ( object->vp.yv.x * visual_vp->xv.x ) + ( object->vp.yv.y * visual_vp->xv.y ) + ( object->vp.yv.z * visual_vp->xv.z ) );
		rotation.matrix[1][1] = ( ( object->vp.yv.x * visual_vp->yv.x ) + ( object->vp.yv.y * visual_vp->yv.y ) + ( object->vp.yv.z * visual_vp->yv.z ) );
		rotation.matrix[2][1] = ( ( object->vp.yv.x * visual_vp->zv.x ) + ( object->vp.yv.y * visual_vp->zv.y ) + ( object->vp.yv.z * visual_vp->zv.z ) );
	
		rotation.matrix[0][2] = ( ( object->vp.zv.x * visual_vp->xv.x ) + ( object->vp.zv.y * visual_vp->xv.y ) + ( object->vp.zv.z * visual_vp->xv.z ) );
		rotation.matrix[1][2] = ( ( object->vp.zv.x * visual_vp->yv.x ) + ( object->vp.zv.y * visual_vp->yv.y ) + ( object->vp.zv.z * visual_vp->yv.z ) );
		rotation.matrix[2][2] = ( ( object->vp.zv.x * visual_vp->zv.x ) + ( object->vp.zv.y * visual_vp->zv.y ) + ( object->vp.zv.z * visual_vp->zv.z ) );
	
		//
		// Rotate the light source vector to be relative to the object.
		//

		object_base[object_current_base].light.x = ( light_source.x * object->vp.attitude[0][0] + light_source.y * object->vp.attitude[0][1] + light_source.z * object->vp.attitude[0][2] );
		object_base[object_current_base].light.y = ( light_source.x * object->vp.attitude[1][0] + light_source.y * object->vp.attitude[1][1] + light_source.z * object->vp.attitude[1][2] );
		object_base[object_current_base].light.z = ( light_source.x * object->vp.attitude[2][0] + light_source.y * object->vp.attitude[2][1] + light_source.z * object->vp.attitude[2][2] );

#else

		//
		// Calculate the sub object's rotation matrix, to transform its 3d points relative to the parent object.
		//

		object->vp.xv.x = imuladdf_ab_cd_ef ( object->rel_vp.xv.x, vp->xv.x, object->rel_vp.xv.y, vp->yv.x, object->rel_vp.xv.z, vp->zv.x );
		object->vp.xv.y = imuladdf_ab_cd_ef ( object->rel_vp.xv.x, vp->xv.y, object->rel_vp.xv.y, vp->yv.y, object->rel_vp.xv.z, vp->zv.y );
		object->vp.xv.z = imuladdf_ab_cd_ef ( object->rel_vp.xv.x, vp->xv.z, object->rel_vp.xv.y, vp->yv.z, object->rel_vp.xv.z, vp->zv.z );
	
		object->vp.yv.x = imuladdf_ab_cd_ef ( object->rel_vp.yv.x, vp->xv.x, object->rel_vp.yv.y, vp->yv.x, object->rel_vp.yv.z, vp->zv.x );
		object->vp.yv.y = imuladdf_ab_cd_ef ( object->rel_vp.yv.x, vp->xv.y, object->rel_vp.yv.y, vp->yv.y, object->rel_vp.yv.z, vp->zv.y );
		object->vp.yv.z = imuladdf_ab_cd_ef ( object->rel_vp.yv.x, vp->xv.z, object->rel_vp.yv.y, vp->yv.z, object->rel_vp.yv.z, vp->zv.z );
	
		object->vp.zv.x = imuladdf_ab_cd_ef ( object->rel_vp.zv.x, vp->xv.x, object->rel_vp.zv.y, vp->yv.x, object->rel_vp.zv.z, vp->zv.x );
		object->vp.zv.y = imuladdf_ab_cd_ef ( object->rel_vp.zv.x, vp->xv.y, object->rel_vp.zv.y, vp->yv.y, object->rel_vp.zv.z, vp->zv.y );
		object->vp.zv.z = imuladdf_ab_cd_ef ( object->rel_vp.zv.x, vp->xv.z, object->rel_vp.zv.y, vp->yv.z, object->rel_vp.zv.z, vp->zv.z );

		//
		// Calculate the main matrix to transform the points to the screen
		//

		rotation.matrix[0][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->xv.x, object->vp.xv.y, visual_vp->xv.y, object->vp.xv.z, visual_vp->xv.z );
		rotation.matrix[1][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->yv.x, object->vp.xv.y, visual_vp->yv.y, object->vp.xv.z, visual_vp->yv.z );
		rotation.matrix[2][0] = imuladdf_ab_cd_ef ( object->vp.xv.x, visual_vp->zv.x, object->vp.xv.y, visual_vp->zv.y, object->vp.xv.z, visual_vp->zv.z );
	
		rotation.matrix[0][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->xv.x, object->vp.yv.y, visual_vp->xv.y, object->vp.yv.z, visual_vp->xv.z );
		rotation.matrix[1][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->yv.x, object->vp.yv.y, visual_vp->yv.y, object->vp.yv.z, visual_vp->yv.z );
		rotation.matrix[2][1] = imuladdf_ab_cd_ef ( object->vp.yv.x, visual_vp->zv.x, object->vp.yv.y, visual_vp->zv.y, object->vp.yv.z, visual_vp->zv.z );
	
		rotation.matrix[0][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->xv.x, object->vp.zv.y, visual_vp->xv.y, object->vp.zv.z, visual_vp->xv.z );
		rotation.matrix[1][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->yv.x, object->vp.zv.y, visual_vp->yv.y, object->vp.zv.z, visual_vp->yv.z );
		rotation.matrix[2][2] = imuladdf_ab_cd_ef ( object->vp.zv.x, visual_vp->zv.x, object->vp.zv.y, visual_vp->zv.y, object->vp.zv.z, visual_vp->zv.z );
	
		//
		// Rotate the light source vector to be relative to the object.
		//

		object_base[object_current_base].light.x = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[0][0], light_source.y, object->vp.attitude[0][1], light_source.z, object->vp.attitude[0][2] );
		object_base[object_current_base].light.y = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[1][0], light_source.y, object->vp.attitude[1][1], light_source.z, object->vp.attitude[1][2] );
		object_base[object_current_base].light.z = imuladdf_ab_cd_ef ( light_source.x, object->vp.attitude[2][0], light_source.y, object->vp.attitude[2][1], light_source.z, object->vp.attitude[2][2] );

#endif

	}
	else
	{
		//
		// Calculate the sub object's rotation matrix, to transform its 3d points relative to the parent object.
		//

		memcpy ( object->vp.attitude, vp->attitude, sizeof ( matrix_3x3 ) );

		object_base[object_current_base].light.x = parent->light.x;
		object_base[object_current_base].light.y = parent->light.y;
		object_base[object_current_base].light.z = parent->light.z;
	}

#ifdef FLOAT_LIBRARY

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	object_pos.x = (	( visual_vp->x - sub_pos.x ) * object->vp.xv.x + ( visual_vp->y - sub_pos.y ) * object->vp.xv.y + ( visual_vp->z - sub_pos.z ) * object->vp.xv.z );
	object_pos.y = (	( visual_vp->x - sub_pos.x ) * object->vp.yv.x + ( visual_vp->y - sub_pos.y ) * object->vp.yv.y + ( visual_vp->z - sub_pos.z ) * object->vp.yv.z );
	object_pos.z = (	( visual_vp->x - sub_pos.x ) * object->vp.zv.x + ( visual_vp->y - sub_pos.y ) * object->vp.zv.y + ( visual_vp->z - sub_pos.z ) * object->vp.zv.z );

#else

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	object_pos.x = imuladdf_ab_cd_ef (	( visual_vp->x - sub_pos.x ), object->vp.xv.x, ( visual_vp->y - sub_pos.y ), object->vp.xv.y, ( visual_vp->z - sub_pos.z ), object->vp.xv.z );
	object_pos.y = imuladdf_ab_cd_ef (	( visual_vp->x - sub_pos.x ), object->vp.yv.x, ( visual_vp->y - sub_pos.y ), object->vp.yv.y, ( visual_vp->z - sub_pos.z ), object->vp.yv.z );
	object_pos.z = imuladdf_ab_cd_ef (	( visual_vp->x - sub_pos.x ), object->vp.zv.x, ( visual_vp->y - sub_pos.y ), object->vp.zv.y, ( visual_vp->z - sub_pos.z ), object->vp.zv.z );

#endif

	//
	//	Set up this objects' object info structure
	//

	object_base[object_current_base].ob = object;
	object_base[object_current_base].normals = global_objects[obj].face_normals;
	object_base[object_current_base].points_base = points_current_base;

	this_object_info = & object_base[object_current_base];

	//
	// Set up the face sorting variables
	//

	num_faces = global_objects[obj].number_of_faces;

	faces = global_objects[obj].faces;

	object_points = global_objects[obj].points;

	//
	// Insert this objects' faces into the sorted list.
	//

	for ( count=0; count<num_faces; count++ )
	{
		normal_pos.x = + faces[count].dpoint.x - object_pos.x;
		normal_pos.y = + faces[count].dpoint.y - object_pos.y;
		normal_pos.z = + faces[count].dpoint.z - object_pos.z;

#ifdef FLOAT_LIBRARY
		if	( (	( normal_pos.x * faces[count].normal_data.x ) +
					( normal_pos.y * faces[count].normal_data.y ) +
					( normal_pos.z * faces[count].normal_data.z ) ) > 0 )
#else
		if ( backface_check ( & normal_pos, & faces[count].normal_data ) > 0 )
#endif
		{
			point_list = faces[count].list;

			object_points [ point_list[0].point ].needed = TRUE;
			object_points [ point_list[1].point ].needed = TRUE;
			object_points [ point_list[2].point ].needed = TRUE;

			for ( temp = 3; temp < faces[count].num_points; temp ++ )
			{
				object_points[ point_list[temp].point ].needed = TRUE;
			}

#ifdef FLOAT_LIBRARY

			tmp = (	( faces[count].dpoint.x * rotation.a02 ) +
						( faces[count].dpoint.y * rotation.a12 ) +
						( faces[count].dpoint.z * rotation.a22 ) + pos->z );

			temp = * ( (int*) &tmp );
			temp -= INTEGER_METRES_FACTOR;

#else

			temp = imulfastf ( faces[count].dpoint.x, rotation.a02 );
			temp += imulfastf ( faces[count].dpoint.y, rotation.a12 );
			temp += imulfastf ( faces[count].dpoint.z, rotation.a22 );
			temp += pos->z;

#endif

			insert_face ( & faces[count], temp, this_object_info );
		}
	}

	//
	// Transform the object's shape data
	//

	transform_3d_object ( & global_objects[obj], & object->vp.position, & object_base[object_current_base].light, & object_base[object_current_base].light, points_current_base );

	//
	// Set the points base index to after the end of the object.
	//

	object_current_base ++;
	points_current_base += global_objects[obj].number_of_points;

	//
	// Recurse down any sub objects
	//

	if ( object->number_of_sub_objects != 0 )
	{
		for ( count=0; count<object->number_of_sub_objects; count++ )
		{
			draw_sub_object ( object->sub_objects[count], this_object_info, & object->vp.position );
		}
	}

	if ( ! object->static_object )
	{
		memcpy ( rotation.matrix, temp_matrix, sizeof ( matrix_3x3 ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum OBJECT_3D_VISIBILITY	set_object_relative_position ( view_point *vp, object_instance * object )
{
	REAL
		radius,
		z,
		q,
		i,
		j;

	int
		screenx,
		screeny,
		width,
		height,
		outcode,
		outcode1,
		outcode2;

#ifdef FLOAT_LIBRARY

	object->rel_vp.x = (	( object->vp.x - vp->x ) * vp->xv.x + ( object->vp.y - vp->y ) * vp->xv.y + ( object->vp.z - vp->z ) * vp->xv.z );
	object->rel_vp.y = (	( object->vp.x - vp->x ) * vp->yv.x + ( object->vp.y - vp->y ) * vp->yv.y + ( object->vp.z - vp->z ) * vp->yv.z );
	object->rel_vp.z = (	( object->vp.x - vp->x ) * vp->zv.x + ( object->vp.y - vp->y ) * vp->zv.y + ( object->vp.z - vp->z ) * vp->zv.z );

	radius = global_objects[object->object_number].radius;

	if ( ( object->rel_vp.z + radius ) < eye_near_distance )
	{
		return ( OBJECT_NOT_VISIBLE );
	}

	z = object->rel_vp.z - radius;

	if ( z > eye_near_distance )
	{
		//
		// It is possible for this object to be labelled completely visible.
		//

		q = 1.0 / z;
	
		i = ( active_screen_width_eye_scale * object->rel_vp.x * q ) + FLOAT_FLOAT_FACTOR;
	
		j = ( active_screen_height_eye_scale * object->rel_vp.y * q ) + FLOAT_FLOAT_FACTOR;
	
		width = active_screen_width_eye_scale * radius * q;
	
		height = active_screen_width_eye_scale * radius * q;
	
		screeny = ( active_screen_height_middle - ( ( * ( ( int * ) & j ) ) - INTEGER_FLOAT_FACTOR ) );
	
		screenx = ( active_screen_width_middle + ( ( * ( ( int * ) & i ) ) - INTEGER_FLOAT_FACTOR ) );
	
		outcode = generate_2d_outcode ( screenx, screeny );
		outcode1 = outcode;
		outcode2 = outcode;
	
		outcode = generate_2d_outcode ( screenx + width, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		outcode = generate_2d_outcode ( screenx - width, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		outcode = generate_2d_outcode ( screenx, screeny + height );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		outcode = generate_2d_outcode ( screenx, screeny - height );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		if ( outcode2 != 0 )
		{
			return ( OBJECT_NOT_VISIBLE );
		}
	
		if ( outcode1 == 0 )
		{
			return ( OBJECT_COMPLETELY_VISIBLE );
		}
	
		return ( OBJECT_PARTIALLY_VISIBLE );
	
	}
	else
	{
		//
		// The object cannot be completely visible, as it intersects the eye_distance plane
		//

		z = object->rel_vp.z + radius;
	
		q = 1.0 / z;
	
		i = ( active_screen_width_eye_scale * object->rel_vp.x * q ) + FLOAT_FLOAT_FACTOR;
	
		j = ( active_screen_height_eye_scale * object->rel_vp.y * q ) + FLOAT_FLOAT_FACTOR;
	
		width = active_screen_width_eye_scale * radius * q;
	
		height = active_screen_width_eye_scale * radius * q;
	
		screeny = ( active_screen_height_middle - ( ( * ( ( int * ) & j ) ) - INTEGER_FLOAT_FACTOR ) );
	
		screenx = ( active_screen_width_middle + ( ( * ( ( int * ) & i ) ) - INTEGER_FLOAT_FACTOR ) );
	
		outcode = generate_2d_outcode ( screenx, screeny );
		outcode1 = outcode;
		outcode2 = outcode;
	
		outcode = generate_2d_outcode ( screenx + width, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		outcode = generate_2d_outcode ( screenx - width, screeny );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		outcode = generate_2d_outcode ( screenx, screeny + height );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		outcode = generate_2d_outcode ( screenx, screeny - height );
		outcode1 |= outcode;
		outcode2 &= outcode;
	
		if ( outcode2 != 0 )
		{
			return ( OBJECT_NOT_VISIBLE );
		}
		else
		{
			return ( OBJECT_PARTIALLY_VISIBLE );
		}
	}


#else

	object->rel_vp.x = imuladdf_ab_cd_ef (	( object->vp.x - vp->x ), vp->xv.x, ( object->vp.y - vp->y ), vp->xv.y, ( object->vp.z - vp->z ), vp->xv.z );
	object->rel_vp.y = imuladdf_ab_cd_ef (	( object->vp.x - vp->x ), vp->yv.x, ( object->vp.y - vp->y ), vp->yv.y, ( object->vp.z - vp->z ), vp->yv.z );
	object->rel_vp.z = imuladdf_ab_cd_ef (	( object->vp.x - vp->x ), vp->zv.x, ( object->vp.y - vp->y ), vp->zv.y, ( object->vp.z - vp->z ), vp->zv.z );

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_face (face * this_face, int z, object_info * this_object_info )
{
	face_list *new_list_item;

	face_checks = 0;

	new_list_item = & face_order_list[face_order_index++];

	new_list_item->z = z;
	new_list_item->face = this_face;
	new_list_item->object_base = this_object_info;

	if (!last_insert_point)
	{
		list = new_list_item;
		list->pred = NULL;
		list->succ = NULL;
		last_insert_point = list;

		return;
	}
	else
	{

#if 0
		//
		// DEBUG
		//
		last_insert_point->succ = new_list_item;
		new_list_item->pred = last_insert_point;
		new_list_item->succ = NULL;

		last_insert_point = new_list_item;
		return;

		//
		// DEBUG
		//
#else

		if (z < last_insert_point->z)
		{
			// Search Forwards

			while (last_insert_point)
			{
				face_checks ++;

				if (z >= last_insert_point->z)
				{
					// Insert before this one.

					new_list_item->pred = last_insert_point->pred;
					new_list_item->succ = last_insert_point;

					last_insert_point->pred = new_list_item;
					if (new_list_item->pred)
					{
						new_list_item->pred->succ = new_list_item;
					}

					last_insert_point = new_list_item;

					return;
				}

				if (last_insert_point->succ)
				{
					last_insert_point = last_insert_point->succ;

//					if (last_insert_point->succ)
//					{
//						last_insert_point = last_insert_point->succ;
//					}
				}
				else
				{
					// Insert at end of list

					last_insert_point->succ = new_list_item;
					new_list_item->pred = last_insert_point;
					new_list_item->succ = NULL;

					last_insert_point = new_list_item;

					return;
				}
			}
		}
		else
		{
			// Search Backwards

			while (last_insert_point)
			{
				face_checks ++;

				if (z <= last_insert_point->z)
				{
					// Insert after this one.

					new_list_item->pred = last_insert_point;
					new_list_item->succ = last_insert_point->succ;
					last_insert_point->succ = new_list_item;

					if (new_list_item->succ)
					{
						new_list_item->succ->pred = new_list_item;
					}

					last_insert_point = new_list_item;

					return;
				}

				if (last_insert_point->pred)
				{
					last_insert_point = last_insert_point->pred;

//					if (last_insert_point->pred)
//					{
//						last_insert_point = last_insert_point->pred;
//					}
				}
				else
				{
					// Insert at start of list

					list->pred = new_list_item;
					new_list_item->succ = list;
					new_list_item->pred = NULL;

					list = new_list_item;

					last_insert_point = new_list_item;

					return;
				}
			}
		}

#endif

	}
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_drawing_list * get_object_drawing_slot ( void )
{
	if ( object_order_index < MAX_OBJECTS )
	{
		return ( & object_order_list[object_order_index++] );
	}
	else
	{
		return ( NULL );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_object_to_draw ( object_drawing_list * object )
{
	if ( ! last_object_insert_point )
	{
		object_list = object;
		object_list->pred = NULL;
		object_list->succ = NULL;
		last_object_insert_point = object_list;

		return;
	}
	else
	{
		if ( object->z < last_object_insert_point->z )
		{
			// Search Forwards

			while ( last_object_insert_point )
			{
				if ( object->z >= last_object_insert_point->z )
				{
					// Insert before this one.

					object->pred = last_object_insert_point->pred;
					object->succ = last_object_insert_point;

					last_object_insert_point->pred = object;
					if (object->pred)
					{
						object->pred->succ = object;
					}

					last_object_insert_point = object;

					return;
				}

				if (last_object_insert_point->succ)
				{
					last_object_insert_point = last_object_insert_point->succ;
				}
				else
				{
					// Insert at end of list

					last_object_insert_point->succ = object;
					object->pred = last_object_insert_point;
					object->succ = NULL;

					last_object_insert_point = object;

					return;
				}
			}
		}
		else
		{
			// Search Backwards

			while (last_object_insert_point)
			{
				if (object->z <= last_object_insert_point->z)
				{
					// Insert after this one.

					object->pred = last_object_insert_point;
					object->succ = last_object_insert_point->succ;
					last_object_insert_point->succ = object;

					if (object->succ)
					{
						object->succ->pred = object;
					}

					last_object_insert_point = object;

					return;
				}

				if (last_object_insert_point->pred)
				{
					last_object_insert_point = last_object_insert_point->pred;
				}
				else
				{
					// Insert at start of list

					object_list->pred = object;
					object->succ = object_list;
					object->pred = NULL;

					object_list = object;

					last_object_insert_point = object;

					return;
				}
			}
		}
	}

	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	clear_object_list ( void )
{
	object_list = NULL;

	last_object_insert_point = NULL;

	object_order_index = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	process_face_tree ( face * node )
{
	point_reference	*	point_list;
	int						temp, tmp;

	normal_pos.x = node->dpoint.x - object_pos.x;
	normal_pos.y = node->dpoint.y - object_pos.y;
	normal_pos.z = node->dpoint.z - object_pos.z;

#ifdef FLOAT_LIBRARY
	if ( (	( normal_pos.x * node->normal_data.x ) +
				( normal_pos.y * node->normal_data.y ) +
				( normal_pos.z * node->normal_data.z ) ) > 0 )
#else
	if ( backface_check ( & normal_pos, & node->normal_data ) > 0 )
#endif
	{
		if ( node->infront )
		{
			process_face_tree ( node->infront );
		}

		point_list = node->list;
		object_points [ point_list->point ].needed = TRUE; point_list++;
		object_points [ point_list->point ].needed = TRUE; point_list++;
		object_points [ point_list->point ].needed = TRUE; point_list++;

		for ( temp = 3; temp < node->num_points; temp ++ )
		{
			object_points[ point_list->point ].needed = TRUE;
			point_list++;
		}

//		tmp = imulfastf ( node->dpoint.x, rotation.a02 );
//		tmp += imulfastf ( node->dpoint.y, rotation.a12 );
//		tmp += imulfastf ( node->dpoint.z, rotation.a22 );
//		tmp += pos->z;
		tmp =0;

		insert_face ( node, tmp, global_object_info );

		if ( node->behind )
		{
			process_face_tree ( node->behind );
		}
	}
	else
	{
		if  ( node->behind )
		{
			process_face_tree ( node->behind );
		}

		if ( node->infront )
		{
			process_face_tree ( node->infront );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

