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

#define MAX_NUMBER_OF_LIGHTNING_STRIKES 32

#define MAX_LIGHTNING_VISUAL_RANGE 15000

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct LIGHTNING_STRIKE
{

	vec3d
		position;

	float
		time_started,
		time_length,
		ground_height;

	enum LIGHTNING_STRIKE_TYPES
		type;

	int
		in_use,
		current_frame_number;
};

typedef struct LIGHTNING_STRIKE lightning_strike;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

texture_animation_indices
	lightning_strike_animation;

texture_index_numbers
	lightning_cloud_texture;

int
	number_of_lightning_strikes;

lightning_strike
	lightning_strikes[MAX_NUMBER_OF_LIGHTNING_STRIKES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_lightning_strike ( lightning_strike *strike );

static void draw_3d_lightning_cloud_burst ( lightning_strike *strike );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_lightning ( texture_animation_indices strike_animation, texture_index_numbers cloud_index )
{

	int
		count;

	lightning_strike_animation = strike_animation;

	lightning_cloud_texture = cloud_index;

	number_of_lightning_strikes = 0;

	for ( count = 0; count < MAX_NUMBER_OF_LIGHTNING_STRIKES; count++ )
	{

		lightning_strikes[count].in_use = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_lightning_strike ( lightning_strike_types type, float time, float x, float z )
{

	int
		count;

	if ( active_3d_environment )
	{
	
		for ( count = 0; count < MAX_NUMBER_OF_LIGHTNING_STRIKES; count++ )
		{
	
			if ( !lightning_strikes[count].in_use )
			{
	
				lightning_strikes[count].in_use = TRUE;
	
				lightning_strikes[count].position.x = x;
				lightning_strikes[count].position.z = z;
	
				lightning_strikes[count].position.y = 6000;
	
				lightning_strikes[count].type = type;
	
				lightning_strikes[count].current_frame_number = 0;
	
//				lightning_strikes[count].ground_height = get_3d_terrain_elevation ( x, z );
	
				lightning_strikes[count].time_started = get_3d_time_of_day ( active_3d_environment );
	
				lightning_strikes[count].time_length = time;
	
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_3d_lightning_strikes ( env_3d *env )
{

	int
		count;

	float
		time_of_day;


	time_of_day = get_3d_time_of_day ( env );

	for ( count = 0; count < MAX_NUMBER_OF_LIGHTNING_STRIKES; count++ )
	{

		if ( lightning_strikes[count].in_use )
		{

			float
				t;

			switch ( lightning_strikes[count].type )
			{

				case LIGHTNING_TYPE_CLOUD_BURST:
				{

					if ( !timed_event_has_finished ( lightning_strikes[count].time_started,
																lightning_strikes[count].time_length,
																time_of_day,
																&t ) )
					{

						lightning_strikes[count].current_frame_number = t * 10;
					}
					else
					{

						//
						// Lightning effect has terminated
						//

						lightning_strikes[count].in_use = FALSE;

					}
					
					break;
				}

				case LIGHTNING_TYPE_FORKED_1:
				case LIGHTNING_TYPE_FORKED_2:
				case LIGHTNING_TYPE_FORKED_3:
				case LIGHTNING_TYPE_FORKED_4:
				{

					if ( !timed_event_has_finished ( lightning_strikes[count].time_started,
																lightning_strikes[count].time_length,
																time_of_day,
																&t ) )
					{

						lightning_strikes[count].current_frame_number = t * ( texture_animations[lightning_strike_animation].number_of_frames );
					}
					else
					{

						//
						// Lightning effect has terminated
						//

						lightning_strikes[count].in_use = FALSE;
					}
					
					break;
				}

				default:
				{

					debug_fatal ( "Updating unknown lightning type" );

					break;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_lightning_strikes ( void )
{

	int
		count;

	for ( count = 0; count < MAX_NUMBER_OF_LIGHTNING_STRIKES; count++ )
	{

		if ( lightning_strikes[count].in_use )
		{

			float
				dx,
				dy,
				dz,
				range;

			dx = ( lightning_strikes[count].position.x - visual_3d_vp->x );
			dy = ( lightning_strikes[count].position.y - visual_3d_vp->y );
			dz = ( lightning_strikes[count].position.z - visual_3d_vp->z );

			range = sqrt ( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) );

			if ( range < MAX_LIGHTNING_VISUAL_RANGE )
			{
	
				switch ( lightning_strikes[count].type )
				{
	
					case LIGHTNING_TYPE_CLOUD_BURST:
					{
	
						draw_3d_lightning_cloud_burst ( &lightning_strikes[count] );
	
						break;
					}
	
					case LIGHTNING_TYPE_FORKED_1:
					case LIGHTNING_TYPE_FORKED_2:
					case LIGHTNING_TYPE_FORKED_3:
					case LIGHTNING_TYPE_FORKED_4:
					{
	
						draw_3d_lightning_strike ( &lightning_strikes[count] );
	
						break;
					}
	
					default:
					{
	
						debug_fatal ( "Drawing unknown lightning type" );
	
						break;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_lightning_strike ( lightning_strike *strike )
{

	vertex
		*polygon,
		*vert,
		quad[4];

	float
		heading,
		width,
		width_sin,
		width_cos;

	vec3d
		relative_position;

	int
		outcode,
		outcode2;

	screen
		*texture;

	texture = system_textures[ texture_animations[lightning_strike_animation].texture_indices[strike->current_frame_number] ];

	heading = get_heading_from_attitude_matrix ( visual_3d_vp->attitude );

	width = 3000;
	width_sin = width * sin ( -heading );
	width_cos = width * cos ( -heading );

	quad[0].next_vertex = &quad[1];
	quad[1].next_vertex = &quad[2];
	quad[2].next_vertex = &quad[3];
	quad[3].next_vertex = NULL;

	quad[0].x = width_cos;
	quad[0].z = width_sin;
	quad[0].y = 0;
	quad[0].u = 0;
	quad[0].v = 0;

	quad[3].x = -width_cos;
	quad[3].z = -width_sin;
	quad[3].y = 0;
	quad[3].u = 1;
	quad[3].v = 0;

	quad[2].x = -width_cos;
	quad[2].z = -width_sin;
	quad[2].y = - ( strike->position.y - strike->ground_height );
	quad[2].u = 1;
	quad[2].v = 1;

	quad[1].x = width_cos;
	quad[1].z = width_sin;
	quad[1].y = - ( strike->position.y - strike->ground_height );
	quad[1].u = 0;
	quad[1].v = 1;

	polygon = quad;

	//
	// Calculate the relative position of the lightning strike
	//

	relative_position.x = (	( strike->position.x - visual_3d_vp->x ) * visual_3d_vp->xv.x +
									( strike->position.y - visual_3d_vp->y ) * visual_3d_vp->xv.y +
									( strike->position.z - visual_3d_vp->z ) * visual_3d_vp->xv.z );

	relative_position.y = (	( strike->position.x - visual_3d_vp->x ) * visual_3d_vp->yv.x +
									( strike->position.y - visual_3d_vp->y ) * visual_3d_vp->yv.y +
									( strike->position.z - visual_3d_vp->z ) * visual_3d_vp->yv.z );

	relative_position.z = (	( strike->position.x - visual_3d_vp->x ) * visual_3d_vp->zv.x +
									( strike->position.y - visual_3d_vp->y ) * visual_3d_vp->zv.y +
									( strike->position.z - visual_3d_vp->z ) * visual_3d_vp->zv.z );

	{

		//
		// Rotate the polygon around to the users viewpoint
		//
	
		vert = polygon;

		rotation_3d[0][0] = ( visual_3d_vp->xv.x );
		rotation_3d[0][1] = ( visual_3d_vp->yv.x );
		rotation_3d[0][2] = ( visual_3d_vp->zv.x );
	
		rotation_3d[1][0] = ( visual_3d_vp->xv.y );
		rotation_3d[1][1] = ( visual_3d_vp->yv.y );
		rotation_3d[1][2] = ( visual_3d_vp->zv.y );
	
		rotation_3d[2][0] = ( visual_3d_vp->xv.z );
		rotation_3d[2][1] = ( visual_3d_vp->yv.z );
		rotation_3d[2][2] = ( visual_3d_vp->zv.z );

		outcode = 0;

		outcode2 = CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM | CLIP_HITHER | CLIP_YONDER;

		clip_3d_coord = 0;

		while ( vert )
		{
	
			float
				x,
				y,
				z;
	
			x = vert->x * rotation_3d[0][0] + vert->y * rotation_3d[1][0] + vert->z * rotation_3d[2][0] + relative_position.x;
			y = vert->x * rotation_3d[0][1] + vert->y * rotation_3d[1][1] + vert->z * rotation_3d[2][1] + relative_position.y;
			z = vert->x * rotation_3d[0][2] + vert->y * rotation_3d[1][2] + vert->z * rotation_3d[2][2] + relative_position.z;
	
			x *= active_3d_environment->screen_i_scale;
			y *= active_3d_environment->screen_j_scale;

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{
	
				float
					q,
					i,
					j;
	
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
			
				q = 1.0 / z;
	
				vert->x = x;
				vert->y = y;
				vert->z = z;
				vert->q = q;
	
				i = ( x * q );
				j = ( y * q );
	
				vert->j = active_3d_environment->y_origin - j;
				vert->i = active_3d_environment->x_origin + i;
	
				oxmax = active_viewport.x_max - vert->i;
				oxmin = vert->i - active_viewport.x_min;
				oymax = active_viewport.y_max - vert->j;
				oymin = vert->j - active_viewport.y_min;
			
				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );
			
				vert->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				outcode |= vert->outcode;
				outcode2 &= vert->outcode;
			}
			else
			{
	
				vert->outcode = CLIP_HITHER;
				vert->z = z;
				vert->x = x;
				vert->y = y;

				outcode |= vert->outcode;
				outcode2 &= vert->outcode;
			}
	
			vert = vert->next_vertex;
		}

		if ( outcode2 )
		{

			return;
		}


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

		{

			real_colour
				colour,
				specular;

			set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

			set_d3d_texture ( 0, load_hardware_texture_map ( texture ) );

			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
			set_d3d_texture_stage_state ( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
	
			set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
			set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
			set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );
			set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );
			set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, D3DTFP_POINT );

			colour.red = 255;
			colour.green = 255;
			colour.blue = 255;
			colour.alpha = 255;

			specular.colour = 0;
	
			draw_wbuffered_flat_shaded_textured_polygon ( polygon, colour, specular );
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_lightning_cloud_burst ( lightning_strike *strike )
{

	vertex
		*polygon,
		*vert,
		quad[4];

	float
		width,
		depth,
		intensity;

	vec3d
		relative_position;

	int
		int_intensity,
		outcode,
		outcode2;

	screen
		*texture;

	texture = system_textures[lightning_cloud_texture];

	width = 30000;
	depth = 30000;

	if ( !strike->current_frame_number )
	{

		intensity = 0.5;
	}
	else
	{

		intensity = 1.0 / ( ( float ) strike->current_frame_number );
	}

	intensity /= 3;

	quad[0].next_vertex = &quad[1];
	quad[1].next_vertex = &quad[2];
	quad[2].next_vertex = &quad[3];
	quad[3].next_vertex = NULL;

	quad[0].x = -width/2;
	quad[0].y = 0;
	quad[0].z = -depth/2;
	quad[0].u = 0;
	quad[0].v = 0;

	quad[1].x = width/2;
	quad[1].y = 0;
	quad[1].z = -depth/2;
	quad[1].u = 1;
	quad[1].v = 0;

	quad[2].x = width/2;
	quad[2].y = 0;
	quad[2].z = depth/2;
	quad[2].u = 1;
	quad[2].v = 1;

	quad[3].x = -width/2;
	quad[3].y = 0;
	quad[3].z = depth/2;
	quad[3].u = 0;
	quad[3].v = 1;

	polygon = quad;

	//
	// Calculate the relative position of the lightning strike
	//

	relative_position.x = (	( strike->position.x - visual_3d_vp->x ) * visual_3d_vp->xv.x +
									( strike->position.y - visual_3d_vp->y ) * visual_3d_vp->xv.y +
									( strike->position.z - visual_3d_vp->z ) * visual_3d_vp->xv.z );

	relative_position.y = (	( strike->position.x - visual_3d_vp->x ) * visual_3d_vp->yv.x +
									( strike->position.y - visual_3d_vp->y ) * visual_3d_vp->yv.y +
									( strike->position.z - visual_3d_vp->z ) * visual_3d_vp->yv.z );

	relative_position.z = (	( strike->position.x - visual_3d_vp->x ) * visual_3d_vp->zv.x +
									( strike->position.y - visual_3d_vp->y ) * visual_3d_vp->zv.y +
									( strike->position.z - visual_3d_vp->z ) * visual_3d_vp->zv.z );

	{

		//
		// Rotate the polygon around to the users viewpoint
		//
	
		vert = polygon;
	
		rotation_3d[0][0] = ( visual_3d_vp->xv.x );
		rotation_3d[0][1] = ( visual_3d_vp->yv.x );
		rotation_3d[0][2] = ( visual_3d_vp->zv.x );
	
		rotation_3d[1][0] = ( visual_3d_vp->xv.y );
		rotation_3d[1][1] = ( visual_3d_vp->yv.y );
		rotation_3d[1][2] = ( visual_3d_vp->zv.y );
	
		rotation_3d[2][0] = ( visual_3d_vp->xv.z );
		rotation_3d[2][1] = ( visual_3d_vp->yv.z );
		rotation_3d[2][2] = ( visual_3d_vp->zv.z );

		outcode = 0;

		outcode2 = CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM | CLIP_HITHER | CLIP_YONDER;

		clip_3d_coord = 0;

		while ( vert )
		{
	
			float
				x,
				y,
				z;
	
			x = vert->x * rotation_3d[0][0] + vert->y * rotation_3d[1][0] + vert->z * rotation_3d[2][0] + relative_position.x;
			y = vert->x * rotation_3d[0][1] + vert->y * rotation_3d[1][1] + vert->z * rotation_3d[2][1] + relative_position.y;
			z = vert->x * rotation_3d[0][2] + vert->y * rotation_3d[1][2] + vert->z * rotation_3d[2][2] + relative_position.z;

			x *= active_3d_environment->screen_i_scale;
			y *= active_3d_environment->screen_j_scale;

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{
	
				float
					q,
					i,
					j;
	
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
			
				q = 1.0 / z;
	
				vert->x = x;
				vert->y = y;
				vert->z = z;
				vert->q = q;
	
				i = ( x * q );
				j = ( y * q );
	
				vert->j = active_3d_environment->y_origin - j;
				vert->i = active_3d_environment->x_origin + i;
	
				oxmax = active_viewport.x_max - vert->i;
				oxmin = vert->i - active_viewport.x_min;
				oymax = active_viewport.y_max - vert->j;
				oymin = vert->j - active_viewport.y_min;
			
				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );
			
				vert->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				outcode |= vert->outcode;
				outcode2 &= vert->outcode;
			}
			else
			{
	
				vert->outcode = CLIP_HITHER;
				vert->z = z;
				vert->x = x;
				vert->y = y;

				outcode |= vert->outcode;
				outcode2 &= vert->outcode;
			}
	
			vert = vert->next_vertex;
		}

		if ( outcode2 )
		{

			return;
		}


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

		{

			real_colour
				colour,
				specular;

			set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

			convert_float_to_int ( intensity * 255, &int_intensity );

			colour.red = int_intensity;
			colour.green = int_intensity;
			colour.blue = int_intensity;
			colour.alpha = int_intensity;

			set_d3d_texture ( 0, load_hardware_texture_map ( texture ) );
			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
			set_d3d_texture_stage_state ( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
	
			set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
			set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
			set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );
			set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );
			set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, D3DTFP_POINT );

			specular.colour = 0;
	
			draw_wbuffered_flat_shaded_textured_polygon ( polygon, colour, specular );
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

