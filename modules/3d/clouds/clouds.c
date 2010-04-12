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

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CLOUD_MINIMUM_BLEND_DISTANCE 16384.0

#define CLOUD_MAXIMUM_BLEND_DISTANCE 65536.0

#define CLOUD_MAXIMUM_COLOUR_BLEND_DISTANCE 2048.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CLOUD_WEATHER_TEXTURE
{

	int
		valid;

	texture_index_numbers
		texture_index;
};

typedef struct CLOUD_WEATHER_TEXTURE cloud_weather_texture;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CLOUD_3D_TEXTURED_REFERENCE
{

	unsigned int

		//
		// Reference number of transformed point ( index number )
		//
	
		point;

	float

		//
		// Texture map coordinates for this cloud point
		//

		u,
		v;

	union
	{
	
		struct
		{
		
			unsigned char
				blue,
				green,
				red;

			union
			{
		
				unsigned char
					fog,
					alpha;
			};
		};

		unsigned int
			colour;
	};
};

typedef struct CLOUD_3D_TEXTURED_REFERENCE cloud_3d_textured_reference;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CLOUD_3D_POINT
{

	float
		x,
		y,
		z,
		a;

	union
	{
	
		struct
		{
		
			unsigned char
				blue,
				green,
				red;

			union
			{
		
				unsigned char
					fog,
					alpha;
			};
		};

		unsigned int
			colour;
	};
};
typedef struct CLOUD_3D_POINT cloud_3d_point;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	cloud_3d_base_height;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	cloud_3d_blend_start,
	cloud_3d_blend_end,
	cloud_3d_blend_distance;

static double
	cloud_3d_blend_constant,
	cloud_3d_blend_factor,
	cloud_3d_adjusted_blend_factor,
	cloud_3d_blend_start_squared,
	cloud_3d_blend_distance_squared;

static int
	cloud_3d_sector_scan_radius;

static vertex
	cloud_transformed_3d_points[64];

static cloud_weather_texture
	cloud_textures[WEATHERMODE_LAST];

static float
	cloud_weather_blend_factor,
	cloud_weather_one_minus_blend_factor;

static screen
	*current_weather_texture,
	*target_weather_texture;

static vec3d
	cloud_colour_blend_vector;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void transform_cloud_points ( int number_of_points, cloud_3d_point *source_points, vertex *result_points, vec3d *position );

static void render_cloud_polygon ( int number_of_points, cloud_3d_textured_reference *point_references, vertex *transformed_points, cloud_3d_point *source_points, float alpha_blend, screen *texture );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_clouds ( void )
{

	int
		count;

	for ( count = WEATHERMODE_INVALID + 1; count < WEATHERMODE_LAST; count++ )
	{

		cloud_textures[count].valid = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_cloud_texture ( texture_index_numbers index, enum WEATHERMODES weather )
{

	cloud_textures[weather].texture_index = index;

	cloud_textures[weather].valid = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_cloud_3d_base_height ( float height )
{

	cloud_3d_base_height = height;

	set_middle_scene_slot_height ( height );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_cloud_3d_base_height ( void )
{

	return ( cloud_3d_base_height );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_position_in_clouds ( float height )
{

	if ( height > cloud_3d_base_height )
	{

		return ( POSITION_ABOVE_CLOUDS );
	}
	else if ( height < cloud_3d_base_height )
	{

		return ( POSITION_BELOW_CLOUDS );
	}
	else
	{

		return ( POSITION_IN_CLOUDS );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_cloud_3d_scan_radius ( int scan_radius )
{

	if ( ( scan_radius < 1 ) || ( scan_radius > 32 ) )
	{

		debug_fatal ( "Trying to set cloud scan radius to %d", scan_radius );
	}
	else
	{

		cloud_3d_sector_scan_radius = scan_radius;

		//
		// Now set up the blending constants
		//

		cloud_3d_blend_start = CLOUD_MINIMUM_BLEND_DISTANCE;

		cloud_3d_blend_end = CLOUD_MAXIMUM_BLEND_DISTANCE;

		cloud_3d_blend_distance = cloud_3d_blend_end - cloud_3d_blend_start;

		cloud_3d_blend_start_squared = cloud_3d_blend_start * cloud_3d_blend_start;

		cloud_3d_blend_distance_squared = cloud_3d_blend_distance * cloud_3d_blend_distance;

		cloud_3d_blend_constant = cloud_3d_blend_distance_squared - cloud_3d_blend_start_squared;

		cloud_3d_blend_factor = 1.0 / cloud_3d_blend_distance_squared;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_cloud_3d_scan_radius ( void )
{

	return ( cloud_3d_sector_scan_radius );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_3d_clouds ( void )
{

	int
		visual_sector_x,
		visual_sector_z,
		current_sector_x,
		current_sector_z,
		minimum_sector_x,
		minimum_sector_z,
		maximum_sector_x,
		maximum_sector_z;

	float
		initial_sector_x_offset,
		initial_sector_z_offset,
		current_sector_x_offset,
		current_sector_z_offset;

	weathermodes
		current_weathermode,
		target_weathermode;

	matrix3x3
		cloud_matrix;

	//
	// Get the vector pointing to the colour blend
	//

	get_3d_transformation_matrix ( cloud_matrix, active_3d_environment->cloud_light.heading, active_3d_environment->cloud_light.pitch, 0 );

	cloud_colour_blend_vector.x = cloud_matrix[2][0];
	cloud_colour_blend_vector.y = 0;
	cloud_colour_blend_vector.z = cloud_matrix[2][2];

	normalise_3d_vector ( &cloud_colour_blend_vector );

	//
	// Adjust the cloud blend factor
	//

	if ( ( visual_3d_vp->y > ( cloud_3d_base_height - 100 ) ) && ( visual_3d_vp->y < ( cloud_3d_base_height + 100 ) ) )
	{

		float
			blend;

		blend = ( ( fabs ( visual_3d_vp->y - cloud_3d_base_height ) ) / 100 );

		if ( blend > 1 )
		{

			blend = 1;
		}

		cloud_3d_adjusted_blend_factor = cloud_3d_blend_factor * blend;
	}
	else
	{

		cloud_3d_adjusted_blend_factor = cloud_3d_blend_factor;
	}

	//
	// Choose the two textures to be blending inbetween
	//

	current_weathermode = get_3d_weathermode ( active_3d_environment );

	target_weathermode = get_3d_target_weathermode ( active_3d_environment );

	if ( !cloud_textures[current_weathermode].valid )
	{

		debug_fatal ( "Unable to draw clouds - no texture set for current weathermode: %d", current_weathermode );
	}

	if ( !cloud_textures[target_weathermode].texture_index )
	{

		debug_fatal ( "Unable to draw clouds - no texture set for target weathermode: %d", target_weathermode );
	}

	cloud_weather_blend_factor = get_3d_target_weathermode_transitional_status ( active_3d_environment );

	cloud_weather_one_minus_blend_factor = 1.0 - cloud_weather_blend_factor;

	if ( current_weathermode != target_weathermode )
	{

		if ( cloud_weather_blend_factor == 1 )
		{

			current_weather_texture = system_textures[ cloud_textures[target_weathermode].texture_index ];

			target_weather_texture = NULL;

			cloud_weather_blend_factor = 0;
		
			cloud_weather_one_minus_blend_factor = 1.0;
		}
		else if ( cloud_weather_blend_factor == 0 )
		{

			current_weather_texture = system_textures[ cloud_textures[current_weathermode].texture_index ];

			target_weather_texture = NULL;

			cloud_weather_blend_factor = 0;
		
			cloud_weather_one_minus_blend_factor = 1.0;
		}
		else
		{

			current_weather_texture = system_textures[ cloud_textures[current_weathermode].texture_index ];

			target_weather_texture = system_textures[ cloud_textures[target_weathermode].texture_index ];
		}
	}
	else
	{

		current_weather_texture = system_textures[ cloud_textures[current_weathermode].texture_index ];

		target_weather_texture = NULL;

		cloud_weather_blend_factor = 0;
	
		cloud_weather_one_minus_blend_factor = 1.0;
	}

	//
	// Now bias the blend factors, to take into account the transparency of each texture
	//

	cloud_weather_one_minus_blend_factor *= active_3d_environment->cloud_light.light__colour.alpha;

	cloud_weather_blend_factor *= active_3d_environment->cloud_light.light__colour.alpha;

	//
	// Get the sector the visual_3d_vp is currently in
	//

	get_cloud_3d_sector ( visual_3d_vp->x, visual_3d_vp->z, &visual_sector_x, &visual_sector_z );

	minimum_sector_x = visual_sector_x - cloud_3d_sector_scan_radius;
	minimum_sector_z = visual_sector_z - cloud_3d_sector_scan_radius;

	maximum_sector_x = visual_sector_x + cloud_3d_sector_scan_radius;
	maximum_sector_z = visual_sector_z + cloud_3d_sector_scan_radius;

	initial_sector_x_offset = minimum_sector_x * CLOUD_3D_SECTOR_SIDE_LENGTH;
	initial_sector_z_offset = minimum_sector_z * CLOUD_3D_SECTOR_SIDE_LENGTH;

	current_sector_z_offset = initial_sector_z_offset;

	for ( current_sector_z = minimum_sector_z; current_sector_z < maximum_sector_z; current_sector_z++ )
	{

		current_sector_x_offset = initial_sector_x_offset;

		for ( current_sector_x = minimum_sector_x; current_sector_x < maximum_sector_x; current_sector_x++ )
		{

			vec3d
				sector_centre,
				sector_relative_centre;

			scene_slot_drawing_list
				*sorting_slot;

			sector_centre.x = current_sector_x_offset + ( CLOUD_3D_SECTOR_SIDE_LENGTH / 2 );
			sector_centre.y = cloud_3d_base_height;
			sector_centre.z = current_sector_z_offset + ( CLOUD_3D_SECTOR_SIDE_LENGTH / 2 );

			sector_relative_centre.z = (	( sector_centre.x - visual_3d_vp->x ) * visual_3d_vp->zv.x +
													( sector_centre.y - visual_3d_vp->y ) * visual_3d_vp->zv.y +
													( sector_centre.z - visual_3d_vp->z ) * visual_3d_vp->zv.z );

			if ( ( sector_relative_centre.z + ( CLOUD_3D_SECTOR_SIDE_LENGTH * 1.4142 ) ) < clip_hither )
			{

				//
				// Cloud sector is totally behind the view
				//
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
					z_minimum_offset,
					z_maximum_offset;

				x_minimum_offset = current_sector_x_offset;
				x_maximum_offset = current_sector_x_offset + CLOUD_3D_SECTOR_SIDE_LENGTH;

				z_minimum_offset = current_sector_z_offset;
				z_maximum_offset = current_sector_z_offset + CLOUD_3D_SECTOR_SIDE_LENGTH;

				outcode = get_3d_point_outcodes ( x_minimum_offset, cloud_3d_base_height, z_minimum_offset );
				outcode1 = outcode;
				outcode2 = outcode;

				outcode = get_3d_point_outcodes ( x_minimum_offset, cloud_3d_base_height, z_maximum_offset );
				outcode1 |= outcode;
				outcode2 &= outcode;

				outcode = get_3d_point_outcodes ( x_maximum_offset, cloud_3d_base_height, z_minimum_offset );
				outcode1 |= outcode;
				outcode2 &= outcode;

				outcode = get_3d_point_outcodes ( x_maximum_offset, cloud_3d_base_height, z_maximum_offset );
				outcode1 |= outcode;
				outcode2 &= outcode;

//				if ( outcode2 == 0 )
				{

					sorting_slot = get_3d_scene_slot ();
		
					if ( sorting_slot )
					{
		
						sorting_slot->type = OBJECT_3D_DRAW_TYPE_CLOUD_SECTOR;
		
						//
						// Use the integer representation of the float value
						//
		
						sector_relative_centre.z += 32768;
		
						sorting_slot->z = *( ( int * ) &sector_relative_centre.z );
		
						sorting_slot->cloud_sector.x = current_sector_x;
		
						sorting_slot->cloud_sector.z = current_sector_z;
		
						insert_middle_scene_slot_into_3d_scene ( sorting_slot );
					}
					else
					{
		
						debug_log ( "Run out of object slots!" );
					}
				}
			}

			current_sector_x_offset += CLOUD_3D_SECTOR_SIDE_LENGTH;
		}

		current_sector_z_offset += CLOUD_3D_SECTOR_SIDE_LENGTH;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_cloud_sector ( scene_slot_drawing_list *slot )
{

	int
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset;

	double
		tempx,
		tempz;

	vec3d
		sector_centre,
		sector_relative_centre;

	cloud_3d_point
		cloud_points[256];

	float
		cloud_polygon_alphas[256];

	cloud_3d_textured_reference
		point_references[4];

	//
	// Set the fog intensity for clouds ( NO FOG )
	//

	current_sector_x_offset = slot->cloud_sector.x * CLOUD_3D_SECTOR_SIDE_LENGTH;
	current_sector_z_offset = slot->cloud_sector.z * CLOUD_3D_SECTOR_SIDE_LENGTH;

	sector_centre.x = current_sector_x_offset + ( CLOUD_3D_SECTOR_SIDE_LENGTH / 2 );
	sector_centre.y = cloud_3d_base_height;
	sector_centre.z = current_sector_z_offset + ( CLOUD_3D_SECTOR_SIDE_LENGTH / 2 );

	sector_centre.x -= visual_3d_vp->x;
	sector_centre.y -= visual_3d_vp->y;
	sector_centre.z -= visual_3d_vp->z;

	sector_relative_centre.x = (	( sector_centre.x ) * visual_3d_vp->xv.x +
											( sector_centre.y ) * visual_3d_vp->xv.y +
											( sector_centre.z ) * visual_3d_vp->xv.z );

	sector_relative_centre.y = (	( sector_centre.x ) * visual_3d_vp->yv.x +
											( sector_centre.y ) * visual_3d_vp->yv.y +
											( sector_centre.z ) * visual_3d_vp->yv.z );

	sector_relative_centre.z = (	( sector_centre.x ) * visual_3d_vp->zv.x +
											( sector_centre.y ) * visual_3d_vp->zv.y +
											( sector_centre.z ) * visual_3d_vp->zv.z );

	set_d3d_fog_face_intensity ( 0 );

	if ( d3d_flat_only_alpha )
	{

		int
			number_of_sub_sectors,
			number_of_points,
			x,
			z;

		float
			x_offset,
			z_offset,
			alpha;

		number_of_sub_sectors = 1;

		number_of_points = ( number_of_sub_sectors + 1 ) * ( number_of_sub_sectors + 1 );

		count = 0;

		for ( z = 0; z <= number_of_sub_sectors; z++ )
		{

			for ( x = 0; x <= number_of_sub_sectors; x++ )
			{

				vec3d
					point_vector;

				float
					angle,
					distance,
					colour_t,
					dr,
					dg,
					db,
					r,
					g,
					b;

				int
					ir,
					ig,
					ib;

				x_offset = ( -CLOUD_3D_SECTOR_SIDE_LENGTH/2 ) + ( ( ( float ) x / ( float ) number_of_sub_sectors ) * CLOUD_3D_SECTOR_SIDE_LENGTH );
				z_offset = ( -CLOUD_3D_SECTOR_SIDE_LENGTH/2 ) + ( ( ( float ) z / ( float ) number_of_sub_sectors ) * CLOUD_3D_SECTOR_SIDE_LENGTH );

				cloud_points[count].x = x_offset;
				cloud_points[count].y = 0;
				cloud_points[count].z = z_offset;

				point_vector.x = sector_centre.x + x_offset;
				point_vector.y = 0;
				point_vector.z = sector_centre.z + z_offset;
	
				distance = get_3d_vector_magnitude ( &point_vector );

				if ( distance > 1 )
				{
	
					normalise_3d_vector_given_magnitude ( &point_vector, distance );
		
					angle = ( ( point_vector.x * cloud_colour_blend_vector.x ) + ( point_vector.z * cloud_colour_blend_vector.z ) );
					angle = bound ( angle, 0, 1 );
					angle *= angle;
					angle *= angle;
		
					colour_t = ( distance / CLOUD_MAXIMUM_COLOUR_BLEND_DISTANCE );
					colour_t = bound ( colour_t, 0, 1 );
					colour_t *= angle;
				}
				else
				{

					colour_t = 0;
				}

				dr = active_3d_environment->cloud_light.object_colour.red - active_3d_environment->cloud_light.light__colour.red;
				dg = active_3d_environment->cloud_light.object_colour.green - active_3d_environment->cloud_light.light__colour.green;
				db = active_3d_environment->cloud_light.object_colour.blue - active_3d_environment->cloud_light.light__colour.blue;
	
				r = active_3d_environment->cloud_light.light__colour.red + ( colour_t * dr );
				g = active_3d_environment->cloud_light.light__colour.green + ( colour_t * dg );
				b = active_3d_environment->cloud_light.light__colour.blue + ( colour_t * db );
	
				convert_float_to_int ( r * 255.0, &ir );
				convert_float_to_int ( g * 255.0, &ig );
				convert_float_to_int ( b * 255.0, &ib );
	
				cloud_points[count].red = ir;
				cloud_points[count].green = ig;
				cloud_points[count].blue = ib;

				count++;
			}
		}

		count = 0;

		z_offset = -CLOUD_3D_SECTOR_SIDE_LENGTH/2 + ( CLOUD_3D_SECTOR_SIDE_LENGTH / ( number_of_sub_sectors * 2 ) );

		for ( z = 0; z < number_of_sub_sectors; z++ )
		{

			x_offset = -CLOUD_3D_SECTOR_SIDE_LENGTH/2 + ( CLOUD_3D_SECTOR_SIDE_LENGTH / ( number_of_sub_sectors * 2 ) );

			for ( x = 0; x < number_of_sub_sectors; x++ )
			{

				tempx = sector_centre.x + x_offset;
				tempz = sector_centre.z + z_offset;

				tempx *= tempx;
				tempz *= tempz;

				alpha = ( ( cloud_3d_blend_constant - ( tempx + tempz ) ) * cloud_3d_adjusted_blend_factor );
				alpha = bound ( alpha, 0, 1 );
		
				cloud_polygon_alphas[count] = alpha;

				x_offset += CLOUD_3D_SECTOR_SIDE_LENGTH / ( number_of_sub_sectors * 1 );

				count++;
			}

			z_offset += CLOUD_3D_SECTOR_SIDE_LENGTH / ( number_of_sub_sectors * 1 );
		}

		transform_cloud_points ( number_of_points, cloud_points, cloud_transformed_3d_points, &sector_relative_centre );

		//
		// Render a quad twice, for the blending between cloud textures
		//

		count = 0;

		z_offset = 0;

		for ( z = 0; z < number_of_sub_sectors; z++ )
		{

			x_offset = 0;

			for ( x = 0; x < number_of_sub_sectors; x++ )
			{

				int
					tmp,
					z_bottom_point_offset,
					z_top_point_offset;

				z_bottom_point_offset = z * ( number_of_sub_sectors + 1 );

				z_top_point_offset = z_bottom_point_offset +  ( number_of_sub_sectors + 1 );

				if ( cloud_3d_base_height < visual_3d_vp->y )
				{
	
					point_references[3].point = x + z_bottom_point_offset;
					point_references[3].u = x_offset;
					point_references[3].v = z_offset;
	
					point_references[2].point = x + z_bottom_point_offset + 1;
					point_references[2].u = x_offset + ( 1.0 / number_of_sub_sectors );
					point_references[2].v = z_offset;
	
					point_references[1].point = x + z_top_point_offset + 1;
					point_references[1].u = x_offset + ( 1.0 / number_of_sub_sectors );
					point_references[1].v = z_offset + ( 1.0 / number_of_sub_sectors );
	
					point_references[0].point = x + z_top_point_offset;
					point_references[0].u = x_offset;
					point_references[0].v = z_offset + ( 1.0 / number_of_sub_sectors );
				}
				else
				{
	
					point_references[0].point = x + z_bottom_point_offset;
					point_references[0].u = x_offset;
					point_references[0].v = z_offset;
	
					point_references[1].point = x + z_bottom_point_offset + 1;
					point_references[1].u = x_offset + ( 1.0 / number_of_sub_sectors );
					point_references[1].v = z_offset;
	
					point_references[2].point = x + z_top_point_offset + 1;
					point_references[2].u = x_offset + ( 1.0 / number_of_sub_sectors );
					point_references[2].v = z_offset + ( 1.0 / number_of_sub_sectors );
	
					point_references[3].point = x + z_top_point_offset;
					point_references[3].u = x_offset;
					point_references[3].v = z_offset + ( 1.0 / number_of_sub_sectors );
				}

				for ( tmp = 0; tmp < 4; tmp++ )
				{
		
					cloud_points[ point_references[tmp].point ].a = cloud_polygon_alphas[count];
				}

				if ( current_weather_texture )
				{

					render_cloud_polygon ( 4, point_references, cloud_transformed_3d_points, cloud_points, cloud_weather_one_minus_blend_factor, current_weather_texture );
				}

				if ( target_weather_texture )
				{

					render_cloud_polygon ( 4, point_references, cloud_transformed_3d_points, cloud_points, cloud_weather_blend_factor, target_weather_texture );
				}

				x_offset += ( 1.0 / number_of_sub_sectors );

				count++;
			}

			z_offset += ( 1.0 / number_of_sub_sectors );
		}
	}
	else
	{
	
		cloud_points[0].x = -CLOUD_3D_SECTOR_SIDE_LENGTH/2;
		cloud_points[0].y = 0;
		cloud_points[0].z = -CLOUD_3D_SECTOR_SIDE_LENGTH/2;
	
		cloud_points[1].x = +CLOUD_3D_SECTOR_SIDE_LENGTH/2;
		cloud_points[1].y = 0;
		cloud_points[1].z = -CLOUD_3D_SECTOR_SIDE_LENGTH/2;
	
		cloud_points[2].x = +CLOUD_3D_SECTOR_SIDE_LENGTH/2;
		cloud_points[2].y = 0;
		cloud_points[2].z = +CLOUD_3D_SECTOR_SIDE_LENGTH/2;
	
		cloud_points[3].x = -CLOUD_3D_SECTOR_SIDE_LENGTH/2;
		cloud_points[3].y = 0;
		cloud_points[3].z = +CLOUD_3D_SECTOR_SIDE_LENGTH/2;

		for ( count = 0; count < 4; count++ )
		{

			vec3d
				point_vector;

			int
				ir,
				ig,
				ib;

			float
				colour_t,
				alpha,
				distance,
				angle,
				dr,
				dg,
				db,
				r,
				g,
				b;

			tempx = sector_centre.x + cloud_points[count].x;
			tempz = sector_centre.z + cloud_points[count].z;

			point_vector.x = tempx;
			point_vector.y = 0;
			point_vector.z = tempz;

			distance = get_3d_vector_magnitude ( &point_vector );

			if ( distance > 1 )
			{
	
				normalise_3d_vector_given_magnitude ( &point_vector, distance );
	
				angle = ( ( point_vector.x * cloud_colour_blend_vector.x ) + ( point_vector.z * cloud_colour_blend_vector.z ) );
				angle = bound ( angle, 0, 1 );
				angle *= angle;
				angle *= angle;
	
				colour_t = ( distance / CLOUD_MAXIMUM_COLOUR_BLEND_DISTANCE );
				colour_t = bound ( colour_t, 0, 1 );
				colour_t *= angle;
			}
			else
			{

				colour_t = 0;
			}
	
			alpha = ( ( cloud_3d_blend_constant - ( distance * distance ) ) * cloud_3d_adjusted_blend_factor );

			cloud_points[count].a = bound ( alpha, 0, 1 );

			dr = active_3d_environment->cloud_light.object_colour.red - active_3d_environment->cloud_light.light__colour.red;
			dg = active_3d_environment->cloud_light.object_colour.green - active_3d_environment->cloud_light.light__colour.green;
			db = active_3d_environment->cloud_light.object_colour.blue - active_3d_environment->cloud_light.light__colour.blue;

			r = active_3d_environment->cloud_light.light__colour.red + ( colour_t * dr );
			g = active_3d_environment->cloud_light.light__colour.green + ( colour_t * dg );
			b = active_3d_environment->cloud_light.light__colour.blue + ( colour_t * db );

			convert_float_to_int ( r * 255.0, &ir );
			convert_float_to_int ( g * 255.0, &ig );
			convert_float_to_int ( b * 255.0, &ib );

			cloud_points[count].red = ir;
			cloud_points[count].green = ig;
			cloud_points[count].blue = ib;
/*
			debug_log ( "( %d, %d, %d ) -> ( %d, %d, %d ) d( %d, %d, %d ) blend = %f = %d, %d, %d",
									active_3d_environment->cloud_light.light__colour.red * 255,
									active_3d_environment->cloud_light.light__colour.green * 255,
									active_3d_environment->cloud_light.light__colour.blue * 255,
									active_3d_environment->cloud_light.object_colour.red * 255,
									active_3d_environment->cloud_light.object_colour.green * 255,
									active_3d_environment->cloud_light.object_colour.blue * 255,
									dr * 255,
									dg * 255,
									db * 255,
									colour_t,
									ir, ig, ib );
*/
		}

		transform_cloud_points ( 4, cloud_points, cloud_transformed_3d_points, &sector_relative_centre );

		//
		// Render a quad twice, for the blending between cloud textures
		//

		if ( cloud_3d_base_height < visual_3d_vp->y )
		{
	
			point_references[3].point = 0; point_references[3].u = 0; point_references[3].v = 0;
			point_references[2].point = 1; point_references[2].u = 1; point_references[2].v = 0;
			point_references[1].point = 2; point_references[1].u = 1; point_references[1].v = 1;
			point_references[0].point = 3; point_references[0].u = 0; point_references[0].v = 1;
		}
		else
		{
	
			point_references[0].point = 0; point_references[0].u = 0; point_references[0].v = 0;
			point_references[1].point = 1; point_references[1].u = 1; point_references[1].v = 0;
			point_references[2].point = 2; point_references[2].u = 1; point_references[2].v = 1;
			point_references[3].point = 3; point_references[3].u = 0; point_references[3].v = 1;
		}

		if ( current_weather_texture )
		{

			render_cloud_polygon ( 4, point_references, cloud_transformed_3d_points, cloud_points, cloud_weather_one_minus_blend_factor, current_weather_texture );
		}

		if ( target_weather_texture )
		{

			render_cloud_polygon ( 4, point_references, cloud_transformed_3d_points, cloud_points, cloud_weather_blend_factor, target_weather_texture );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_cloud_points ( int number_of_points, cloud_3d_point *source_points, vertex *result_points, vec3d *position )
{

	float
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		count,
		ixmax,
		ixmin,
		iymax,
		iymin;

	//
	// Now transform all the points.
	//

	for ( count = number_of_points; count > 0; count-- )
	{

		float
			x,
			y,
			z;

		x = source_points->x * visual_3d_vp->attitude[0][0] +
				source_points->y * visual_3d_vp->attitude[0][1] +
				source_points->z * visual_3d_vp->attitude[0][2] + position->x;

		y = source_points->x * visual_3d_vp->attitude[1][0] +
				source_points->y * visual_3d_vp->attitude[1][1] +
				source_points->z * visual_3d_vp->attitude[1][2] + position->y;

		z = source_points->x * visual_3d_vp->attitude[2][0] +
				source_points->y * visual_3d_vp->attitude[2][1] +
				source_points->z * visual_3d_vp->attitude[2][2] + position->z;

		x *= active_3d_environment->screen_i_scale;
		y *= active_3d_environment->screen_j_scale;

		result_points->colour = source_points->colour;

		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			q = 1.0 / z;

			result_points->x = x;
			result_points->y = y;
			result_points->z = z;

			i = ( x * q );
			j = ( y * q );

			result_points->j = ( active_3d_environment->y_origin - j );
			result_points->i = ( active_3d_environment->x_origin + i );
			result_points->q = q;

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
			result_points->z = z;
			result_points->x = x;
			result_points->y = y;
		}

		result_points++;
	
		source_points++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_cloud_polygon ( int number_of_points, cloud_3d_textured_reference *point_references, vertex *transformed_points, cloud_3d_point *source_points, float alpha_blend, screen *texture )
{

	int
		count,
		alpha,
		first_point,
		this_point,
		previous_point,
		outcode,
		outcode2;

	vertex
		*polygon;

	first_point = point_references->point;

	this_point = first_point;

	outcode = transformed_points[this_point].outcode;
	outcode2 = transformed_points[this_point].outcode;
	convert_float_to_int ( ( source_points[this_point].a * alpha_blend * 255 ), &alpha );
	transformed_points[this_point].u = point_references->u;
	transformed_points[this_point].v = point_references->v;
	transformed_points[this_point].alpha = alpha;

	point_references++;

	for ( count = 1; count < number_of_points; count++ )
	{

		previous_point = this_point;

		this_point = point_references->point;

		outcode |= transformed_points[this_point].outcode;
		outcode2 &= transformed_points[this_point].outcode;

		convert_float_to_int ( ( source_points[this_point].a * alpha_blend * 255 ), &alpha );

		transformed_points[this_point].u = point_references->u;
		transformed_points[this_point].v = point_references->v;
		transformed_points[this_point].alpha = alpha;

		cloud_transformed_3d_points[previous_point].next_vertex = &cloud_transformed_3d_points[this_point];

		point_references++;
	}

	cloud_transformed_3d_points[this_point].next_vertex = NULL;

	if ( !outcode2 )
	{
	
		polygon = &cloud_transformed_3d_points[first_point];

		clip_3d_coord = 0;
	
		if ( outcode & CLIP_HITHER )
		{
	
			polygon = hither_clip_3d_polygon ( polygon, &outcode );

			if ( !polygon )
			{

				return;
			}
		}
	
		if ( outcode )
		{

			apply_perspective_to_polygon_texture ( polygon );

			polygon = clip_3d_polygon ( polygon, outcode );

			if ( !polygon )
			{

				return;
			}

			remove_perspective_from_polygon_texture ( polygon );
		}
	
		if ( polygon )
		{

			set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
			set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
			set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
			set_d3d_gouraud_shaded_textured_renderstate ( texture );

			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
			set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );
			set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );

			{
			
				int
					number_of_vertices;
			
				vertex
					*vert;
			
				LPD3DTLVERTEX
					vertices,
					vptr;
			
				vert = polygon;
			
				vertices = get_d3d_vertices_address ( polygon, &number_of_vertices );
			
				vptr = vertices;
			
				while ( vert )
				{
			
					real_colour
						specular;
			
					specular.colour = d3d_fog_intensity;
					specular.red = vert->specular;
					specular.green = vert->specular;
					specular.blue = vert->specular;
			
					*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
					*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
					*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
					*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
					*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
					vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
					vptr->color = vert->colour;
					vptr->specular = specular.colour;

					if ( vptr->sz >= 1.0 )
					{

						vptr->sz = 0.999f;
					}
		
					vptr++;
			
					vert = vert->next_vertex;
				}
			
				draw_fan_primitive ( number_of_vertices, vertices );
			}

//			draw_wbuffered_gouraud_shaded_textured_polygon ( polygon );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_cloud_3d_sector ( float x, float z, int *sectorx, int *sectorz )
{

	convert_float_to_int ( ( x / CLOUD_3D_SECTOR_SIDE_LENGTH ), sectorx );

	convert_float_to_int ( ( z / CLOUD_3D_SECTOR_SIDE_LENGTH ), sectorz );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

