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

#include "terrain.h"
//VJ 051011 global zbuffer optional
#include "cmndline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Store the transformed vertices in a global array ( like the transformed_3d_points )
//	 but specifically for the terrain - this ensures the 3d objects can have all the other points
//

#define TERRAIN_SECTOR_APPROXIMATION_DISTANCE 3072

#define MAX_TERRAIN_TRANSFORMED_3D_POINTS 4096

#define ALLOW_TERRAIN_TEXTURES 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// All the global variables which are used in rendering the terrain
//

terrain_3d_point_byte_reference
	*terrain_3d_sector_point_byte_references;

terrain_3d_point_word_reference
	*terrain_3d_sector_point_word_references;

terrain_types
	current_terrain_type;

terrain_type_info
	*current_terrain_type_class;

terrain_3d_sector
	*current_terrain_sector;

terrain_3d_point_xz
	*current_terrain_points_xz;

terrain_3d_point_y
	*current_terrain_points_y;

float
	current_terrain_sector_xz_texture_scale,
	current_terrain_sector_y_texture_scale;

terrain_3d_transformed_point_colour
	transformed_3d_point_colours[MAX_TERRAIN_TRANSFORMED_3D_POINTS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	terrain_texture_mag_filter,
	terrain_texture_min_filter,
	terrain_texture_mip_filter;

int
	terrain_object_rendering_enabled = TRUE;

int
	current_terrain_x_int,
	current_terrain_z_int,
	current_terrain_y_int;

//
// Some variables, because WATCOM uses DOUBLES to store #define'd stuff - and doesn't align them!
//

float
	terrain_3d_xz_scale = TERRAIN_3D_XZ_SCALE,
	terrain_3d_y_scale = TERRAIN_3D_Y_SCALE;

//
// Some handy pragmas to get around watcom's poor handling of partial stalls
//

/*
void set_terrain_y_int_value ( struct TERRAIN_3D_POINT_Y *point );

#pragma aux set_terrain_y_int_value =	\
	"xor	eax, eax"							\
	"mov	ax, word ptr [ edx ]"			\
	"and	eax, 0x7fff"						\
	"mov	current_terrain_y_int, eax"	\
parm [ edx ] 									\
modify exact [ eax edx ];
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_terrain_3d_point_normals;

vec3d
	terrain_3d_point_normals[256];

terrain_3d_transformed_point_normal
	terrain_3d_transformed_point_normals[256];

vec3d
	terrain_3d_face_normal;

int
	terrain_3d_face_outcode;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	terrain_3d_sector_scan_radius = 4;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int draw_default_shared_clipped_polygons ( int type_index, terrain_type_info *type, terrain_3d_sector *sector, terrain_3d_face *polygons, int polygons_left );

int draw_default_shared_unclipped_polygons ( terrain_type_info *type, terrain_3d_sector *sector, terrain_3d_face *polygons, int polygons_left );

void draw_3d_terrain_sector_point_normals ( scene_slot_drawing_list *slot );

vertex * construct_3d_terrain_normal_line ( int index, int *polygon_outcode );

static void set_terrain_3d_zbuffer_constant ( scene_slot_drawing_list *slot );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
int convert_signed_byte_vector_to_int_vector ( signed char *byte, int *integer );

#pragma aux convert_signed_byte_vector_to_int_vector =	\
	"xor	eax, eax"													\
	"mov	al, BYTE PTR [ esi ]"									\
	"xor	ebx, ebx"													\
	"shl	eax, 24"														\
	"mov	bl, BYTE PTR [ esi + 1 ]"								\
	"sar	eax, 24"														\
	"xor	ecx, ecx"													\
	"shl	ebx, 24"														\
	"mov	[ edi ], eax"												\
	"sar	ebx, 24"														\
	"mov	cl, BYTE PTR [ esi + 2 ]"								\
	"shl	ecx, 24"														\
	"mov	[ edi + 4 ], ebx"											\
	"sar	ecx, 24"														\
	"mov	[ edi + 8], ecx"											\
modify exact [ esi edi eax ebx ecx ]							\
parm [ esi ] [ edi ];
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	total_number_of_terrain_points,
	total_number_of_terrain_points_transformed,
	total_number_of_terrain_faces_inserted,
	terrain_3d_faces_considered,
	terrain_3d_faces_outcoded,
	terrain_3d_faces_hither_clipped,
	terrain_3d_faces_screen_clipped,
	terrain_3d_faces_constructed,
	terrain_3d_faces_rejected,
	terrain_3d_sectors_inserted,
	terrain_3d_sectors_totally_visible,
	terrain_3d_sectors_trivially_culled,
	terrain_3d_sectors_complex_culled,
	final_total_number_of_terrain_points,
	final_total_number_of_terrain_points_transformed,
	final_terrain_3d_faces_considered,
	final_terrain_3d_faces_outcoded,
	final_terrain_3d_faces_hither_clipped,
	final_terrain_3d_faces_screen_clipped,
	final_terrain_3d_faces_constructed,
	final_terrain_3d_faces_rejected,
	final_terrain_3d_sectors_inserted,
	final_terrain_3d_sectors_totally_visible,
	final_terrain_3d_sectors_trivially_culled,
	final_terrain_3d_sectors_complex_culled;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_terrain_3d_sector_scan_radius ( int radius )
{

	if ( radius > 20 )
	{

		debug_fatal ( "Unable to set sector scan radius above 7. Tried to set to %d", radius );
	}

	if ( radius < 0 )
	{

		debug_fatal ( "Unable to set sector scan radius below 1. Tried to set to %d", radius );
	}

	terrain_3d_sector_scan_radius = radius;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_terrain_3d_sector_scan_radius ( void )
{

	return ( terrain_3d_sector_scan_radius );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_terrain_3d_alpha ( float z )
{

	//
	// See d3dfog.c for explanation of the formula
	//

	int
		ivalue;

	asm_convert_float_to_int ( ( ( terrain_3d_alpha_constant - z ) * terrain_3d_alpha_factor ), &ivalue );

	ivalue = bound ( ivalue, 0, 255 );

	return ( ivalue );
/*	value = terrain_3d_alpha_constant - z;

	if ( *( ( int * ) &value ) < *( ( int * ) &float_value_zero ) )
	{

		return ( 0 );
	}
	else
	{

		value *= terrain_3d_alpha_factor;

		if ( *( ( int * ) &value ) > *( ( int * ) &float_value_255 ) )
		{

			return ( 255 );
		}
		else
		{

			int
				int_value;

			asm_convert_float_to_int ( value, &int_value );

			return ( int_value );
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_terrain_normals ( void )
{

	double
		heading,
		pitch;

	int
		int_heading,
		int_pitch,
		count;

	matrix3x3
		m;

	count = 0;

	for ( int_pitch = 0; int_pitch < 90; int_pitch += 9 )
	{

		pitch = ( ( ( float ) int_pitch ) / 90.0 ) * ( PI / 2 );

		for ( int_heading = 0; int_heading < 360; int_heading += 15 )
		{

			heading = ( ( ( float ) int_heading ) / 360.0 ) * ( PI * 2 );

			get_3d_transformation_matrix ( m, heading, pitch, 0 );

			terrain_3d_point_normals[count].x = m[2][0];
			terrain_3d_point_normals[count].y = m[2][1];
			terrain_3d_point_normals[count].z = m[2][2];

			count++;
		}
	}

	get_3d_transformation_matrix ( m, 0, ( PI / 2 ), 0 );

	terrain_3d_point_normals[count].x = m[2][0];
	terrain_3d_point_normals[count].y = m[2][1];
	terrain_3d_point_normals[count].z = m[2][2];

	count++;

	int_pitch = -45;

	pitch = ( ( ( float ) int_pitch ) / 90.0 ) * ( PI / 2 );

	for ( int_heading = 0; int_heading < 360; int_heading += 30 )
	{

		heading = ( ( ( float ) int_heading ) / 360.0 ) * ( PI * 2 );

		get_3d_transformation_matrix ( m, heading, pitch, 0 );

		terrain_3d_point_normals[count].x = m[2][0];
		terrain_3d_point_normals[count].y = m[2][1];
		terrain_3d_point_normals[count].z = m[2][2];

		count++;
	}

	get_3d_transformation_matrix ( m, 0, ( -PI / 2 ), 0 );

	terrain_3d_point_normals[count].x = m[2][0];
	terrain_3d_point_normals[count].y = m[2][1];
	terrain_3d_point_normals[count].z = m[2][2];

	count++;

	number_of_terrain_3d_point_normals = count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_3d_terrain ( void )
{

	int
		count,
		visual_sector_x,
		visual_sector_z,
		current_sector_x,
		current_sector_z,
		minimum_sector_x,
		minimum_sector_z,
		maximum_sector_x,
		maximum_sector_z;

	terrain_3d_sector
		*sector;

	float
		initial_sector_x_offset,
		initial_sector_z_offset,
		current_sector_x_offset,
		current_sector_z_offset;

	vec3d
		*point_normals;

	terrain_3d_transformed_point_normal
		*result_normals;

	//
	// First, set the texture blending values
	//

	set_3d_terrain_detail_blend_factors ();

	//
	// Set the rendering routines dependant on infrared mode
	//

	if ( active_3d_environment->infrared_mode == INFRARED_ON )
	{

		if ( get_3d_terrain_dual_pass_rendering () )
		{

			initialise_3d_terrain_rendering_routines ( FALSE );
		}
	}
	else
	{

		initialise_3d_terrain_rendering_routines ( get_3d_terrain_dual_pass_rendering () );
	}

	//
	// Next, light all the terrain normal vectors.
	//

	point_normals = terrain_3d_point_normals;

	result_normals = terrain_3d_transformed_point_normals;

	for ( count = 0; count < number_of_terrain_3d_point_normals; count++ )
	{

		float
			r,
			g,
			b;

		light_3d_source
			*this_light;

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

		this_light = current_3d_lights;

		while ( this_light )
		{

			if ( this_light->type == LIGHT_3D_TYPE_DIRECTIONAL )
			{
	
				float
					temp_intensity;
	
				temp_intensity = point_normals->x * this_light->lx + point_normals->y * this_light->ly + point_normals->z * this_light->lz;
	
				if ( *( ( int *) &temp_intensity ) > *( ( int *) &float_value_zero ) )
				{

					r += temp_intensity * this_light->colour.red;
					g += temp_intensity * this_light->colour.green;
					b += temp_intensity * this_light->colour.blue;
				}
			}

			this_light = this_light->succ;
		}

		if ( *( ( int *) &r ) > *( ( int *) &float_value_one ) )
		{

			r = 1.0;
		}

		if ( *( ( int *) &g ) > *( ( int *) &float_value_one ) )
		{

			g = 1.0;
		}

		if ( *( ( int *) &b ) > *( ( int *) &float_value_one ) )
		{

			b = 1.0;
		}

		result_normals->r = r;
		result_normals->g = g;
		result_normals->b = b;

		asm_convert_float_to_int ( ( r * 255.0 ), &ir );
		asm_convert_float_to_int ( ( g * 255.0 ), &ig );
		asm_convert_float_to_int ( ( b * 255.0 ), &ib );

		result_normals->colour.red = ir;
		result_normals->colour.green = ig;
		result_normals->colour.blue = ib;

		point_normals++;

		result_normals++;
	}

	//
	// Get the sector the visual_3d_vp is currently in
	//

	get_terrain_3d_sector ( visual_3d_vp->x, visual_3d_vp->z, &visual_sector_x, &visual_sector_z );

	minimum_sector_x = visual_sector_x - terrain_3d_sector_scan_radius;
	minimum_sector_z = visual_sector_z - terrain_3d_sector_scan_radius;

	maximum_sector_x = visual_sector_x + terrain_3d_sector_scan_radius;
	maximum_sector_z = visual_sector_z + terrain_3d_sector_scan_radius;

	minimum_sector_x = bound ( minimum_sector_x, 0, ( terrain_3d_sector_x_max - 1 ) );
	minimum_sector_z = bound ( minimum_sector_z, 0, ( terrain_3d_sector_z_max - 1 ) );
	maximum_sector_x = bound ( maximum_sector_x, 0, ( terrain_3d_sector_x_max - 1 ) );
	maximum_sector_z = bound ( maximum_sector_z, 0, ( terrain_3d_sector_z_max - 1 ) );

	initial_sector_x_offset = minimum_sector_x * TERRAIN_3D_SECTOR_SIDE_LENGTH;
	initial_sector_z_offset = minimum_sector_z * TERRAIN_3D_SECTOR_SIDE_LENGTH;

	current_sector_z_offset = initial_sector_z_offset;

	for ( current_sector_z = minimum_sector_z; current_sector_z <= maximum_sector_z; current_sector_z++ )
	{

		current_sector_x_offset = initial_sector_x_offset;

		for ( current_sector_x = minimum_sector_x; current_sector_x <= maximum_sector_x; current_sector_x++ )
		{

			vec3d
				sector_centre,
				sector_relative_centre;

			sector = &terrain_sectors[current_sector_z][current_sector_x];

			sector_centre.x = current_sector_x_offset + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );
			sector_centre.y = sector->average_height;
			sector_centre.z = current_sector_z_offset + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

			sector_relative_centre.x = (	( sector_centre.x - visual_3d_vp->x ) * visual_3d_vp->xv.x +
													( sector_centre.y - visual_3d_vp->y ) * visual_3d_vp->xv.y +
													( sector_centre.z - visual_3d_vp->z ) * visual_3d_vp->xv.z );

			sector_relative_centre.y = (	( sector_centre.x - visual_3d_vp->x ) * visual_3d_vp->yv.x +
													( sector_centre.y - visual_3d_vp->y ) * visual_3d_vp->yv.y +
													( sector_centre.z - visual_3d_vp->z ) * visual_3d_vp->yv.z );

			sector_relative_centre.z = (	( sector_centre.x - visual_3d_vp->x ) * visual_3d_vp->zv.x +
													( sector_centre.y - visual_3d_vp->y ) * visual_3d_vp->zv.y +
													( sector_centre.z - visual_3d_vp->z ) * visual_3d_vp->zv.z );
	
			if (	( terrain_sectors[current_sector_z][current_sector_x].number_of_points ) ||
					( ( terrain_tree_sectors ) && ( terrain_tree_sectors[current_sector_z][current_sector_x].number_of_trees ) ) )
			{
	
				//
				// Do a visibility check on the sector.
				//
	
				if ( ( sector_relative_centre.z + sector->radius ) < clip_hither )
				{
	
					terrain_3d_sectors_trivially_culled++;
				}
				else
				{
	
					unsigned int
						outcode,
						outcode1,
						outcode2;
	
					float
						x_minimum_offset,
						x_maximum_offset,
						y_minimum_offset,
						y_maximum_offset,
						z_minimum_offset,
						z_maximum_offset;
	
					x_minimum_offset = current_sector_x_offset;
					x_maximum_offset = current_sector_x_offset + TERRAIN_3D_SECTOR_SIDE_LENGTH;
	
					y_minimum_offset = ( float ) sector->minimum_height;
					y_maximum_offset = ( float ) sector->maximum_height;
	
					z_minimum_offset = current_sector_z_offset;
					z_maximum_offset = current_sector_z_offset + TERRAIN_3D_SECTOR_SIDE_LENGTH;
	
					outcode = get_3d_point_outcodes ( x_minimum_offset, y_minimum_offset, z_minimum_offset );
					outcode1 = outcode;
					outcode2 = outcode;
	
					outcode = get_3d_point_outcodes ( x_minimum_offset, y_maximum_offset, z_minimum_offset );
					outcode1 |= outcode;
					outcode2 &= outcode;
	
					outcode = get_3d_point_outcodes ( x_minimum_offset, y_minimum_offset, z_maximum_offset );
					outcode1 |= outcode;
					outcode2 &= outcode;
	
					outcode = get_3d_point_outcodes ( x_minimum_offset, y_maximum_offset, z_maximum_offset );
					outcode1 |= outcode;
					outcode2 &= outcode;
	
					outcode = get_3d_point_outcodes ( x_maximum_offset, y_minimum_offset, z_minimum_offset );
					outcode1 |= outcode;
					outcode2 &= outcode;
	
					outcode = get_3d_point_outcodes ( x_maximum_offset, y_maximum_offset, z_minimum_offset );
					outcode1 |= outcode;
					outcode2 &= outcode;
	
					outcode = get_3d_point_outcodes ( x_maximum_offset, y_minimum_offset, z_maximum_offset );
					outcode1 |= outcode;
					outcode2 &= outcode;
	
					outcode = get_3d_point_outcodes ( x_maximum_offset, y_maximum_offset, z_maximum_offset );
					outcode1 |= outcode;
					outcode2 &= outcode;

					if ( outcode2 == 0 )
					{

						scene_slot_drawing_list
							*sorting_slot;

						float
							sector_range,
							biased_z;

						if ( terrain_sectors[current_sector_z][current_sector_x].number_of_points )
						{

							//
							// Insert the actual terrain sector into the visual
							//
	
							sector_range = sqrt (	( sector_relative_centre.x * sector_relative_centre.x ) +
															( sector_relative_centre.y * sector_relative_centre.y ) +
															( sector_relative_centre.z * sector_relative_centre.z ) );
	
							biased_z = sector_relative_centre.z + ( TERRAIN_3D_SECTOR_SIDE_LENGTH * 4 );
	
							sorting_slot = get_3d_scene_slot ();
			
							if ( sorting_slot )
							{
	
								//
								// Use the integer representation of the float value
								//
	
								if ( outcode1 == 0 )
								{
		
									sorting_slot->type = OBJECT_3D_DRAW_TYPE_TERRAIN_UNCLIPPED_SECTOR;
								}
								else if ( outcode1 & ( CLIP_HITHER | CLIP_YONDER ) )
								{
		
									sorting_slot->type = OBJECT_3D_DRAW_TYPE_TERRAIN_3D_CLIPPED_SECTOR;
								}
								else
								{
		
									if ( sector_relative_centre.z < TERRAIN_3D_SECTOR_SIDE_LENGTH )
									{
		
										sorting_slot->type = OBJECT_3D_DRAW_TYPE_TERRAIN_3D_CLIPPED_SECTOR;
									}
									else
									{
		
										sorting_slot->type = OBJECT_3D_DRAW_TYPE_TERRAIN_2D_CLIPPED_SECTOR;
									}
								}
			
								sorting_slot->z = *( ( int * ) &biased_z );
			
								sorting_slot->sector.range = sector_range;
	
								sorting_slot->sector.x = current_sector_x;
			
								sorting_slot->sector.z = current_sector_z;
			
								insert_low_zbuffered_scene_slot_into_3d_scene ( sorting_slot );
							}
						}

						if (	( terrain_3d_tree_rendering_enabled ) &&
						//VJ 040206 for Craigmire: trun on trees in infrared!
								//( active_3d_environment->infrared_mode != INFRARED_ON ) &&
								( terrain_tree_sectors ) &&
								( terrain_tree_sectors[current_sector_z][current_sector_x].number_of_trees ) )
						{

							int
								tree_count;

							terrain_3d_tree_data
								*trees;

							terrain_3d_colour
								*colours;

							//
							// Insert the trees within the sectors.
							//

							trees = terrain_tree_sectors[current_sector_z][current_sector_x].trees;

							colours = terrain_sectors[current_sector_z][current_sector_x].point_colours;

							for ( tree_count = 0; tree_count < terrain_tree_sectors[current_sector_z][current_sector_x].number_of_trees; tree_count++ )
							{

								float
									x,
									y,
									z,
									dx,
									dy,
									dz,
									range;

								x = sector_centre.x;
								z = sector_centre.z;

								x += trees->x * TERRAIN_3D_XZ_SCALE / 2;
								z += trees->z * TERRAIN_3D_XZ_SCALE / 2;
								y = trees->y * terrain_3d_map_scaled_height_difference / 2 + terrain_3d_map_minimum_height;

								dx = x - visual_3d_vp->x;
								dy = y - visual_3d_vp->y;
								dz = z - visual_3d_vp->z;

								range = ( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) );

								if ( trees->type )
								{
	
									if ( range < ( 4000 * 4000 ) )
									{
		
										sorting_slot = get_3d_scene_slot ();
						
										if ( sorting_slot )
										{
	
											float
												scale;

											float
												sq_range;

											scale = get_terrain_3d_tree_scale ( trees );

											sq_range = range;

											range = sqrt ( range );
	
											sorting_slot->type = OBJECT_3D_DRAW_TYPE_TERRAIN_3D_TREE_OBJECT;
											sorting_slot->z = *( ( int * ) &range );
											sorting_slot->terrain_tree.dissolve = 255.0;	//255.0 - ( ( sq_range / ( 4000.0 * 4000.0 ) ) * 255.0 );
											sorting_slot->terrain_tree.x = x;
											sorting_slot->terrain_tree.y = y;
											sorting_slot->terrain_tree.z = z;
											sorting_slot->terrain_tree.scale = scale;
											sorting_slot->terrain_tree.colour.red = colours[trees->colour].red;
											sorting_slot->terrain_tree.colour.green = colours[trees->colour].green;
											sorting_slot->terrain_tree.colour.blue = colours[trees->colour].blue;
					
											insert_low_nonzbuffered_scene_slot_into_3d_scene ( sorting_slot );
										}
									}
								}
								else
								{
	
									if ( range < ( 1000 * 1000 ) )
									{
		
										sorting_slot = get_3d_scene_slot ();
						
										if ( sorting_slot )
										{
	
											float
												scale;
	
											scale = get_terrain_3d_tree_scale ( trees );

											range = sqrt ( range );
	
											sorting_slot->type = OBJECT_3D_DRAW_TYPE_TERRAIN_3D_TREE_OBJECT;
											sorting_slot->z = *( ( int * ) &range );
											sorting_slot->terrain_tree.dissolve = 255.0 - ( ( range / 1000.0 ) * 255.0 );
											sorting_slot->terrain_tree.x = x;
											sorting_slot->terrain_tree.y = y;
											sorting_slot->terrain_tree.z = z;
											sorting_slot->terrain_tree.scale = scale;
											sorting_slot->terrain_tree.colour.red = colours[trees->colour].red;
											sorting_slot->terrain_tree.colour.green = colours[trees->colour].green;
											sorting_slot->terrain_tree.colour.blue = colours[trees->colour].blue;
					
											insert_low_nonzbuffered_scene_slot_into_3d_scene ( sorting_slot );
										}
									}
								}

								trees++;
							}
						}
					}
					else
					{
	
						terrain_3d_sectors_complex_culled++;
					}
				}
			}

			if ( ( sector->objects ) && ( terrain_object_rendering_enabled ) )
			{
	
				terrain_3d_object
					*object;

				scene_slot_drawing_list
					*sorting_slot;

				object = sector->objects;
	
				while ( object )
				{
	
					enum OBJECT_3D_VISIBILITY
						visibility;
	
					set_object_3d_instance_relative_position ( object->object );
		
					visibility = get_object_3d_instance_visibility ( object->object );
		
					if ( visibility != OBJECT_3D_NOT_VISIBLE )
					{
	
						sorting_slot = get_3d_scene_slot ();
		
						if ( sorting_slot )
						{

							float
								biased_z;
	
							biased_z = sector_relative_centre.z + ( TERRAIN_3D_SECTOR_SIDE_LENGTH * 2 );
	
							sorting_slot->type = OBJECT_3D_DRAW_TYPE_TERRAIN_3D_OBJECT;
	
							sorting_slot->z = *( ( int * ) &biased_z );
		
							sorting_slot->object = object->object;
		
							insert_low_zbuffered_scene_slot_into_3d_scene ( sorting_slot );
						}
					}
	
					object = object->next_object;
				}
			}

			current_sector_x_offset += TERRAIN_3D_SECTOR_SIDE_LENGTH;
		}

		current_sector_z_offset += TERRAIN_3D_SECTOR_SIDE_LENGTH;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void pretouch_integer ( int *value );

#pragma aux pretouch_integer =	\
	"mov	edx, [ esi ]"				\
parm [ esi ]							\
modify exact [ edx esi];
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_tree_object ( scene_slot_drawing_list *slot )
{

	enum OBJECT_3D_VISIBILITY
		visibility;

	terrain_3d_tree_object->vp.x = slot->terrain_tree.x;
	terrain_3d_tree_object->vp.y = slot->terrain_tree.y;
	terrain_3d_tree_object->vp.z = slot->terrain_tree.z;
	terrain_3d_tree_object->requires_immediate_render = TRUE;

	terrain_3d_tree_object->relative_scale.x = slot->terrain_tree.scale;
	terrain_3d_tree_object->relative_scale.y = slot->terrain_tree.scale;
	terrain_3d_tree_object->relative_scale.z = slot->terrain_tree.scale;

	terrain_3d_tree_object->object_dissolve_value = slot->terrain_tree.dissolve;

	set_object_3d_instance_relative_position ( terrain_3d_tree_object );

	visibility = get_object_3d_instance_visibility ( terrain_3d_tree_object );

	if ( visibility != OBJECT_3D_NOT_VISIBLE )
	{

		if ( shadows_enabled )
		{

			float
				dissolve;

			int
				old_dissolve,
				idissolve;

			old_dissolve = terrain_3d_tree_object->object_dissolve_value;

			dissolve = old_dissolve;

			dissolve *= 0.650;

			convert_float_to_int ( dissolve, &idissolve );

			terrain_3d_tree_object->object_dissolve_value = idissolve;

			draw_3d_object_shadow ( terrain_3d_tree_object );

			terrain_3d_tree_object->object_dissolve_value = old_dissolve;
		}

		//
		// Recolour the lights
		//

		copy_and_recolour_current_3d_lights ( slot->terrain_tree.colour );

		draw_wbuffered_3d_object ( terrain_3d_tree_object, FALSE, TRUE );

		restore_uncoloured_current_3d_lights ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_3d_clipped_sector ( scene_slot_drawing_list *slot )
{

	int
		normal_index,
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset,
		current_sector_x_visual_offset,
		current_sector_y_visual_offset,
		current_sector_z_visual_offset,
		oxmax,
		oxmin,
		oymax,
		oymin;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	terrain_3d_face
		*polygon;

	terrain_3d_surface
		*surface;

	terrain_3d_normal_index
		*normal_indices;

	terrain_3d_colour
		*colours;

	terrain_3d_colour_index
		*colour_indices;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		tmp_vertex,
		*last_transformed_point,
		*result_2d_points;

	terrain_3d_transformed_point_colour
		*result_colours;

	unsigned char
		tmp_outcode,
		*result_outcodes,
		*last_transformed_point_outcode;

	float
		scaled_rotation[3][3];
		
	 int sz = slot->sector.z;
	 int sx = slot->sector.x;

	//
	// Set fpu precision
	//

	set_fpu_precision_mode_single ();

	terrain_3d_sectors_inserted++;

	current_terrain_sector = &terrain_sectors[slot->sector.z][slot->sector.x];

//	if ( ( current_terrain_sector->approximation ) && ( slot->sector.range > TERRAIN_SECTOR_APPROXIMATION_DISTANCE ) )
//	{
//
//		current_terrain_sector = current_terrain_sector->approximation;
//	}
//
	current_terrain_points_xz = current_terrain_sector->points_xz;

	current_terrain_points_y = current_terrain_sector->points_y;

	points_xz = current_terrain_points_xz;

	points_y = current_terrain_points_y;

//	pretouch_integer ( ( int * ) &points_xz->x );

//	pretouch_integer ( ( int * ) &points_y->whole_value );

	current_sector_x_offset = slot->sector.x * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_z_offset = slot->sector.z * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_x_visual_offset = current_sector_x_offset - visual_3d_vp->x;

	current_sector_z_visual_offset = current_sector_z_offset - visual_3d_vp->z;

	current_sector_y_visual_offset = terrain_3d_map_minimum_height - visual_3d_vp->y;

	normal_indices = current_terrain_sector->normal_changes;

	colours = current_terrain_sector->point_colours;

	colour_indices = current_terrain_sector->colour_indices;

	result_3d_points = transformed_3d_3d_points;

	result_2d_points = transformed_3d_2d_points;

	result_outcodes = transformed_3d_point_outcodes;

	result_colours = transformed_3d_point_colours;

	last_transformed_point = &tmp_vertex;

	last_transformed_point_outcode = &tmp_outcode;

	tmp_vertex.i = 0;
	tmp_vertex.j = 0;

	//
	// Initialise the first point normal index
	//

	normal_index = normal_indices->index;

	//
	// Now transform all the points.
	//

	total_number_of_terrain_points_transformed += current_terrain_sector->number_of_points;

	//
	// Set up the scaled rotation matrix
	//

	scaled_rotation[0][0] = visual_3d_vp->attitude[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = visual_3d_vp->attitude[0][1] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][2] = visual_3d_vp->attitude[0][2] * active_3d_environment->screen_i_scale;

	scaled_rotation[1][0] = visual_3d_vp->attitude[1][0] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][1] = visual_3d_vp->attitude[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = visual_3d_vp->attitude[1][2] * active_3d_environment->screen_j_scale;

	scaled_rotation[2][0] = visual_3d_vp->attitude[2][0];
	scaled_rotation[2][1] = visual_3d_vp->attitude[2][1];
	scaled_rotation[2][2] = visual_3d_vp->attitude[2][2];

	for ( count = current_terrain_sector->number_of_points; count > 0; count-- )
	{


		current_terrain_y_int = points_y->y;

//		set_terrain_y_int_value ( points_y );
		normal_indices += points_y->normal_change;	//get_3d_terrain_point_y_normal_change ( points_y );
	
		{
	
			float
				r,
				g,
				b;
	
			int
				ir,
				ig,
				ib,
				colour_index;
	
			colour_index = colour_indices->index;
			normal_index = normal_indices->index;
	
			r = colours[colour_index].red * terrain_3d_transformed_point_normals[normal_index].r + FLOAT_FLOAT_FACTOR;
			g = colours[colour_index].green * terrain_3d_transformed_point_normals[normal_index].g + FLOAT_FLOAT_FACTOR;
			b = colours[colour_index].blue * terrain_3d_transformed_point_normals[normal_index].b + FLOAT_FLOAT_FACTOR;
	
			ir = ( *( int * ) &r ) - INTEGER_FLOAT_FACTOR;
			ig = ( *( int * ) &g ) - INTEGER_FLOAT_FACTOR;
			ib = ( *( int * ) &b ) - INTEGER_FLOAT_FACTOR;
	
			result_colours->red = ir;
			result_colours->green = ig;
			result_colours->blue = ib;
			result_colours->normal_index = normal_index;
		}

		{
	
			float
				posx,
				posy,
				posz;

			posx = ( ( ( float ) points_xz->x ) * terrain_3d_xz_scale ) + current_sector_x_visual_offset;
			posz = ( ( ( float ) points_xz->z ) * terrain_3d_xz_scale ) + current_sector_z_visual_offset;
			posy =  ( ( ( float ) current_terrain_y_int ) * terrain_3d_map_scaled_height_difference ) + current_sector_y_visual_offset;
	
			result_3d_points->x = posx * scaled_rotation[0][0] + posy * scaled_rotation[0][1] + posz * scaled_rotation[0][2];
			result_3d_points->y = posx * scaled_rotation[1][0] + posy * scaled_rotation[1][1] + posz * scaled_rotation[1][2];
			result_2d_points->z = posx * scaled_rotation[2][0] + posy * scaled_rotation[2][1] + posz * scaled_rotation[2][2];
		}

		if ( *( ( int * ) &result_2d_points->z ) >= *( ( int * ) &clip_hither ) )
		{

			if ( result_2d_points->z <= clip_yonder )
			{

				float
					q,
					i,
					j;

				result_colours->fog = get_int_fog_distance_value ( result_2d_points->z );
				result_colours->alpha = get_terrain_3d_alpha ( result_2d_points->z );

				oxmax = active_viewport.x_max - last_transformed_point->i;
				oxmin = last_transformed_point->i - active_viewport.x_min;
				oymax = active_viewport.y_max - last_transformed_point->j;
				oymin = last_transformed_point->j - active_viewport.y_min;
	
				ixmax = *( ( unsigned int * ) &oxmax );
				ixmin = *( ( unsigned int * ) &oxmin );
				iymax = *( ( unsigned int * ) &oymax );
				iymin = *( ( unsigned int * ) &oymin );

#ifdef __WATCOMC__

				start_float_divide ( result_2d_points->z, 1.0 );
	
				*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
	
				q = end_float_divide ();

#else

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

#endif

				last_transformed_point = result_2d_points;

				last_transformed_point_outcode = result_outcodes;
	
				i = ( result_3d_points->x * q );
				j = ( result_3d_points->y * q );
	
				result_2d_points->j = ( active_3d_environment->y_origin - j );
				result_2d_points->i = ( active_3d_environment->x_origin + i );
				result_2d_points->q = q;
			}
			else
			{
	
				result_colours->fog = 0;
				result_colours->alpha = 0;
		
				*result_outcodes = CLIP_YONDER;
			}
		}
		else
		{

			result_colours->fog = 255;
			result_colours->alpha = 255;
	
			*result_outcodes = CLIP_HITHER;
		}

		result_3d_points++;
		result_2d_points++;
		result_outcodes++;
		result_colours++;

		points_xz++;
		points_y++;
		colour_indices++;
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
	// Reset fpu precision
	//

	set_fpu_precision_mode_double ();

	//
	// Set the cullmode ( terrain isn't culled in software )
	//

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	//
	// Set the rendering states for the terrain polygons
	//

	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, terrain_texture_mag_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, terrain_texture_min_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, terrain_texture_mip_filter );

#if ALLOW_TERRAIN_TEXTURES
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
#else
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
#endif

	//
	// Go through the polys in sector, and drawing them
	//

	polygon = current_terrain_sector->polygons;

	surface = current_terrain_sector->surface_changes;

	terrain_3d_faces_considered += current_terrain_sector->number_of_polygons;

	current_terrain_type = surface->surface_id;

	current_terrain_type_class = &terrain_type_information[current_terrain_type];

	reset_terrain_3d_buffered_polygons ();

	reset_deferred_state_changes ();

	set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );

	//
	// Set the zdistance bias level
	//

	set_terrain_3d_zbuffer_constant ( slot );

	if ( current_terrain_sector->number_of_points < 257 )
	{
	
		terrain_3d_sector_point_byte_references = current_terrain_sector->point_byte_references;
	
		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;

			 if ( polygon->surface_change || customtype[sz][sx][count].flag == 1)
			{
				
				if ( polygon->surface_change )
					surface++;

				current_terrain_type = surface->surface_id;
	
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				if (customtype[sz][sx][count].flag == 1)  
				{
			/*		current_terrain_type_class->texture = system_textures[customtype[sz][sx][count].id];    Maverick fix the strange lighting effects in winter mode and bad weather
					current_terrain_type_class->texture2 = system_textures[customtype[sz][sx][count].id];   
			*/	}	
              
				//  
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				reset_deferred_state_changes ();

				set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			{
		
				if ( outcode_3d_terrain_byte_polygon ( number_of_points, terrain_3d_sector_point_byte_references, &terrain_3d_face_outcode ) )
				{
		
					commit_deferred_state_changes ();

					if ( terrain_3d_face_outcode )
					{
	
						current_terrain_type_class->render_byte_clipped ( number_of_points );
					}
					else
					{
	
						current_terrain_type_class->render_byte_unclipped ( number_of_points );
					}
				}
		
				terrain_3d_sector_point_byte_references += number_of_points;
		
				polygon++;
			}
		}
	}
	else
	{
	
		terrain_3d_sector_point_word_references = current_terrain_sector->point_word_references;
	
		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;

			if ( polygon->surface_change  || customtype[sz][sx][count].flag == 1)
			{
				
				if ( polygon->surface_change )
					surface++;

				current_terrain_type = surface->surface_id;
	
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				if (customtype[sz][sx][count].flag == 1) 
				{
					current_terrain_type_class->texture = system_textures[customtype[sz][sx][count].id];
					current_terrain_type_class->texture2 = system_textures[customtype[sz][sx][count].id];
				}	

				// 
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				reset_deferred_state_changes ();

				set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			{
		
				if ( outcode_3d_terrain_word_polygon ( number_of_points, terrain_3d_sector_point_word_references, &terrain_3d_face_outcode ) )
				{
		
					commit_deferred_state_changes ();

					if ( terrain_3d_face_outcode )
					{
	
						current_terrain_type_class->render_word_clipped ( number_of_points );
					}
					else
					{
	
						current_terrain_type_class->render_word_unclipped ( number_of_points );
					}
				}
		
				terrain_3d_sector_point_word_references += number_of_points;
		
				polygon++;
			}
		}
	}

	zbuffer_constant = zbuffer_constant_normal_bias;

	//
	// Flush any buffered polygons
	//

	draw_terrain_3d_buffered_polygons ();

#ifdef RENDER_TERRAIN_POINT_NORMALS

	//
	// Render the point normals
	//

	suspend_d3d_fog ();

	draw_3d_terrain_sector_point_normals ( slot );

	reinstate_d3d_fog ();

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_2d_clipped_sector ( scene_slot_drawing_list *slot )
{

	int
		normal_index,
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset,
		current_sector_x_visual_offset,
		current_sector_y_visual_offset,
		current_sector_z_visual_offset,
		oxmax,
		oxmin,
		oymax,
		oymin;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	terrain_3d_face
		*polygon;

	terrain_3d_surface
		*surface;

	terrain_3d_normal_index
		*normal_indices;

	terrain_3d_colour
		*colours;

	terrain_3d_colour_index
		*colour_indices;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		tmp_vertex,
		*last_transformed_point,
		*result_2d_points;

	terrain_3d_transformed_point_colour
		*result_colours;

	unsigned char
		tmp_outcode,
		*result_outcodes,
		*last_transformed_point_outcode;

	float
		scaled_rotation[3][3];
		
	int sz = slot->sector.z;
	int sx = slot->sector.x;		

	//
	// Set fpu precision
	//

	set_fpu_precision_mode_single ();

	terrain_3d_sectors_inserted++;

	current_terrain_sector = &terrain_sectors[slot->sector.z][slot->sector.x];

//	if ( ( current_terrain_sector->approximation ) && ( slot->sector.range > TERRAIN_SECTOR_APPROXIMATION_DISTANCE ) )
//	{
//
//		current_terrain_sector = current_terrain_sector->approximation;
//	}

	current_terrain_points_xz = current_terrain_sector->points_xz;

	current_terrain_points_y = current_terrain_sector->points_y;

	points_xz = current_terrain_points_xz;

	points_y = current_terrain_points_y;

//	pretouch_integer ( ( int * ) &points_xz->x );

//	pretouch_integer ( ( int * ) &points_y->whole_value );

	current_sector_x_offset = slot->sector.x * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_z_offset = slot->sector.z * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_x_visual_offset = current_sector_x_offset - visual_3d_vp->x;

	current_sector_z_visual_offset = current_sector_z_offset - visual_3d_vp->z;

	current_sector_y_visual_offset = terrain_3d_map_minimum_height - visual_3d_vp->y;

	normal_indices = current_terrain_sector->normal_changes;

	colours = current_terrain_sector->point_colours;

	colour_indices = current_terrain_sector->colour_indices;

	result_3d_points = transformed_3d_3d_points;

	result_2d_points = transformed_3d_2d_points;

	result_outcodes = transformed_3d_point_outcodes;

	result_colours = transformed_3d_point_colours;

	last_transformed_point = &tmp_vertex;

	last_transformed_point_outcode = &tmp_outcode;

	tmp_vertex.i = 0;
	tmp_vertex.j = 0;

	//
	// Initialise the first point normal index
	//

	normal_index = normal_indices->index;

	//
	// Now transform all the points.
	//

	total_number_of_terrain_points_transformed += current_terrain_sector->number_of_points;

	//
	// Set up the scaled rotation matrix
	//

	scaled_rotation[0][0] = visual_3d_vp->attitude[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = visual_3d_vp->attitude[0][1] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][2] = visual_3d_vp->attitude[0][2] * active_3d_environment->screen_i_scale;

	scaled_rotation[1][0] = visual_3d_vp->attitude[1][0] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][1] = visual_3d_vp->attitude[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = visual_3d_vp->attitude[1][2] * active_3d_environment->screen_j_scale;

	scaled_rotation[2][0] = visual_3d_vp->attitude[2][0];
	scaled_rotation[2][1] = visual_3d_vp->attitude[2][1];
	scaled_rotation[2][2] = visual_3d_vp->attitude[2][2];

	for ( count = current_terrain_sector->number_of_points; count > 0; count-- )
	{

		float
			posx,
			posy,
			posz,
			r,
			g,
			b;

		int
			ir,
			ig,
			ib,
			colour_index;

		//
		// Read in all the memory variables
		//

		current_terrain_y_int = points_y->y;

//		set_terrain_y_int_value ( points_y );

		colour_index = colour_indices->index;

		r = colours[colour_index].red;
		g = colours[colour_index].green;
		b = colours[colour_index].blue;

		posx = ( ( ( float ) points_xz->x ) * terrain_3d_xz_scale ) + current_sector_x_visual_offset;
		posz = ( ( ( float ) points_xz->z ) * terrain_3d_xz_scale ) + current_sector_z_visual_offset;
		posy =  ( ( ( float ) current_terrain_y_int ) * terrain_3d_map_scaled_height_difference ) + current_sector_y_visual_offset;

		result_3d_points->x = posx * scaled_rotation[0][0] + posy * scaled_rotation[0][1] + posz * scaled_rotation[0][2];
		result_3d_points->y = posx * scaled_rotation[1][0] + posy * scaled_rotation[1][1] + posz * scaled_rotation[1][2];
		result_2d_points->z = posx * scaled_rotation[2][0] + posy * scaled_rotation[2][1] + posz * scaled_rotation[2][2];

		normal_indices += points_y->normal_change;	//get_3d_terrain_point_y_normal_change ( points_y );

		normal_index = normal_indices->index;

		r = ( r * terrain_3d_transformed_point_normals[normal_index].r ) + FLOAT_FLOAT_FACTOR;
		g = ( g * terrain_3d_transformed_point_normals[normal_index].g ) + FLOAT_FLOAT_FACTOR;
		b = ( b * terrain_3d_transformed_point_normals[normal_index].b ) + FLOAT_FLOAT_FACTOR;

		ir = ( *( int * ) &r ) - INTEGER_FLOAT_FACTOR;
		ig = ( *( int * ) &g ) - INTEGER_FLOAT_FACTOR;
		ib = ( *( int * ) &b ) - INTEGER_FLOAT_FACTOR;

		result_colours->red = ir;
		result_colours->green = ig;
		result_colours->blue = ib;
		result_colours->normal_index = normal_index;

		result_colours->fog = get_int_fog_distance_value ( result_2d_points->z );
		result_colours->alpha = get_terrain_3d_alpha ( result_2d_points->z );

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

#ifdef __WATCOMC__

			start_float_divide ( result_2d_points->z, 1.0 );

			*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			q = end_float_divide ();

#else

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

#endif

			last_transformed_point = result_2d_points;
			last_transformed_point_outcode = result_outcodes;

			i = ( result_3d_points->x * q );
			j = ( result_3d_points->y * q );

			result_2d_points->j = ( active_3d_environment->y_origin - j );
			result_2d_points->i = ( active_3d_environment->x_origin + i );
			result_2d_points->q = q;
		}

		result_3d_points++;
		result_2d_points++;
		result_outcodes++;
		result_colours++;

		points_xz++;
		points_y++;
		colour_indices++;
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
	// Reset fpu precision
	//

	set_fpu_precision_mode_double ();

	//
	// Set the cullmode ( terrain isn't culled in software )
	//

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	//
	// Set the rendering states for the terrain polygons
	//

	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, terrain_texture_mag_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, terrain_texture_min_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, terrain_texture_mip_filter );
#if ALLOW_TERRAIN_TEXTURES
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
#else
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
#endif

	//
	// Go through the polys in sector, backface culling them, and drawing them
	//

	polygon = current_terrain_sector->polygons;

	surface = current_terrain_sector->surface_changes;

	terrain_3d_faces_considered += current_terrain_sector->number_of_polygons;

	current_terrain_type = surface->surface_id;

	current_terrain_type_class = &terrain_type_information[current_terrain_type];

	reset_terrain_3d_buffered_polygons ();

	reset_deferred_state_changes ();

	set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );

	set_terrain_3d_zbuffer_constant ( slot );

	if ( current_terrain_sector->number_of_points < 257 )
	{
	
		terrain_3d_sector_point_byte_references = current_terrain_sector->point_byte_references;
	
		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;

			if ( polygon->surface_change || customtype[sz][sx][count].flag == 1)
			{
				
				if ( polygon->surface_change )
					surface++;

				current_terrain_type = surface->surface_id;
	
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				if (customtype[sz][sx][count].flag == 1)
				{
					current_terrain_type_class->texture = system_textures[customtype[sz][sx][count].id];
					current_terrain_type_class->texture2 = system_textures[customtype[sz][sx][count].id];
				}	

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				reset_deferred_state_changes ();

				set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			{
		
				if ( outcode_3d_terrain_byte_polygon ( number_of_points, terrain_3d_sector_point_byte_references, &terrain_3d_face_outcode ) )
				{
		
					commit_deferred_state_changes ();

					if ( terrain_3d_face_outcode )
					{
	
						current_terrain_type_class->render_byte_clipped ( number_of_points );
					}
					else
					{
	
						current_terrain_type_class->render_byte_unclipped ( number_of_points );
					}
				}
		
				terrain_3d_sector_point_byte_references += number_of_points;
		
				polygon++;
			}
		}
	}
	else
	{
	
		terrain_3d_sector_point_word_references = current_terrain_sector->point_word_references;
	
		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;

			if ( polygon->surface_change || customtype[sz][sx][count].flag == 1)
			{
				
				if ( polygon->surface_change )
					surface++;

				current_terrain_type = surface->surface_id;
	
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				if (customtype[sz][sx][count].flag == 1)
				{
					current_terrain_type_class->texture = system_textures[customtype[sz][sx][count].id];
					current_terrain_type_class->texture2 = system_textures[customtype[sz][sx][count].id];
				}	

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				reset_deferred_state_changes ();

				set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			{
		
				if ( outcode_3d_terrain_word_polygon ( number_of_points, terrain_3d_sector_point_word_references, &terrain_3d_face_outcode ) )
				{
		
					commit_deferred_state_changes ();

					if ( terrain_3d_face_outcode )
					{
	
						current_terrain_type_class->render_word_clipped ( number_of_points );
					}
					else
					{
	
						current_terrain_type_class->render_word_unclipped ( number_of_points );
					}
				}
		
				terrain_3d_sector_point_word_references += number_of_points;
		
				polygon++;
			}
		}
	}

	zbuffer_constant = zbuffer_constant_normal_bias;

	//
	// Flush any buffered polygons
	//

	draw_terrain_3d_buffered_polygons ();

#ifdef RENDER_TERRAIN_POINT_NORMALS

	//
	// Render the point normals
	//

	suspend_d3d_fog ();

	draw_3d_terrain_sector_point_normals ( slot );

	reinstate_d3d_fog ();

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_unclipped_sector ( scene_slot_drawing_list *slot )
{

	int
		normal_index,
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset,
		current_sector_x_visual_offset,
		current_sector_y_visual_offset,
		current_sector_z_visual_offset;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	terrain_3d_face
		*polygon;

	terrain_3d_surface
		*surface;

	terrain_3d_normal_index
		*normal_indices;

	terrain_3d_colour
		*colours;

	terrain_3d_colour_index
		*colour_indices;

	object_transformed_2d_point
		*result_2d_points;

	terrain_3d_transformed_point_colour
		*result_colours;

	float
		scaled_rotation[3][3];

	int sz = slot->sector.z;
	int sx = slot->sector.x;

	//
	// Set fpu precision
	//

	set_fpu_precision_mode_single ();

	terrain_3d_sectors_inserted++;

	terrain_3d_sectors_totally_visible++;

	current_terrain_sector = &terrain_sectors[slot->sector.z][slot->sector.x];

//	if ( ( current_terrain_sector->approximation ) && ( slot->sector.range > TERRAIN_SECTOR_APPROXIMATION_DISTANCE ) )
//	{
//
//		current_terrain_sector = current_terrain_sector->approximation;
//	}

	current_terrain_points_xz = current_terrain_sector->points_xz;

	current_terrain_points_y = current_terrain_sector->points_y;

	points_xz = current_terrain_points_xz;

	points_y = current_terrain_points_y;

//	pretouch_integer ( ( int * ) &points_xz->x );

//	pretouch_integer ( ( int * ) &points_y->whole_value );

	current_sector_x_offset = slot->sector.x * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_z_offset = slot->sector.z * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_x_visual_offset = current_sector_x_offset - visual_3d_vp->x;

	current_sector_z_visual_offset = current_sector_z_offset - visual_3d_vp->z;

	current_sector_y_visual_offset = terrain_3d_map_minimum_height - visual_3d_vp->y;

	colours = current_terrain_sector->point_colours;

	colour_indices = current_terrain_sector->colour_indices;

	normal_indices = current_terrain_sector->normal_changes;

	result_2d_points = transformed_3d_2d_points;

	result_colours = transformed_3d_point_colours;

	//
	// Now transform all the points. Have rgb & ramp solutions though.
	//

	total_number_of_terrain_points_transformed += current_terrain_sector->number_of_points;

	normal_index = normal_indices->index;

	//
	// Set up the scaled rotation matrix
	//

	scaled_rotation[0][0] = visual_3d_vp->attitude[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = visual_3d_vp->attitude[0][1] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][2] = visual_3d_vp->attitude[0][2] * active_3d_environment->screen_i_scale;

	scaled_rotation[1][0] = visual_3d_vp->attitude[1][0] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][1] = visual_3d_vp->attitude[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = visual_3d_vp->attitude[1][2] * active_3d_environment->screen_j_scale;

	scaled_rotation[2][0] = visual_3d_vp->attitude[2][0];
	scaled_rotation[2][1] = visual_3d_vp->attitude[2][1];
	scaled_rotation[2][2] = visual_3d_vp->attitude[2][2];

	for ( count = current_terrain_sector->number_of_points; count > 0; count-- )
	{

		float
			posx,
			posy,
			posz,
			x,
			y,
			q,
			i,
			j,
			r,
			g,
			b;

		int
			ir,
			ig,
			ib,
			colour_index;

		current_terrain_y_int = points_y->y;

//		set_terrain_y_int_value ( points_y );

		if ( points_y->normal_change )
		{

			normal_indices++;

			normal_index = normal_indices->index;
		}

		posx = ( ( ( float ) points_xz->x ) * terrain_3d_xz_scale ) + current_sector_x_visual_offset;
		posz = ( ( ( float ) points_xz->z ) * terrain_3d_xz_scale ) + current_sector_z_visual_offset;
		posy =  ( ( ( float ) current_terrain_y_int ) * terrain_3d_map_scaled_height_difference ) + current_sector_y_visual_offset;

		x = posx * scaled_rotation[0][0] + posy * scaled_rotation[0][1] + posz * scaled_rotation[0][2];
		y = posx * scaled_rotation[1][0] + posy * scaled_rotation[1][1] + posz * scaled_rotation[1][2];
		result_2d_points->z = posx * scaled_rotation[2][0] + posy * scaled_rotation[2][1] + posz * scaled_rotation[2][2];

		colour_index = colour_indices->index;

		r = colours[colour_index].red;
		g = colours[colour_index].green;
		b = colours[colour_index].blue;

		asm_convert_float_to_int ( ( r * terrain_3d_transformed_point_normals[normal_index].r ), &ir );
		asm_convert_float_to_int ( ( g * terrain_3d_transformed_point_normals[normal_index].g ), &ig );
		asm_convert_float_to_int ( ( b * terrain_3d_transformed_point_normals[normal_index].b ), &ib );

		result_colours->red = ir;
		result_colours->green = ig;
		result_colours->blue = ib;
		result_colours->normal_index = normal_index;

		result_colours->fog = get_int_fog_distance_value ( result_2d_points->z );
		result_colours->alpha = get_terrain_3d_alpha ( result_2d_points->z );

		q = 1.0 / result_2d_points->z;

		i = ( x * q );
		j = ( y * q );

		result_2d_points->j = ( active_3d_environment->y_origin - j );
		result_2d_points->i = ( active_3d_environment->x_origin + i );
		result_2d_points->q = q;

		result_2d_points++;
		result_colours++;

		points_xz++;
		points_y++;
		colour_indices++;
	}

	//
	// Reset fpu precision
	//

	set_fpu_precision_mode_double ();

	//
	// Set the cullmode ( terrain isn't culled in software )
	//

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	//
	// Set the rendering states for the terrain polygons
	//

	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, terrain_texture_mag_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, terrain_texture_min_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, terrain_texture_mip_filter );
#if ALLOW_TERRAIN_TEXTURES
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
#else
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
#endif

	//
	// Go through the polys in sector, backface culling them, and drawing them
	//

	terrain_3d_faces_considered += current_terrain_sector->number_of_polygons;

	polygon = current_terrain_sector->polygons;

	surface = current_terrain_sector->surface_changes;

	current_terrain_type = surface->surface_id;

	current_terrain_type_class = &terrain_type_information[current_terrain_type];

	reset_terrain_3d_buffered_polygons ();

	set_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );

	set_terrain_3d_zbuffer_constant ( slot );

	if ( current_terrain_sector->number_of_points < 257 )
	{
		
		terrain_3d_sector_point_byte_references = current_terrain_sector->point_byte_references;

		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;
	
			if ( polygon->surface_change || customtype[sz][sx][count].flag == 1)
			{
				
				if ( polygon->surface_change )
					surface++;

				current_terrain_type = surface->surface_id;
	
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				if (customtype[sz][sx][count].flag == 1)
				{
					current_terrain_type_class->texture = system_textures[customtype[sz][sx][count].id];
					current_terrain_type_class->texture2 = system_textures[customtype[sz][sx][count].id];
				}	

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				set_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );

			current_terrain_type_class->render_byte_unclipped ( number_of_points );
	
			terrain_3d_sector_point_byte_references += number_of_points;
	
			polygon++;
		}
	}
	else
	{		

		terrain_3d_sector_point_word_references = current_terrain_sector->point_word_references;

		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int 
				number_of_points;
				
			if ( polygon->surface_change || customtype[sz][sx][count].flag == 1)
			{
				
				if ( polygon->surface_change )
					surface++;

				current_terrain_type = surface->surface_id;
	
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				if (customtype[sz][sx][count].flag == 1)
				{
					current_terrain_type_class->texture = system_textures[customtype[sz][sx][count].id];
					current_terrain_type_class->texture2 = system_textures[customtype[sz][sx][count].id];
				}	

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				set_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );

			current_terrain_type_class->render_word_unclipped ( number_of_points );
	
			terrain_3d_sector_point_word_references += number_of_points;
	
			polygon++;
		}
	}

	zbuffer_constant = zbuffer_constant_normal_bias;

	//
	// Flush any buffered polygons
	//

	draw_terrain_3d_buffered_polygons ();

#ifdef RENDER_TERRAIN_POINT_NORMALS

	//
	// Render the point normals
	//

	suspend_d3d_fog ();

	draw_3d_terrain_sector_point_normals ( slot );

	reinstate_d3d_fog ();

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_3d_clipped_bw_sector ( scene_slot_drawing_list *slot )
{

	int
		normal_index,
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset,
		current_sector_x_visual_offset,
		current_sector_y_visual_offset,
		current_sector_z_visual_offset,
		oxmax,
		oxmin,
		oymax,
		oymin;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	terrain_3d_face
		*polygon;

	terrain_3d_surface
		*surface;

	terrain_3d_normal_index
		*normal_indices;

	terrain_3d_colour
		*colours;

	terrain_3d_colour_index
		*colour_indices;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		tmp_vertex,
		*last_transformed_point,
		*result_2d_points;

	terrain_3d_transformed_point_colour
		*result_colours;

	unsigned char
		tmp_outcode,
		*result_outcodes,
		*last_transformed_point_outcode;

	float
		scaled_rotation[3][3];

	//
	// Set fpu precision
	//

	set_fpu_precision_mode_single ();

	terrain_3d_sectors_inserted++;

	current_terrain_sector = &terrain_sectors[slot->sector.z][slot->sector.x];

//	if ( ( current_terrain_sector->approximation ) && ( slot->sector.range > TERRAIN_SECTOR_APPROXIMATION_DISTANCE ) )
//	{
//
//		current_terrain_sector = current_terrain_sector->approximation;
//	}
//
	current_terrain_points_xz = current_terrain_sector->points_xz;

	current_terrain_points_y = current_terrain_sector->points_y;

	points_xz = current_terrain_points_xz;

	points_y = current_terrain_points_y;

//	pretouch_integer ( ( int * ) &points_xz->x );

//	pretouch_integer ( ( int * ) &points_y->whole_value );

	current_sector_x_offset = slot->sector.x * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_z_offset = slot->sector.z * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_x_visual_offset = current_sector_x_offset - visual_3d_vp->x;

	current_sector_z_visual_offset = current_sector_z_offset - visual_3d_vp->z;

	current_sector_y_visual_offset = terrain_3d_map_minimum_height - visual_3d_vp->y;

	normal_indices = current_terrain_sector->normal_changes;

	colours = current_terrain_sector->point_colours;

	colour_indices = current_terrain_sector->colour_indices;

	result_3d_points = transformed_3d_3d_points;

	result_2d_points = transformed_3d_2d_points;

	result_outcodes = transformed_3d_point_outcodes;

	result_colours = transformed_3d_point_colours;

	last_transformed_point = &tmp_vertex;

	last_transformed_point_outcode = &tmp_outcode;

	tmp_vertex.i = 0;
	tmp_vertex.j = 0;

	//
	// Initialise the first point normal index
	//

	normal_index = normal_indices->index;

	//
	// Now transform all the points.
	//

	total_number_of_terrain_points_transformed += current_terrain_sector->number_of_points;

	//
	// Set up the scaled rotation matrix
	//

	scaled_rotation[0][0] = visual_3d_vp->attitude[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = visual_3d_vp->attitude[0][1] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][2] = visual_3d_vp->attitude[0][2] * active_3d_environment->screen_i_scale;

	scaled_rotation[1][0] = visual_3d_vp->attitude[1][0] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][1] = visual_3d_vp->attitude[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = visual_3d_vp->attitude[1][2] * active_3d_environment->screen_j_scale;

	scaled_rotation[2][0] = visual_3d_vp->attitude[2][0];
	scaled_rotation[2][1] = visual_3d_vp->attitude[2][1];
	scaled_rotation[2][2] = visual_3d_vp->attitude[2][2];

	for ( count = current_terrain_sector->number_of_points; count > 0; count-- )
	{


		current_terrain_y_int = points_y->y;

//		set_terrain_y_int_value ( points_y );
		normal_indices += points_y->normal_change;	//get_3d_terrain_point_y_normal_change ( points_y );
	
		{
	
			float
				r,
				g,
				b,
				grey;
	
			int
				ir,
				ig,
				ib,
				colour_index;
	
			colour_index = colour_indices->index;
			normal_index = normal_indices->index;

			r = colours[colour_index].red;
			g = colours[colour_index].green;
			b = colours[colour_index].blue;

			r *= 0.3;
			g *= 0.59;
			b *= 0.11;

			grey = r * 0.3 + g * 0.59 + b * 0.11;
	
			r = grey * terrain_3d_transformed_point_normals[normal_index].r;
			g = grey * terrain_3d_transformed_point_normals[normal_index].g;
			b = grey * terrain_3d_transformed_point_normals[normal_index].b;
	
			asm_convert_float_to_int ( r, &ir );
			asm_convert_float_to_int ( g, &ig );
			asm_convert_float_to_int ( b, &ib );
	
			result_colours->red = ir;
			result_colours->green = ig;
			result_colours->blue = ib;
			result_colours->normal_index = normal_index;
		}

		{
	
			float
				posx,
				posy,
				posz;

			posx = ( ( ( float ) points_xz->x ) * terrain_3d_xz_scale ) + current_sector_x_visual_offset;
			posz = ( ( ( float ) points_xz->z ) * terrain_3d_xz_scale ) + current_sector_z_visual_offset;
			posy =  ( ( ( float ) current_terrain_y_int ) * terrain_3d_map_scaled_height_difference ) + current_sector_y_visual_offset;
	
			result_3d_points->x = posx * scaled_rotation[0][0] + posy * scaled_rotation[0][1] + posz * scaled_rotation[0][2];
			result_3d_points->y = posx * scaled_rotation[1][0] + posy * scaled_rotation[1][1] + posz * scaled_rotation[1][2];
			result_2d_points->z = posx * scaled_rotation[2][0] + posy * scaled_rotation[2][1] + posz * scaled_rotation[2][2];
		}

		if ( *( ( int * ) &result_2d_points->z ) >= *( ( int * ) &clip_hither ) )
		{

			if ( result_2d_points->z <= clip_yonder )
			{

				float
					q,
					i,
					j;

				result_colours->fog = get_int_fog_distance_value ( result_2d_points->z );
				result_colours->alpha = get_terrain_3d_alpha ( result_2d_points->z );

				oxmax = active_viewport.x_max - last_transformed_point->i;
				oxmin = last_transformed_point->i - active_viewport.x_min;
				oymax = active_viewport.y_max - last_transformed_point->j;
				oymin = last_transformed_point->j - active_viewport.y_min;
	
				ixmax = *( ( unsigned int * ) &oxmax );
				ixmin = *( ( unsigned int * ) &oxmin );
				iymax = *( ( unsigned int * ) &oymax );
				iymin = *( ( unsigned int * ) &oymin );

#ifdef __WATCOMC__

				start_float_divide ( result_2d_points->z, 1.0 );
	
				*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
	
				q = end_float_divide ();

#else

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

#endif

				last_transformed_point = result_2d_points;

				last_transformed_point_outcode = result_outcodes;
	
				i = ( result_3d_points->x * q );
				j = ( result_3d_points->y * q );
	
				result_2d_points->j = ( active_3d_environment->y_origin - j );
				result_2d_points->i = ( active_3d_environment->x_origin + i );
				result_2d_points->q = q;
			}
			else
			{
	
				result_colours->fog = 0;
				result_colours->alpha = 0;
		
				*result_outcodes = CLIP_YONDER;
			}
		}
		else
		{

			result_colours->fog = 255;
			result_colours->alpha = 255;
	
			*result_outcodes = CLIP_HITHER;
		}

		result_3d_points++;
		result_2d_points++;
		result_outcodes++;
		result_colours++;

		points_xz++;
		points_y++;
		colour_indices++;
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
	// Reset fpu precision
	//

	set_fpu_precision_mode_double ();

	//
	// Set the cullmode ( terrain isn't culled in software )
	//

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	//
	// Set the rendering states for the terrain polygons
	//

	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, terrain_texture_mag_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, terrain_texture_min_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, terrain_texture_mip_filter );

#if ALLOW_TERRAIN_TEXTURES
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
#else
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
#endif

	//
	// Go through the polys in sector, and drawing them
	//

	polygon = current_terrain_sector->polygons;

	surface = current_terrain_sector->surface_changes;

	terrain_3d_faces_considered += current_terrain_sector->number_of_polygons;

	current_terrain_type = surface->surface_id;

	current_terrain_type_class = &terrain_type_information[current_terrain_type];

	reset_terrain_3d_buffered_polygons ();

	reset_deferred_state_changes ();

	set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );

	set_terrain_3d_zbuffer_constant ( slot );

	if ( current_terrain_sector->number_of_points < 257 )
	{
	
		terrain_3d_sector_point_byte_references = current_terrain_sector->point_byte_references;
	
		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;

		 	if ( polygon->surface_change ) //get_3d_terrain_face_surface_change ( polygon ) )
			{

				surface++;

				current_terrain_type = surface->surface_id;
	
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				reset_deferred_state_changes ();

				set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			{
		
				if ( outcode_3d_terrain_byte_polygon ( number_of_points, terrain_3d_sector_point_byte_references, &terrain_3d_face_outcode ) )
				{
		
					commit_deferred_state_changes ();

					if ( terrain_3d_face_outcode )
					{
	
						current_terrain_type_class->render_byte_clipped ( number_of_points );
					}
					else
					{
	
						current_terrain_type_class->render_byte_unclipped ( number_of_points );
					}
				}
		
				terrain_3d_sector_point_byte_references += number_of_points;
		
				polygon++;
			}
		}
	}
	else
	{
	
		terrain_3d_sector_point_word_references = current_terrain_sector->point_word_references;
	
		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;
	
			if ( polygon->surface_change ) //get_3d_terrain_face_surface_change ( polygon ) )
			{

				surface++;

				current_terrain_type = surface->surface_id;
		
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				draw_terrain_3d_buffered_polygons ();

				reset_deferred_state_changes ();

				set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			{
		
				if ( outcode_3d_terrain_word_polygon ( number_of_points, terrain_3d_sector_point_word_references, &terrain_3d_face_outcode ) )
				{
		
					commit_deferred_state_changes ();

					if ( terrain_3d_face_outcode )
					{
	
						current_terrain_type_class->render_word_clipped ( number_of_points );
					}
					else
					{
	
						current_terrain_type_class->render_word_unclipped ( number_of_points );
					}
				}
		
				terrain_3d_sector_point_word_references += number_of_points;
		
				polygon++;
			}
		}
	}

	zbuffer_constant = zbuffer_constant_normal_bias;

	//
	// Flush any buffered polygons
	//

	draw_terrain_3d_buffered_polygons ();

#ifdef RENDER_TERRAIN_POINT_NORMALS

	//
	// Render the point normals
	//

	suspend_d3d_fog ();

	draw_3d_terrain_sector_point_normals ( slot );

	reinstate_d3d_fog ();

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_2d_clipped_bw_sector ( scene_slot_drawing_list *slot )
{

	int
		normal_index,
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset,
		current_sector_x_visual_offset,
		current_sector_y_visual_offset,
		current_sector_z_visual_offset,
		oxmax,
		oxmin,
		oymax,
		oymin;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	terrain_3d_face
		*polygon;

	terrain_3d_surface
		*surface;

	terrain_3d_normal_index
		*normal_indices;

	terrain_3d_colour
		*colours;

	terrain_3d_colour_index
		*colour_indices;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		tmp_vertex,
		*last_transformed_point,
		*result_2d_points;

	terrain_3d_transformed_point_colour
		*result_colours;

	unsigned char
		tmp_outcode,
		*result_outcodes,
		*last_transformed_point_outcode;

	float
		scaled_rotation[3][3];

	//
	// Set fpu precision
	//

	set_fpu_precision_mode_single ();

	terrain_3d_sectors_inserted++;

	current_terrain_sector = &terrain_sectors[slot->sector.z][slot->sector.x];

//	if ( ( current_terrain_sector->approximation ) && ( slot->sector.range > TERRAIN_SECTOR_APPROXIMATION_DISTANCE ) )
//	{
//
//		current_terrain_sector = current_terrain_sector->approximation;
//	}

	current_terrain_points_xz = current_terrain_sector->points_xz;

	current_terrain_points_y = current_terrain_sector->points_y;

	points_xz = current_terrain_points_xz;

	points_y = current_terrain_points_y;

//	pretouch_integer ( ( int * ) &points_xz->x );

//	pretouch_integer ( ( int * ) &points_y->whole_value );

	current_sector_x_offset = slot->sector.x * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_z_offset = slot->sector.z * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_x_visual_offset = current_sector_x_offset - visual_3d_vp->x;

	current_sector_z_visual_offset = current_sector_z_offset - visual_3d_vp->z;

	current_sector_y_visual_offset = terrain_3d_map_minimum_height - visual_3d_vp->y;

	normal_indices = current_terrain_sector->normal_changes;

	colours = current_terrain_sector->point_colours;

	colour_indices = current_terrain_sector->colour_indices;

	result_3d_points = transformed_3d_3d_points;

	result_2d_points = transformed_3d_2d_points;

	result_outcodes = transformed_3d_point_outcodes;

	result_colours = transformed_3d_point_colours;

	last_transformed_point = &tmp_vertex;

	last_transformed_point_outcode = &tmp_outcode;

	tmp_vertex.i = 0;
	tmp_vertex.j = 0;

	//
	// Initialise the first point normal index
	//

	normal_index = normal_indices->index;

	//
	// Now transform all the points.
	//

	total_number_of_terrain_points_transformed += current_terrain_sector->number_of_points;

	//
	// Set up the scaled rotation matrix
	//

	scaled_rotation[0][0] = visual_3d_vp->attitude[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = visual_3d_vp->attitude[0][1] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][2] = visual_3d_vp->attitude[0][2] * active_3d_environment->screen_i_scale;

	scaled_rotation[1][0] = visual_3d_vp->attitude[1][0] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][1] = visual_3d_vp->attitude[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = visual_3d_vp->attitude[1][2] * active_3d_environment->screen_j_scale;

	scaled_rotation[2][0] = visual_3d_vp->attitude[2][0];
	scaled_rotation[2][1] = visual_3d_vp->attitude[2][1];
	scaled_rotation[2][2] = visual_3d_vp->attitude[2][2];

	for ( count = current_terrain_sector->number_of_points; count > 0; count-- )
	{

		float
			posx,
			posy,
			posz,
			r,
			g,
			b,
			grey;

		int
			ir,
			ig,
			ib,
			colour_index;

		//
		// Read in all the memory variables
		//

		current_terrain_y_int = points_y->y;

//		set_terrain_y_int_value ( points_y );

		colour_index = colour_indices->index;

		posx = ( ( ( float ) points_xz->x ) * terrain_3d_xz_scale ) + current_sector_x_visual_offset;
		posz = ( ( ( float ) points_xz->z ) * terrain_3d_xz_scale ) + current_sector_z_visual_offset;
		posy =  ( ( ( float ) current_terrain_y_int ) * terrain_3d_map_scaled_height_difference ) + current_sector_y_visual_offset;

		result_3d_points->x = posx * scaled_rotation[0][0] + posy * scaled_rotation[0][1] + posz * scaled_rotation[0][2];
		result_3d_points->y = posx * scaled_rotation[1][0] + posy * scaled_rotation[1][1] + posz * scaled_rotation[1][2];
		result_2d_points->z = posx * scaled_rotation[2][0] + posy * scaled_rotation[2][1] + posz * scaled_rotation[2][2];

		normal_indices += points_y->normal_change;	//get_3d_terrain_point_y_normal_change ( points_y );

		normal_index = normal_indices->index;

		r = colours[colour_index].red;
		g = colours[colour_index].green;
		b = colours[colour_index].blue;

		r *= 0.3;
		g *= 0.59;
		b *= 0.11;

		grey = r * 0.3 + g * 0.59 + b * 0.11;

		r = grey * terrain_3d_transformed_point_normals[normal_index].r;
		g = grey * terrain_3d_transformed_point_normals[normal_index].g;
		b = grey * terrain_3d_transformed_point_normals[normal_index].b;

		asm_convert_float_to_int ( r, &ir );
		asm_convert_float_to_int ( g, &ig );
		asm_convert_float_to_int ( b, &ib );

		result_colours->red = ir;
		result_colours->green = ig;
		result_colours->blue = ib;
		result_colours->normal_index = normal_index;

		result_colours->fog = get_int_fog_distance_value ( result_2d_points->z );
		result_colours->alpha = get_terrain_3d_alpha ( result_2d_points->z );

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

#ifdef __WATCOMC__

			start_float_divide ( result_2d_points->z, 1.0 );

			*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			q = end_float_divide ();

#else

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

#endif

			last_transformed_point = result_2d_points;
			last_transformed_point_outcode = result_outcodes;

			i = ( result_3d_points->x * q );
			j = ( result_3d_points->y * q );

			result_2d_points->j = ( active_3d_environment->y_origin - j );
			result_2d_points->i = ( active_3d_environment->x_origin + i );
			result_2d_points->q = q;
		}

		result_3d_points++;
		result_2d_points++;
		result_outcodes++;
		result_colours++;

		points_xz++;
		points_y++;
		colour_indices++;
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
	// Reset fpu precision
	//

	set_fpu_precision_mode_double ();

	//
	// Set the cullmode ( terrain isn't culled in software )
	//

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	//
	// Set the rendering states for the terrain polygons
	//

	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, terrain_texture_mag_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, terrain_texture_min_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, terrain_texture_mip_filter );
#if ALLOW_TERRAIN_TEXTURES
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
#else
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
#endif

	//
	// Go through the polys in sector, backface culling them, and drawing them
	//

	polygon = current_terrain_sector->polygons;

	surface = current_terrain_sector->surface_changes;

	terrain_3d_faces_considered += current_terrain_sector->number_of_polygons;

	current_terrain_type = surface->surface_id;

	current_terrain_type_class = &terrain_type_information[current_terrain_type];

	reset_terrain_3d_buffered_polygons ();

	reset_deferred_state_changes ();

	set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );

	set_terrain_3d_zbuffer_constant ( slot );

	if ( current_terrain_sector->number_of_points < 257 )
	{
	
		terrain_3d_sector_point_byte_references = current_terrain_sector->point_byte_references;
	
		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;
	
			if ( polygon->surface_change ) //get_3d_terrain_face_surface_change ( polygon ) )
			{

				surface++;

				current_terrain_type = surface->surface_id;
	
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				reset_deferred_state_changes ();

				set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			{
		
				if ( outcode_3d_terrain_byte_polygon ( number_of_points, terrain_3d_sector_point_byte_references, &terrain_3d_face_outcode ) )
				{
		
					commit_deferred_state_changes ();

					if ( terrain_3d_face_outcode )
					{
	
						current_terrain_type_class->render_byte_clipped ( number_of_points );
					}
					else
					{
	
						current_terrain_type_class->render_byte_unclipped ( number_of_points );
					}
				}
		
				terrain_3d_sector_point_byte_references += number_of_points;
		
				polygon++;
			}
		}
	}
	else
	{
	
		terrain_3d_sector_point_word_references = current_terrain_sector->point_word_references;
	
		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;
	
			if ( polygon->surface_change ) //get_3d_terrain_face_surface_change ( polygon ) )
			{

				surface++;

				current_terrain_type = surface->surface_id;
		
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				reset_deferred_state_changes ();

				set_deferred_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			{
		
				if ( outcode_3d_terrain_word_polygon ( number_of_points, terrain_3d_sector_point_word_references, &terrain_3d_face_outcode ) )
				{
		
					commit_deferred_state_changes ();

					if ( terrain_3d_face_outcode )
					{
	
						current_terrain_type_class->render_word_clipped ( number_of_points );
					}
					else
					{
	
						current_terrain_type_class->render_word_unclipped ( number_of_points );
					}
				}
		
				terrain_3d_sector_point_word_references += number_of_points;
		
				polygon++;
			}
		}
	}

	zbuffer_constant = zbuffer_constant_normal_bias;

	//
	// Flush any buffered polygons
	//

	draw_terrain_3d_buffered_polygons ();

#ifdef RENDER_TERRAIN_POINT_NORMALS

	//
	// Render the point normals
	//

	suspend_d3d_fog ();

	draw_3d_terrain_sector_point_normals ( slot );

	reinstate_d3d_fog ();

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_unclipped_bw_sector ( scene_slot_drawing_list *slot )
{

	int
		normal_index,
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset,
		current_sector_x_visual_offset,
		current_sector_y_visual_offset,
		current_sector_z_visual_offset;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	terrain_3d_face
		*polygon;

	terrain_3d_surface
		*surface;

	terrain_3d_normal_index
		*normal_indices;

	terrain_3d_colour
		*colours;

	terrain_3d_colour_index
		*colour_indices;

	object_transformed_2d_point
		*result_2d_points;

	terrain_3d_transformed_point_colour
		*result_colours;

	float
		scaled_rotation[3][3];

	//
	// Set fpu precision
	//

	set_fpu_precision_mode_single ();

	terrain_3d_sectors_inserted++;

	terrain_3d_sectors_totally_visible++;

	current_terrain_sector = &terrain_sectors[slot->sector.z][slot->sector.x];

//	if ( ( current_terrain_sector->approximation ) && ( slot->sector.range > TERRAIN_SECTOR_APPROXIMATION_DISTANCE ) )
//	{
//
//		current_terrain_sector = current_terrain_sector->approximation;
//	}

	current_terrain_points_xz = current_terrain_sector->points_xz;

	current_terrain_points_y = current_terrain_sector->points_y;

	points_xz = current_terrain_points_xz;

	points_y = current_terrain_points_y;

//	pretouch_integer ( ( int * ) &points_xz->x );

//	pretouch_integer ( ( int * ) &points_y->whole_value );

	current_sector_x_offset = slot->sector.x * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_z_offset = slot->sector.z * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_x_visual_offset = current_sector_x_offset - visual_3d_vp->x;

	current_sector_z_visual_offset = current_sector_z_offset - visual_3d_vp->z;

	current_sector_y_visual_offset = terrain_3d_map_minimum_height - visual_3d_vp->y;

	colours = current_terrain_sector->point_colours;

	colour_indices = current_terrain_sector->colour_indices;

	normal_indices = current_terrain_sector->normal_changes;

	result_2d_points = transformed_3d_2d_points;

	result_colours = transformed_3d_point_colours;

	//
	// Now transform all the points. Have rgb & ramp solutions though.
	//

	total_number_of_terrain_points_transformed += current_terrain_sector->number_of_points;

	normal_index = normal_indices->index;

	//
	// Set up the scaled rotation matrix
	//

	scaled_rotation[0][0] = visual_3d_vp->attitude[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = visual_3d_vp->attitude[0][1] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][2] = visual_3d_vp->attitude[0][2] * active_3d_environment->screen_i_scale;

	scaled_rotation[1][0] = visual_3d_vp->attitude[1][0] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][1] = visual_3d_vp->attitude[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = visual_3d_vp->attitude[1][2] * active_3d_environment->screen_j_scale;

	scaled_rotation[2][0] = visual_3d_vp->attitude[2][0];
	scaled_rotation[2][1] = visual_3d_vp->attitude[2][1];
	scaled_rotation[2][2] = visual_3d_vp->attitude[2][2];

	for ( count = current_terrain_sector->number_of_points; count > 0; count-- )
	{

		float
			posx,
			posy,
			posz,
			x,
			y,
			q,
			i,
			j,
			r,
			g,
			b,
			grey;

		int
			ir,
			ig,
			ib,
			colour_index;

		current_terrain_y_int = points_y->y;

//		set_terrain_y_int_value ( points_y );

		if ( points_y->normal_change )
		{

			normal_indices++;

			normal_index = normal_indices->index;
		}

		posx = ( ( ( float ) points_xz->x ) * terrain_3d_xz_scale ) + current_sector_x_visual_offset;
		posz = ( ( ( float ) points_xz->z ) * terrain_3d_xz_scale ) + current_sector_z_visual_offset;
		posy =  ( ( ( float ) current_terrain_y_int ) * terrain_3d_map_scaled_height_difference ) + current_sector_y_visual_offset;

		x = posx * scaled_rotation[0][0] + posy * scaled_rotation[0][1] + posz * scaled_rotation[0][2];
		y = posx * scaled_rotation[1][0] + posy * scaled_rotation[1][1] + posz * scaled_rotation[1][2];
		result_2d_points->z = posx * scaled_rotation[2][0] + posy * scaled_rotation[2][1] + posz * scaled_rotation[2][2];

		colour_index = colour_indices->index;

		r = colours[colour_index].red;
		g = colours[colour_index].green;
		b = colours[colour_index].blue;

		r *= 0.3;
		g *= 0.59;
		b *= 0.11;

		grey = r * 0.3 + g * 0.59 + b * 0.11;

		r = grey * terrain_3d_transformed_point_normals[normal_index].r;
		g = grey * terrain_3d_transformed_point_normals[normal_index].g;
		b = grey * terrain_3d_transformed_point_normals[normal_index].b;

		asm_convert_float_to_int ( r, &ir );
		asm_convert_float_to_int ( g, &ig );
		asm_convert_float_to_int ( b, &ib );

		result_colours->red = ir;
		result_colours->green = ig;
		result_colours->blue = ib;
		result_colours->normal_index = normal_index;

		result_colours->fog = get_int_fog_distance_value ( result_2d_points->z );
		result_colours->alpha = get_terrain_3d_alpha ( result_2d_points->z );

		q = 1.0 / result_2d_points->z;

		i = ( x * q );
		j = ( y * q );

		result_2d_points->j = ( active_3d_environment->y_origin - j );
		result_2d_points->i = ( active_3d_environment->x_origin + i );
		result_2d_points->q = q;

		result_2d_points++;
		result_colours++;

		points_xz++;
		points_y++;
		colour_indices++;
	}

	//
	// Reset fpu precision
	//

	set_fpu_precision_mode_double ();

	//
	// Set the cullmode ( terrain isn't culled in software )
	//

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	//
	// Set the rendering states for the terrain polygons
	//

	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, terrain_texture_mag_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, terrain_texture_min_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, terrain_texture_mip_filter );
#if ALLOW_TERRAIN_TEXTURES
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
#else
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
#endif

	//
	// Go through the polys in sector, backface culling them, and drawing them
	//

	terrain_3d_faces_considered += current_terrain_sector->number_of_polygons;

	polygon = current_terrain_sector->polygons;

	surface = current_terrain_sector->surface_changes;

	current_terrain_type = surface->surface_id;

	current_terrain_type_class = &terrain_type_information[current_terrain_type];

	reset_terrain_3d_buffered_polygons ();

	set_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );

	set_terrain_3d_zbuffer_constant ( slot );

	if ( current_terrain_sector->number_of_points < 257 )
	{

		terrain_3d_sector_point_byte_references = current_terrain_sector->point_byte_references;

		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;
	
			if ( polygon->surface_change ) //get_3d_terrain_face_surface_change ( polygon ) )
			{

				surface++;

				current_terrain_type = surface->surface_id;
		
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				set_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			current_terrain_type_class->render_byte_unclipped ( number_of_points );
	
			terrain_3d_sector_point_byte_references += number_of_points;
	
			polygon++;
		}
	}
	else
	{

		terrain_3d_sector_point_word_references = current_terrain_sector->point_word_references;

		for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
		{
	
			int
				number_of_points;
	
			if ( polygon->surface_change ) //get_3d_terrain_face_surface_change ( polygon ) )
			{

				surface++;

				current_terrain_type = surface->surface_id;
		
				current_terrain_type_class = &terrain_type_information[current_terrain_type];

				//
				// Flush any buffered polygons
				//

				draw_terrain_3d_buffered_polygons ();

				set_d3d_texture ( 0, load_hardware_texture_map ( current_terrain_type_class->texture ) );
			}

			number_of_points = polygon->number_of_points;	//get_3d_terrain_face_number_of_points ( polygon );
	
			current_terrain_type_class->render_word_unclipped ( number_of_points );
	
			terrain_3d_sector_point_word_references += number_of_points;
	
			polygon++;
		}
	}

	zbuffer_constant = zbuffer_constant_normal_bias;

	//
	// Flush any buffered polygons
	//

	draw_terrain_3d_buffered_polygons ();

#ifdef RENDER_TERRAIN_POINT_NORMALS

	//
	// Render the point normals
	//

	suspend_d3d_fog ();

	draw_3d_terrain_sector_point_normals ( slot );

	reinstate_d3d_fog ();

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_sector_point_normals ( scene_slot_drawing_list *slot )
{
/*
	int
		normal_index,
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset,
		current_sector_x_visual_offset,
		current_sector_z_visual_offset,
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;

	terrain_3d_sector
		*sector;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	terrain_3d_normal_index
		*normal_indices;

	vertex
		*result_points,
		*result_point_normals;

	//
	// Set fpu precision
	//

	set_fpu_precision_mode_single ();

	sector = &terrain_sectors[slot->sector.z][slot->sector.x];

	points_xz = sector->points_xz;

	points_y = sector->points_y;

	current_sector_x_offset = slot->sector.x * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_z_offset = slot->sector.z * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

	current_sector_x_visual_offset = current_sector_x_offset - visual_3d_vp->x;

	current_sector_z_visual_offset = current_sector_z_offset - visual_3d_vp->z;

	normal_indices = sector->normal_changes;

	result_points = transformed_3d_points;

	result_point_normals = terrain_transformed_3d_point_normals;

	//
	// Initialise the first point normal index
	//

	normal_index = normal_indices->index;

	//
	// Now transform all the points.
	//

	for ( count = sector->number_of_points; count > 0; count-- )
	{

		float
			posx,
			posy,
			posz,
			x,
			y,
			z,
			normal_pos_x,
			normal_pos_y,
			normal_pos_z;

		if ( points_y->normal_change )
		{

			normal_indices++;

			normal_index = normal_indices->index;
		}

		posx = ( ( float ) points_xz->x ) * TERRAIN_3D_XZ_SCALE;
		posz = ( ( float ) points_xz->z ) * TERRAIN_3D_XZ_SCALE;
		posy = terrain_3d_map_minimum_height + ( ( ( float ) points_y->y ) * terrain_3d_map_scaled_height_difference );

		normal_pos_x = posx + terrain_3d_point_normals[normal_index].x * 20.0;
		normal_pos_y = posy + terrain_3d_point_normals[normal_index].y * 20.0;
		normal_pos_z = posz + terrain_3d_point_normals[normal_index].z * 20.0;

		posx += current_sector_x_visual_offset;
		posy -= visual_3d_vp->y;
		posz += current_sector_z_visual_offset;

		normal_pos_x += current_sector_x_visual_offset;
		normal_pos_y -= visual_3d_vp->y;
		normal_pos_z += current_sector_z_visual_offset;

		z = posx * visual_3d_vp->attitude[2][0] +
				posy * visual_3d_vp->attitude[2][1] +
				posz * visual_3d_vp->attitude[2][2];

		x = posx * visual_3d_vp->attitude[0][0] +
				posy * visual_3d_vp->attitude[0][1] +
				posz * visual_3d_vp->attitude[0][2];

		y = posx * visual_3d_vp->attitude[1][0] +
				posy * visual_3d_vp->attitude[1][1] +
				posz * visual_3d_vp->attitude[1][2];

		result_points->fog = 255;

		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			q = 1.0 / z;

			result_points->x = ( float ) x;

			result_points->y = ( float ) y;

			result_points->z = ( float ) z;

			i = ( active_3d_environment->screen_i_scale * x * q );

			j = ( active_3d_environment->screen_j_scale * y * q );

			result_points->j = ( float ) ( active_3d_environment->y_origin - j );

			result_points->i = ( float ) ( active_3d_environment->x_origin + i );

			result_points->q = ( float ) q;

			oxmax = active_viewport.x_max - result_points->i;
			oxmin = result_points->i - active_viewport.x_min;
			oymax = active_viewport.y_max - result_points->j;
			oymin = result_points->j - active_viewport.y_min;

			ixmax = *( ( int * ) &oxmax );
			ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax );
			iymin = *( ( int * ) &oymin );

			result_points->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
		}
		else
		{

			result_points->outcode = CLIP_HITHER;

			result_points->z = ( float ) z;

			result_points->x = ( float ) x;

			result_points->y = ( float ) y;
		}


		z = normal_pos_x * visual_3d_vp->attitude[2][0] +
				normal_pos_y * visual_3d_vp->attitude[2][1] +
				normal_pos_z * visual_3d_vp->attitude[2][2];

		x = normal_pos_x * visual_3d_vp->attitude[0][0] +
				normal_pos_y * visual_3d_vp->attitude[0][1] +
				normal_pos_z * visual_3d_vp->attitude[0][2];

		y = normal_pos_x * visual_3d_vp->attitude[1][0] +
				normal_pos_y * visual_3d_vp->attitude[1][1] +
				normal_pos_z * visual_3d_vp->attitude[1][2];

		result_point_normals->fog = 255;

		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			q = 1.0 / z;

			result_point_normals->x = ( float ) x;

			result_point_normals->y = ( float ) y;

			result_point_normals->z = ( float ) z;

			i = ( active_3d_environment->screen_i_scale * x * q );

			j = ( active_3d_environment->screen_j_scale * y * q );

			result_point_normals->j = ( float ) ( active_3d_environment->y_origin - j );

			result_point_normals->i = ( float ) ( active_3d_environment->x_origin + i );

			result_point_normals->q = ( float ) q;

			oxmax = active_viewport.x_max - result_point_normals->i;
			oxmin = result_point_normals->i - active_viewport.x_min;
			oymax = active_viewport.y_max - result_point_normals->j;
			oymin = result_point_normals->j - active_viewport.y_min;

			ixmax = *( ( int * ) &oxmax );
			ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax );
			iymin = *( ( int * ) &oymin );

			result_point_normals->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
		}
		else
		{

			result_point_normals->outcode = CLIP_HITHER;

			result_point_normals->z = ( float ) z;

			result_point_normals->x = ( float ) x;

			result_point_normals->y = ( float ) y;
		}

		result_point_normals++;

		result_points++;
	
		points_xz++;

		points_y++;
	}

	//
	// Reset fpu precision
	//

	set_fpu_precision_mode_double ();

//	set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, FALSE );

//	set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );

	suspend_d3d_fog ();

	//
	// Go through the points - drawing the point normals
	//

	for ( count = 0; count < sector->number_of_points; count++ )
	{

		vertex
			*line;

		int
			outcode;

		line = construct_3d_terrain_normal_line ( count, &outcode );

		clip_3d_coord = 0;

		if ( line )
		{

			if ( outcode & CLIP_HITHER )
			{
		
				line = hither_clip_3d_polygon ( line, &outcode );
			}

			if ( line )
			{
	
				if ( outcode )
				{
			
					line = clip_3d_polygon ( line, outcode );
				}

				if ( line )
				{

					real_colour
						colour;

					colour.red = 255;
					colour.green = 0;
					colour.blue = 0;
					colour.alpha = 0;

					draw_d3d_plain_line ( line, colour );
				}
			}
		}
	}

	reinstate_d3d_fog ();
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_terrain_normal_line ( int index, int *polygon_outcode )
{
/*
	int
		outcode,
		outcode2;

	//
	// Always do 2 points in a line, cos they're guaranteed
	//

	outcode = transformed_3d_points[index].outcode;
	outcode2 = transformed_3d_points[index].outcode;

	//
	// Second point
	//

	outcode |= terrain_transformed_3d_point_normals[index].outcode;
	outcode2 &= terrain_transformed_3d_point_normals[index].outcode;

	transformed_3d_points[index].next_vertex = &terrain_transformed_3d_point_normals[index];

	terrain_transformed_3d_point_normals[index].next_vertex = NULL;

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		//
		// The line is totally off the screen!
		//

		return ( NULL );
	}
	else
	{

		return ( &transformed_3d_points[index] );
	}
	*/

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 060124 revert back to original state. Disappearing runways solved in popread.c
void set_terrain_3d_zbuffer_constant ( scene_slot_drawing_list *slot )
{

	if ( d3d_using_hardware_tnl )
	{

		if ( ( *( float * ) &slot->z ) > ( 3072 + TERRAIN_3D_SECTOR_SIDE_LENGTH * 4 ) )
		{

			zbuffer_constant = zbuffer_constant_normal_bias;
		}
		else
		{

			zbuffer_constant = zbuffer_constant_lowered_bias;
		}
	}
	else
	{

		zbuffer_constant = zbuffer_constant_lowered_bias;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
