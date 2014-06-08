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

#if 0
//
// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
//
//
//  This file needs a re-write. The calling convention etc is fine, but there is a lot of superflous
//		maths being done, to recalculate the lighting for detail faces. Also, need to put in if the
//		main face with detail polys on it is rejected, then so are all the detail faces.
//
// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_face_list
	*object_3d_face_sorted_list,
	*object_3d_detail_face_sorted_list;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static object_3d_face_list
	object_3d_face_order_list[MAX_3D_FACES];

static int
	object_3d_face_order_index;

static object_3d_face_list
	*last_face_insert_point,
	*last_detail_face_insert_point;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_object_face ( object_3d_face_list *face_order );

static void render_3d_object_unlit_face ( object_3d_face *this_face, int surface_index, int reference_offset, int texture_index, object_3d_face_list *face_order );

static void render_3d_object_specularly_lit_face ( object_3d_face *this_face, int surface_index, int reference_offset, int texture_index, object_3d_face_list *face_order );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_object_faces ( void )
{

	object_3d_face_list
		*face_order;

	face_order = object_3d_face_sorted_list;

	while ( face_order )
	{

		render_3d_object_face ( face_order );

		face_order = face_order->succ;
	}

	face_order = object_3d_detail_face_sorted_list;

	while ( face_order )
	{

		render_3d_object_face ( face_order );

		face_order = face_order->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_object_face ( object_3d_face_list *face_order )
{

	object_3d_face
		*main_face;

	main_face = face_order->face;

	current_object_3d_surface = &objects_3d_data[ face_order->object_base->object_number ].surfaces[face_order->surface];
	current_object_3d_point_list = &objects_3d_data[face_order->object_base->object_number].object_faces_point_plain_list[face_order->point_reference_index];
	current_object_3d_gouraud_list = NULL;	//&objects_3d_data[face_order->object_base->object_number].object_point_normal_references[face_order->gouraud_point_index];
	current_object_3d_face_normal_list = &objects_3d_data[face_order->object_base->object_number].object_face_normal_references[face_order->face_normal_index];
	current_object_3d_transformed_normals = &transformed_3d_normals[face_order->object_base->points_base];
	current_object_3d_texture_list = NULL;	//&objects_3d_data[face_order->object_base->object_number].object_faces_texture_point_list[face_order->texture_point_index];

	if ( current_object_3d_surface->specularity )			{ current_object_3d_specular = specular_rendering_enabled; }
	else																	{ current_object_3d_specular = FALSE; }

	reset_deferred_state_changes ();

	set_deferred_d3d_int_state ( D3DRS_SPECULARENABLE, current_object_3d_specular );

	set_deferred_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );

	if ( !outcode_3d_object_polygon ( main_face->number_of_points, current_object_3d_point_list, face_order->object_base->points_base, &current_object_3d_outcode ) )
	{

		if ( current_object_3d_outcode )
		{

			if ( current_object_3d_surface->textured )
			{

				if ( current_object_3d_surface->texture_wrapped_u )	{ current_object_3d_texture_u_address = D3DTADDRESS_WRAP; }
				else																	{ current_object_3d_texture_u_address = D3DTADDRESS_CLAMP; }

				if ( current_object_3d_surface->texture_wrapped_v )	{ current_object_3d_texture_v_address = D3DTADDRESS_WRAP; }
				else																	{ current_object_3d_texture_v_address = D3DTADDRESS_CLAMP; }

				if ( current_object_3d_surface->texture_filtered )		{ current_object_3d_texture_filter = D3DTFG_LINEAR; }
				else																	{ current_object_3d_texture_filter = D3DTFG_POINT; }

				if ( current_object_3d_surface->texture_mipmapped )	{ current_object_3d_texture_mipmap = D3DTFP_POINT; }
				else																	{ current_object_3d_texture_mipmap = D3DTFP_NONE; }

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

				set_deferred_d3d_texture ( 0, current_object_3d_texture );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

				if ( current_object_3d_surface->polygons )
				{

					if ( current_object_3d_surface->smoothed )
					{

//						wrender_clipped_3d_object_gouraud_textured_polygon ( main_face, face_order->object_base );
					}
					else
					{

//						wrender_clipped_3d_object_textured_polygon ( main_face, face_order->object_base );
					}
				}
				else
				{

//					wrender_clipped_3d_object_textured_line ( main_face, face_order->object_base );
				}
			}
			else
			{

				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
				set_deferred_d3d_texture ( 0, NULL );

				if ( current_object_3d_surface->polygons )
				{

					if ( current_object_3d_surface->smoothed )
					{

//						wrender_clipped_3d_object_gouraud_polygon ( main_face, face_order->object_base );
					}
					else
					{

//						wrender_clipped_3d_object_polygon ( main_face, face_order->object_base );
					}
				}
				else
				{

//					wrender_clipped_3d_object_plain_line ( main_face, face_order->object_base );
				}
			}
		}
		else
		{

			if ( current_object_3d_surface->textured )
			{

				if ( current_object_3d_surface->texture_wrapped_u )	{ current_object_3d_texture_u_address = D3DTADDRESS_WRAP; }
				else																	{ current_object_3d_texture_u_address = D3DTADDRESS_CLAMP; }

				if ( current_object_3d_surface->texture_wrapped_v )	{ current_object_3d_texture_v_address = D3DTADDRESS_WRAP; }
				else																	{ current_object_3d_texture_v_address = D3DTADDRESS_CLAMP; }

				if ( current_object_3d_surface->texture_filtered )		{ current_object_3d_texture_filter = D3DTFG_LINEAR; }
				else																	{ current_object_3d_texture_filter = D3DTFG_POINT; }

				if ( current_object_3d_surface->texture_mipmapped )	{ current_object_3d_texture_mipmap = D3DTFP_POINT; }
				else																	{ current_object_3d_texture_mipmap = D3DTFP_NONE; }

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

				set_deferred_d3d_texture ( 0, current_object_3d_texture );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

				if ( current_object_3d_surface->polygons )
				{

					if ( current_object_3d_surface->smoothed )
					{

//						wrender_unclipped_3d_object_gouraud_textured_polygon ( main_face, face_order->object_base );
					}
					else
					{

//						wrender_unclipped_3d_object_textured_polygon ( main_face, face_order->object_base );
					}
				}
				else
				{

//					wrender_unclipped_3d_object_textured_line ( main_face, face_order->object_base );
				}
			}
			else
			{

				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
				set_deferred_d3d_texture ( 0, NULL );

				if ( current_object_3d_surface->polygons )
				{

					if ( current_object_3d_surface->smoothed )
					{

//						wrender_unclipped_3d_object_gouraud_polygon ( main_face, face_order->object_base );
					}
					else
					{

//						wrender_unclipped_3d_object_polygon ( main_face, face_order->object_base );
					}
				}
				else
				{

//					wrender_unclipped_3d_object_plain_line ( main_face, face_order->object_base );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_face_sorting ( void )
{

	object_3d_face_sorted_list = NULL;

	object_3d_detail_face_sorted_list = NULL;

	last_face_insert_point = NULL;

	last_detail_face_insert_point = NULL;

	object_3d_face_order_index = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_z_sorted_3d_face ( object_3d_face *this_face, int z, int surface, int point_reference_index, int gouraud_index, int face_normal_index, int texture_index, object_3d_info *this_object_3d_info )
{

	object_3d_face_list
		*new_list_item;

	face_surface_description
		*this_surface;

	this_surface = &objects_3d_data[ this_object_3d_info->object_number ].surfaces[surface];

	new_list_item = &object_3d_face_order_list[object_3d_face_order_index++];

	new_list_item->z = z;
	new_list_item->surface = surface;
	new_list_item->point_reference_index = point_reference_index;
	new_list_item->gouraud_point_index = gouraud_index;
	new_list_item->face_normal_index = face_normal_index;
	new_list_item->texture_point_index = texture_index;
	new_list_item->face = this_surface->polygons ? this_face : NULL;
	new_list_item->object_base = this_object_3d_info;

	if ( this_surface->detail )
	{

		if ( !last_detail_face_insert_point )
		{

			object_3d_detail_face_sorted_list = new_list_item;

			object_3d_detail_face_sorted_list->pred = NULL;

			object_3d_detail_face_sorted_list->succ = NULL;

			last_detail_face_insert_point = object_3d_detail_face_sorted_list;

			return;
		}
		else
		{

			if ( z < last_detail_face_insert_point->z )
			{

				//
				// Search Forwards
				//

				while ( last_detail_face_insert_point )
				{

					if ( z >= last_detail_face_insert_point->z )
					{

						//
						// Insert before this one.
						//

						new_list_item->pred = last_detail_face_insert_point->pred;

						new_list_item->succ = last_detail_face_insert_point;

						last_detail_face_insert_point->pred = new_list_item;

						if ( new_list_item->pred )
						{

							new_list_item->pred->succ = new_list_item;
						}

						last_detail_face_insert_point = new_list_item;

						return;
					}

					if ( last_detail_face_insert_point->succ )
					{

						last_detail_face_insert_point = last_detail_face_insert_point->succ;
					}
					else
					{

						//
						// Insert at end of list
						//

						last_detail_face_insert_point->succ = new_list_item;

						new_list_item->pred = last_detail_face_insert_point;

						new_list_item->succ = NULL;

						last_detail_face_insert_point = new_list_item;

						return;
					}
				}
			}
			else
			{

				//
				// Search Backwards
				//

				while ( last_detail_face_insert_point )
				{

					if ( z <= last_detail_face_insert_point->z )
					{

						//
						// Insert after this one.
						//

						new_list_item->pred = last_detail_face_insert_point;

						new_list_item->succ = last_detail_face_insert_point->succ;

						last_detail_face_insert_point->succ = new_list_item;

						if ( new_list_item->succ )
						{

							new_list_item->succ->pred = new_list_item;
						}

						last_detail_face_insert_point = new_list_item;

						return;
					}

					if ( last_detail_face_insert_point->pred )
					{

						last_detail_face_insert_point = last_detail_face_insert_point->pred;

					}
					else
					{

						//
						// Insert at start of list
						//

						object_3d_detail_face_sorted_list->pred = new_list_item;

						new_list_item->succ = object_3d_detail_face_sorted_list;

						new_list_item->pred = NULL;

						object_3d_detail_face_sorted_list = new_list_item;

						last_detail_face_insert_point = new_list_item;

						return;
					}
				}
			}
		}
	}
	else
	{

		if ( !last_face_insert_point )
		{

			object_3d_face_sorted_list = new_list_item;

			object_3d_face_sorted_list->pred = NULL;

			object_3d_face_sorted_list->succ = NULL;

			last_face_insert_point = object_3d_face_sorted_list;

			return;
		}
		else
		{

			if ( z < last_face_insert_point->z )
			{

				//
				// Search Forwards
				//

				while ( last_face_insert_point )
				{

					if ( z >= last_face_insert_point->z )
					{

						//
						// Insert before this one.
						//

						new_list_item->pred = last_face_insert_point->pred;

						new_list_item->succ = last_face_insert_point;

						last_face_insert_point->pred = new_list_item;

						if ( new_list_item->pred )
						{

							new_list_item->pred->succ = new_list_item;
						}

						last_face_insert_point = new_list_item;

						return;
					}

					if ( last_face_insert_point->succ )
					{

						last_face_insert_point = last_face_insert_point->succ;
					}
					else
					{

						//
						// Insert at end of list
						//

						last_face_insert_point->succ = new_list_item;

						new_list_item->pred = last_face_insert_point;

						new_list_item->succ = NULL;

						last_face_insert_point = new_list_item;

						return;
					}
				}
			}
			else
			{

				//
				// Search Backwards
				//

				while ( last_face_insert_point )
				{

					if ( z <= last_face_insert_point->z )
					{

						//
						// Insert after this one.
						//

						new_list_item->pred = last_face_insert_point;

						new_list_item->succ = last_face_insert_point->succ;

						last_face_insert_point->succ = new_list_item;

						if ( new_list_item->succ )
						{

							new_list_item->succ->pred = new_list_item;
						}

						last_face_insert_point = new_list_item;

						return;
					}

					if ( last_face_insert_point->pred )
					{

						last_face_insert_point = last_face_insert_point->pred;

					}
					else
					{

						//
						// Insert at start of list
						//

						object_3d_face_sorted_list->pred = new_list_item;

						new_list_item->succ = object_3d_face_sorted_list;

						new_list_item->pred = NULL;

						object_3d_face_sorted_list = new_list_item;

						last_face_insert_point = new_list_item;

						return;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
