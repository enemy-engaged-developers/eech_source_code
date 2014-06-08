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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_RENDER_STATES 256

#define MAX_TEXTURE_STAGES 8

#define MAX_TEXTURE_STAGE_STATES 64

#define MAX_SAMPLER_STATES 16

#define DEBUG_REPORT_STATES 0

#define DEBUG_REPORT_RENDERSTATE_VALUES 0

#define DEBUG_REPORT_TRIANGLES 1

#define ALLOW_RENDERSTATE_SHADEMODE_CHANGES 1

#define ALLOW_SET_TEXTURE 1

#define ALLOW_DEFERRED_CHANGES 1

#define DEBUG_STATE_CHANGE_FLUSHES 0

#define DEBUG_SEND_ALL_STATES 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RENDER_STATE_INFORMATION
{

	DWORD
		value;

	int
		count;
};

typedef struct RENDER_STATE_INFORMATION render_state_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TEXTURE_STATE_INFORMATION
{

	screen
		*texture;

	int
		count;
};

typedef struct TEXTURE_STATE_INFORMATION texture_state_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RENDER_STATE_INT_CHANGE
{
	DWORD
		render_state,
		value;
};

typedef struct RENDER_STATE_INT_CHANGE render_state_int_change;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RENDER_STATE_FLOAT_CHANGE
{
	DWORD
		render_state;

	float
		value;
};

typedef struct RENDER_STATE_FLOAT_CHANGE render_state_float_change;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	running_total_number_of_d3d_triangles,
	running_total_number_of_d3d_flushes,
	total_number_of_d3d_triangles,
	total_number_of_d3d_flushes,
	number_of_d3d_degenerate_triangles,
	number_of_d3d_triangles_drawn,
	number_of_d3d_lines_drawn;

static render_state_information
	render_d3d_state_table[MAX_RENDER_STATES],
	render_d3d_texture_stage_state_table[MAX_TEXTURE_STAGES][MAX_TEXTURE_STAGE_STATES],
	render_d3d_sampler_state_table[MAX_TEXTURE_STAGES][MAX_SAMPLER_STATES];

static texture_state_information
	texture_stage_interfaces[MAX_TEXTURE_STAGES];

static D3DMATERIAL9
	d3d_material;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char * get_render_state_name ( int state );

const char * get_texture_stage_state_name ( int state );

const char * get_sampler_state_name ( int state );

void raw_commit_deferred_state_changes ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPVOID
	state_list_pointer,
	state_data_pointer;

int
	state_list_number_of_states;

int
	d3d_transparency_enabled = FALSE,

	d3d_in_order_rendering = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
immediate_set_render_state ( DWORD state, DWORD data )
{
	render_d3d_state_table[state].value = data;
	render_d3d_state_table[state].count++;

	f3d_render_state ( state, data );
}

void
immediate_set_texture ( int stage, screen *texture )
{
	texture_stage_interfaces[stage].texture = texture;
	texture_stage_interfaces[stage].count++;

	f3d_set_texture ( stage, texture );
}

void
immediate_set_texture_state ( int stage, DWORD state, DWORD data )
{
	render_d3d_texture_stage_state_table[stage][state].value = data;

	f3d_set_texture_state(stage, state, data);
}

void
immediate_set_sampler_state ( int sampler, DWORD type, DWORD data )
{
	render_d3d_sampler_state_table[sampler][type].value = data;

	f3d_set_sampler_state(sampler, type, data);
}

void
immediate_set_material ( D3DMATERIAL9 *material )
{
	f3d_set_material ( material );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initialise_d3d_state ( void )
{
	int
		stage;

#if DEBUG_REPORT_TRIANGLES

	debug_colour_watch ( DEBUG_COLOUR_RED, "Number of d3d triangles: %d", MT_INT, &total_number_of_d3d_triangles );

	debug_colour_watch ( DEBUG_COLOUR_RED, "Number of d3d flushes: %d", MT_INT, &total_number_of_d3d_flushes );

#endif

	//
	// Set the default state of d3d
	//

	if ( d3d_initialised /*d3d_data.device*/ )
	{
		f3d_scene_begin ();

		force_set_d3d_int_state ( D3DRS_LASTPIXEL, TRUE );
		force_set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_FLAT );
		force_set_d3d_int_state ( D3DRS_FILLMODE, D3DFILL_SOLID );
		force_set_d3d_int_state ( D3DRS_DITHERENABLE, TRUE );
		force_set_d3d_int_state ( D3DRS_SPECULARENABLE, FALSE );
		force_set_d3d_int_state ( D3DRS_ALPHABLENDENABLE, FALSE );
		force_set_d3d_int_state ( D3DRS_ALPHATESTENABLE, FALSE );
		force_set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		force_set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		force_set_d3d_int_state ( D3DRS_CULLMODE, D3DCULL_CCW );
		force_set_d3d_int_state ( D3DRS_FOGENABLE, FALSE );
		force_set_d3d_int_state ( D3DRS_FOGTABLEMODE, D3DFOG_NONE );
		force_set_d3d_int_state ( D3DRS_FOGCOLOR, D3DCOLOR_XRGB ( 255, 255, 255 ) );
		force_set_d3d_float_state ( D3DRS_FOGSTART, 0.0 );
		force_set_d3d_float_state ( D3DRS_FOGDENSITY, 0.0 );
		force_set_d3d_float_state ( D3DRS_FOGEND, 0.0 );

		force_set_d3d_int_state ( D3DRS_ZENABLE, TRUE );
		force_set_d3d_int_state ( D3DRS_ZWRITEENABLE, TRUE );
		force_set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );

		for ( stage = 0; stage < MAX_TEXTURE_STAGES; stage++ )
		{

			float
				bias;

			bias = 0.0;

			force_set_d3d_texture ( stage, NULL );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_COLOROP, D3DTOP_DISABLE );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BUMPENVMAT00, 0 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BUMPENVMAT01, 0 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BUMPENVMAT10, 0 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BUMPENVMAT11, 0 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_TEXCOORDINDEX, stage );
			force_set_d3d_sampler_state ( stage, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
			force_set_d3d_sampler_state ( stage, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
			force_set_d3d_sampler_state ( stage, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP );
			force_set_d3d_sampler_state ( stage, D3DSAMP_BORDERCOLOR, 0 );
			force_set_d3d_sampler_state ( stage, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
			force_set_d3d_sampler_state ( stage, D3DSAMP_MINFILTER, D3DTEXF_POINT );
			force_set_d3d_sampler_state ( stage, D3DSAMP_MIPFILTER, D3DTEXF_NONE );
			force_set_d3d_sampler_state ( stage, D3DSAMP_MIPMAPLODBIAS, *( ( int * ) &bias ) );
			force_set_d3d_sampler_state ( stage, D3DSAMP_MAXMIPLEVEL, 0 );
			force_set_d3d_sampler_state ( stage, D3DSAMP_MAXANISOTROPY, 1 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BUMPENVLSCALE, 0 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BUMPENVLOFFSET, 0 );
		}

		force_set_d3d_int_state ( D3DRS_CLIPPING, FALSE );
		force_set_d3d_int_state ( D3DRS_LIGHTING, FALSE );
		force_set_d3d_int_state ( D3DRS_NORMALIZENORMALS, TRUE );
		force_set_d3d_int_state ( D3DRS_LOCALVIEWER, FALSE );

		force_set_d3d_int_state ( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL );
		force_set_d3d_int_state ( D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL );
		force_set_d3d_int_state ( D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL );
		force_set_d3d_int_state ( D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL );

		f3d_scene_end();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_alpha_fog_zbuffer ( int alpha, int fog, int ztest, int zwrite )
{

	if ( alpha )
	{

		set_d3d_int_state ( D3DRS_ALPHABLENDENABLE, TRUE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

		set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}
	else
	{

		set_d3d_int_state ( D3DRS_ALPHABLENDENABLE, FALSE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
	}

	if ( fog )
	{

		set_d3d_int_state ( D3DRS_FOGENABLE, TRUE );
		set_d3d_int_state ( D3DRS_FOGTABLEMODE, D3DFOG_NONE );
		set_d3d_float_state ( D3DRS_FOGSTART, d3d_fog_start );
		set_d3d_float_state ( D3DRS_FOGEND, d3d_fog_end );
		set_d3d_float_state ( D3DRS_FOGDENSITY, d3d_fog_density );
		set_d3d_int_state ( D3DRS_FOGCOLOR, d3d_fog_colour.colour );
	}
	else
	{

		set_d3d_int_state ( D3DRS_FOGENABLE, FALSE );
	}

	if ( ztest )
	{

		set_d3d_int_state ( D3DRS_ZENABLE, TRUE);
		set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );
	}
	else
	{

		set_d3d_int_state ( D3DRS_ZENABLE, FALSE);
		set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );
	}

	if ( zwrite )
	{

		set_d3d_int_state ( D3DRS_ZWRITEENABLE, TRUE );
	}
	else
	{

		set_d3d_int_state ( D3DRS_ZWRITEENABLE, FALSE );
	}

	d3d_transparency_enabled = alpha;

	if ( ( !alpha ) && ( ztest ) && ( zwrite ) )
	{

		set_d3d_texture_batching ( TRUE );
	}
	else
	{

		set_d3d_texture_batching ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_transparency_on ( void )
{

	set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_transparency_off ( void )
{

	set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_in_order_rendering ( int flag )
{

	d3d_in_order_rendering = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_zbuffer_comparison ( int flag )
{

	if ( flag )
	{

		set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );
	}
	else
	{

		set_d3d_int_state ( D3DRS_ZFUNC, D3DCMP_ALWAYS );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_culling ( int flag )
{

	if ( flag )
	{

		set_d3d_int_state ( D3DRS_CULLMODE, D3DCULL_CCW );
	}
	else
	{

		set_d3d_int_state ( D3DRS_CULLMODE, D3DCULL_NONE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_wrapping ( int stage, int flag )
{

	if ( flag )
	{

		set_d3d_sampler_state ( stage, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
		set_d3d_sampler_state ( stage, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	}
	else
	{

		set_d3d_sampler_state ( stage, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
		set_d3d_sampler_state ( stage, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_filtering ( int flag )
{

	if ( flag )
	{

		set_d3d_sampler_state (0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		set_d3d_sampler_state (0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		set_d3d_sampler_state (0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	else
	{

		set_d3d_sampler_state (0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		set_d3d_sampler_state (0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		set_d3d_sampler_state (0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_mag_filtering ( int flag )
{

	if ( flag )
	{

		set_d3d_sampler_state (0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}
	else
	{

		set_d3d_sampler_state (0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_min_filtering ( int flag )
{

	if ( flag )
	{

		set_d3d_sampler_state (0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	}
	else
	{

		set_d3d_sampler_state (0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_mip_filtering ( int flag )
{

	if ( flag )
	{

		set_d3d_sampler_state (0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	}
	else
	{

		set_d3d_sampler_state (0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_d3d_state_performance ( void )
{

	int
		count;

	for ( count = 0; count < MAX_RENDER_STATES; count++ )
	{

		render_d3d_state_table[count].count = 0;
	}

	for ( count = 0; count < MAX_TEXTURE_STAGES; count++ )
	{

		int
			state;

		for ( state = 0; state < MAX_TEXTURE_STAGE_STATES; state++ )
		{

			render_d3d_texture_stage_state_table[count][state].count = 0;
		}
	}

	for ( count = 0; count < MAX_TEXTURE_STAGES; count++ )
	{

		texture_stage_interfaces[count].count = 0;
	}

	number_of_d3d_triangles_drawn = 0;

	number_of_d3d_degenerate_triangles = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_d3d_state_performance ( void )
{

	running_total_number_of_d3d_triangles += number_of_d3d_triangles_drawn;

	running_total_number_of_d3d_flushes += number_of_d3d_triangle_primitives_drawn;

#if DEBUG_REPORT_STATES

	debug_log ( "Called DrawPrimitive %d times", number_of_d3d_triangle_primitives_drawn );

	{

		int
			count;


		if ( number_of_d3d_degenerate_triangles )
		{

			debug_log ( "%d DEGENERATE polygons", number_of_d3d_degenerate_triangles );
		}

		for ( count = 0; count < MAX_RENDER_STATES; count++ )
		{

			if ( render_d3d_state_table[count].count )
			{

				debug_log ( "State: %s, count: %d", get_render_state_name ( count ), render_d3d_state_table[count].count );
			}
		}

		for ( count = 0; count < MAX_TEXTURE_STAGES; count++ )
		{

			int
				state;

			for ( state = 0; state < MAX_TEXTURE_STAGE_STATES; state++ )
			{

				if ( render_d3d_texture_stage_state_table[count][state].count )
				{

					debug_log ( "Stage: %d, State: %s, count: %d", count, get_texture_stage_state_name ( state ), render_d3d_texture_stage_state_table[count][state].count );
				}
			}
		}

		for ( count = 0; count < MAX_TEXTURE_STAGES; count++ )
		{

			int
				type;

			for ( type = 0; type < MAX_SAMPLER_STATES; type++ )
			{

				if ( render_d3d_sampler_state_table[count][type].count )
				{

					debug_log ( "Sampler: %d, Type: %s, count: %d", count, get_sampler_state_name ( state ), render_d3d_sampler_state_table[count][type].count );
				}
			}
		}

		for ( count = 0; count < MAX_TEXTURE_STAGES; count++ )
		{

			if ( texture_stage_interfaces[count].count )
			{

				debug_log ( "Texture stage %d, count %d", count, texture_stage_interfaces[count].count );
			}
		}
	}

#endif

#if DEBUG_REPORT_RENDERSTATE_VALUES

	{

		int
			count;

		for ( count = 0; count < D3DRS_STIPPLEPATTERN00; count++ )
		{

			DWORD
				value;

			//IDirect3DDevice9_GetRenderState ( d3d.device3, count, &value );

			debug_log ( "State: %s, value: %d", get_render_state_name ( count ), value );
		}

		for ( count = 0; count < MAX_TEXTURE_STAGES; count++ )
		{

			int
				state;

			for ( state = 0; state < MAX_TEXTURE_STAGE_STATES; state++ )
			{

				DWORD
					value;

				//IDirect3DDevice9_GetTextureStageState ( d3d.device3, count, state, &value );

				debug_log ( "Stage: %d, State: %s, value: %d", count, get_texture_stage_state_name ( state ), value );
			}
		}

	}

#endif

	number_of_d3d_triangle_primitives_drawn = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_material_colour ( int red, int green, int blue, int alpha, int specular )
{
	float
		r,
		g,
		b,
		a,
		s;

	r = red;
	g = green;
	b = blue;
	a = alpha;
	s = specular;

	r /= 255;
	g /= 255;
	b /= 255;
	a /= 255;
	s /= 255;

	d3d_material.Diffuse.r = r;	d3d_material.Diffuse.g = g;	d3d_material.Diffuse.b = b;	d3d_material.Diffuse.a = a;
	d3d_material.Ambient.r = r;	d3d_material.Ambient.g = g;	d3d_material.Ambient.b = b;	d3d_material.Ambient.a = a;
	d3d_material.Emissive.r = 0;	d3d_material.Emissive.g = 0;	d3d_material.Emissive.b = 0;	d3d_material.Emissive.a = 0;
	d3d_material.Specular.r = s * r;	d3d_material.Specular.g = s * g;	d3d_material.Specular.b = s * b;	d3d_material.Specular.a = a;
	d3d_material.Power = 50 * s * (a + 1);

	immediate_set_material ( &d3d_material );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_material_emissive_colour ( int red, int green, int blue, int alpha )
{
	float
		r,
		g,
		b,
		a;

	r = red;
	g = green;
	b = blue;
	a = alpha;

	r /= 255;
	g /= 255;
	b /= 255;
	a /= 255;

	d3d_material.Diffuse.r = 0;	d3d_material.Diffuse.g = 0;	d3d_material.Diffuse.b = 0;	d3d_material.Diffuse.a = a;
	d3d_material.Ambient.r = 0;	d3d_material.Ambient.g = 0;	d3d_material.Ambient.b = 0;	d3d_material.Ambient.a = a;
	d3d_material.Emissive.r = r;	d3d_material.Emissive.g = g;	d3d_material.Emissive.b = b;	d3d_material.Emissive.a = a;
	d3d_material.Specular.r = 0;	d3d_material.Specular.g = 0;	d3d_material.Specular.b = 0;	d3d_material.Specular.a = a;

	immediate_set_material ( &d3d_material );
}

void set_d3d_material_default ( void )
{
	d3d_material.Diffuse.r = 1;	d3d_material.Diffuse.g = 1;	d3d_material.Diffuse.b = 1;	d3d_material.Diffuse.a = 1;
	d3d_material.Ambient.r = 1;	d3d_material.Ambient.g = 1;	d3d_material.Ambient.b = 1;	d3d_material.Ambient.a = 1;
	d3d_material.Emissive.r = 0;	d3d_material.Emissive.g = 0;	d3d_material.Emissive.b = 0;	d3d_material.Emissive.a = 1;
	d3d_material.Specular.r = 1;	d3d_material.Specular.g = 1;	d3d_material.Specular.b = 1;	d3d_material.Specular.a = 1;
	d3d_material.Power = 1;

	immediate_set_material ( &d3d_material );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_plain_renderstate ( void )
{

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture ( 0, NULL );

	set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_FLAT );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_gouraud_shaded_renderstate ( void )
{

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture ( 0, NULL );

	set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_flat_shaded_textured_renderstate ( struct SCREEN *texture )
{

	set_d3d_texture ( 0, texture );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

	set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_FLAT );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_gouraud_shaded_textured_renderstate ( struct SCREEN *texture )
{

	set_d3d_texture ( 0, texture );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

	set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void force_set_d3d_int_state ( D3DRENDERSTATETYPE state, DWORD data )
{
	flush_triangle_primitives ();
	flush_line_primitives ();

#if DEBUG_STATE_CHANGE_FLUSHES
	debug_log ( "[FORCED] Renderstate %s change caused flush", get_render_state_name ( state ) );
#endif

	immediate_set_render_state ( state, data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void force_set_d3d_float_state ( D3DRENDERSTATETYPE state, float data )
{
	flush_triangle_primitives ();
	flush_line_primitives ();

#if DEBUG_STATE_CHANGE_FLUSHES
	debug_log ( "[FORCED] Renderstate %s change caused flush", get_render_state_name ( state ) );
#endif

	immediate_set_render_state ( state, * ( DWORD * ) &data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void force_set_d3d_texture ( int stage, screen *texture )
{
#if ALLOW_SET_TEXTURE

	flush_triangle_primitives ();
	flush_line_primitives ();

#if DEBUG_STATE_CHANGE_FLUSHES
	debug_log ( "[FORCED] SetTexture %08x change caused flush", texture );
#endif

	immediate_set_texture ( stage, texture );

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void force_set_d3d_texture_stage_state ( int stage, int state, int data )
{
	ASSERT ( ( stage >= 0 ) && ( stage < 8 ) );

	flush_triangle_primitives ();
	flush_line_primitives ();

#if DEBUG_STATE_CHANGE_FLUSHES
	debug_log ( "[FORCED] Texture stage state %s change caused flush", get_texture_stage_state_name ( state ) );
#endif

	immediate_set_texture_state ( stage, state, data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void force_set_d3d_sampler_state ( int sampler, int type, int data )
{
	ASSERT ( ( sampler >= 0 ) && ( sampler < 8 ) );

	flush_triangle_primitives ();
	flush_line_primitives ();

#if DEBUG_STATE_CHANGE_FLUSHES
	debug_log ( "[FORCED] Sampler state %s change caused flush", get_sampler_state_name ( state ) );
#endif

	immediate_set_sampler_state ( sampler, type, data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int d3d_texture_batching_vertex_maximum;

void set_d3d_int_state ( D3DRENDERSTATETYPE state, DWORD data )
{
	ASSERT ( state < MAX_RENDER_STATES );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_state_table[state].value != data )
#endif
	{

#if DEBUG_STATE_CHANGE_FLUSHES
		debug_log ( "Renderstate %s change caused flush", get_render_state_name ( state ) );
#endif

		flush_triangle_primitives ();
		flush_line_primitives ();

		immediate_set_render_state ( state, data );
	}
}

void set_d3d_int_state_no_flush ( D3DRENDERSTATETYPE state, DWORD data )
{
	ASSERT ( state < MAX_RENDER_STATES );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_state_table[state].value != data )
#endif
	{

#if DEBUG_STATE_CHANGE_FLUSHES
		debug_log ( "Renderstate %s change caused flush", get_render_state_name ( state ) );
#endif

		immediate_set_render_state ( state, data );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_float_state ( D3DRENDERSTATETYPE state, float data )
{
	ASSERT ( state < MAX_RENDER_STATES );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_state_table[state].value != *( ( DWORD * ) &data ) )
#endif
	{

#if DEBUG_STATE_CHANGE_FLUSHES
		debug_log ( "Renderstate %s change caused flush", get_render_state_name ( state ) );
#endif

		flush_triangle_primitives ();
		flush_line_primitives ();

		immediate_set_render_state ( state, *( ( DWORD * ) &data ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture ( int stage, screen *texture )
{
	ASSERT ( ( stage >= 0 ) && ( stage < 8 ) );

#if ALLOW_SET_TEXTURE

#if ( !DEBUG_SEND_ALL_STATES )
	if ( texture_stage_interfaces[stage].texture != texture )
#endif
	{

#if DEBUG_STATE_CHANGE_FLUSHES
		debug_log ( "Texture change to %08x caused flush", texture );
#endif

		flush_triangle_primitives ();
		flush_line_primitives ();

		immediate_set_texture ( stage, texture );
	}

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_stage_state ( int stage, int state, int data )
{
	ASSERT ( ( stage >= 0 ) && ( stage < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_texture_stage_state_table[stage][state].value != data )
#endif
	{

#if DEBUG_STATE_CHANGE_FLUSHES
		debug_log ( "Texture stage state %s change caused flush", get_texture_stage_state_name ( state ) );
#endif

		flush_triangle_primitives ();
		flush_line_primitives ();

		immediate_set_texture_state ( stage, state, data );
	}
}

void set_d3d_texture_stage_state_no_flush ( int stage, int state, int data )
{
	ASSERT ( ( stage >= 0 ) && ( stage < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_texture_stage_state_table[stage][state].value != data )
#endif
	{

#if DEBUG_STATE_CHANGE_FLUSHES
		debug_log ( "Texture stage state %s change caused flush", get_texture_stage_state_name ( state ) );
#endif

		immediate_set_texture_state ( stage, state, data );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_sampler_state ( int sampler, int type, int data )
{
	ASSERT ( ( sampler >= 0 ) && ( sampler < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_sampler_state_table[sampler][type].value != data )
#endif
	{

#if DEBUG_STATE_CHANGE_FLUSHES
		debug_log ( "Sampler state %s change caused flush", get_sampler_state_name ( state ) );
#endif

		flush_triangle_primitives ();
		flush_line_primitives ();

		immediate_set_sampler_state ( sampler, type, data );
	}
}

void set_d3d_sampler_state_no_flush ( int sampler, int type, int data )
{
	ASSERT ( ( sampler >= 0 ) && ( sampler < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_sampler_state_table[sampler][type].value != data )
#endif
	{

#if DEBUG_STATE_CHANGE_FLUSHES
		debug_log ( "Sampler state %s change caused flush", get_sampler_state_name ( type ) );
#endif

		immediate_set_sampler_state ( sampler, type, data );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_int_state_immediate ( D3DRENDERSTATETYPE state, DWORD data )
{
	ASSERT ( state < MAX_RENDER_STATES );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_state_table[state].value != data )
#endif
	{
		immediate_set_render_state ( state, data );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_float_state_immediate ( D3DRENDERSTATETYPE state, float data )
{
	ASSERT ( state < MAX_RENDER_STATES );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_state_table[state].value != *( ( DWORD * ) &data ) )
#endif
	{
		immediate_set_render_state ( state, *( ( DWORD * ) &data ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_immediate ( int stage, screen *texture )
{
	ASSERT ( ( stage >= 0 ) && ( stage < 8 ) );

#if ALLOW_SET_TEXTURE

#if ( !DEBUG_SEND_ALL_STATES )
	if ( texture_stage_interfaces[stage].texture != texture )
#endif
	{
		immediate_set_texture ( stage, texture );
	}

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_stage_state_immediate ( int stage, int state, int data )
{
	ASSERT ( ( stage >= 0 ) && ( stage < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_texture_stage_state_table[stage][state].value != data )
#endif
	{
		immediate_set_texture_state ( stage, state, data );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_sampler_state_immediate ( int sampler, int type, int data )
{
	ASSERT ( ( sampler >= 0 ) && ( type < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_sampler_state_table[sampler][type].value != data )
#endif
	{
		immediate_set_sampler_state ( sampler, type, data );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
int get_d3d_int_state ( D3DRENDERSTATETYPE render_state )
{

	DWORD
		state;

	//IDirect3DDevice9_GetRenderState ( d3d.device, render_state, &state );

	return ( ( int ) state );
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DEFERRED_RENDERSTATE_CHANGE
{

	int
		state;

	union
	{

		int
			int_data;

		float
			float_data;
	};
};

typedef struct DEFERRED_RENDERSTATE_CHANGE deferred_renderstate_change;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DEFERRED_TEXTURE_CHANGE
{

	int
		stage;

	screen
		*texture;

	int
		count;
};

typedef struct DEFERRED_TEXTURE_CHANGE deferred_texture_change;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DEFERRED_TEXTURE_STAGE_STATE_CHANGE
{

	int
		stage,

		state,

		data;
};

typedef struct DEFERRED_TEXTURE_STAGE_STATE_CHANGE deferred_texture_stage_state_change;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DEFERRED_SAMPLER_STATE_CHANGE
{

	int
		sampler,

		type,

		data;
};

typedef struct DEFERRED_SAMPLER_STATE_CHANGE deferred_sampler_state_change;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static deferred_renderstate_change
	deferred_renderstate_changes[MAX_RENDER_STATES];

static deferred_texture_change
	deferred_texture_changes[MAX_TEXTURE_STAGES];

static deferred_texture_stage_state_change
	deferred_texture_stage_state_changes[ ( MAX_TEXTURE_STAGES * MAX_TEXTURE_STAGE_STATES ) ];

static deferred_sampler_state_change
	deferred_sampler_state_changes[ ( MAX_TEXTURE_STAGES * MAX_SAMPLER_STATES ) ];

static int
	number_of_deferred_d3d_renderstate_changes,
	number_of_deferred_d3d_texture_changes,
	number_of_deferred_d3d_texture_stage_state_changes,
	number_of_deferred_d3d_sampler_state_changes,
	deferred_d3d_changes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_deferred_d3d_int_state ( D3DRENDERSTATETYPE state, DWORD data )
{

	ASSERT ( state < MAX_RENDER_STATES );

#if ( !ALLOW_RENDERSTATE_SHADEMODE_CHANGES )

	if ( state == D3DRS_SHADEMODE )
	{

		return;
	}

#endif

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_state_table[state].value != data )
#endif
	{

		deferred_renderstate_changes[number_of_deferred_d3d_renderstate_changes].state = state;
		deferred_renderstate_changes[number_of_deferred_d3d_renderstate_changes].int_data = data;

		number_of_deferred_d3d_renderstate_changes++;
		deferred_d3d_changes = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_deferred_d3d_float_state ( D3DRENDERSTATETYPE state, float data )
{

	ASSERT ( state < MAX_RENDER_STATES );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_state_table[state].value != *( ( DWORD * ) &data ) )
#endif
	{

		deferred_renderstate_changes[number_of_deferred_d3d_renderstate_changes].state = state;
		deferred_renderstate_changes[number_of_deferred_d3d_renderstate_changes].float_data = data;

		number_of_deferred_d3d_renderstate_changes++;
		deferred_d3d_changes = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_deferred_d3d_texture ( int stage, screen *texture )
{

#if ALLOW_SET_TEXTURE
	ASSERT ( ( stage >= 0 ) && ( stage < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( texture_stage_interfaces[stage].texture != texture )
#endif
	{

		deferred_texture_changes[number_of_deferred_d3d_texture_changes].stage = stage;
		deferred_texture_changes[number_of_deferred_d3d_texture_changes].texture = texture;

		number_of_deferred_d3d_texture_changes++;
		deferred_d3d_changes = TRUE;
	}

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_deferred_d3d_texture_stage_state ( int stage, int state, int data )
{

#if ALLOW_SET_TEXTURE

	ASSERT ( ( stage >= 0 ) && ( stage < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_texture_stage_state_table[stage][state].value != data )
#endif
	{

		deferred_texture_stage_state_changes[number_of_deferred_d3d_texture_stage_state_changes].stage = stage;
		deferred_texture_stage_state_changes[number_of_deferred_d3d_texture_stage_state_changes].state = state;
		deferred_texture_stage_state_changes[number_of_deferred_d3d_texture_stage_state_changes].data = data;

		number_of_deferred_d3d_texture_stage_state_changes++;
		deferred_d3d_changes = TRUE;
	}

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_deferred_d3d_sampler_state ( int sampler, int type, int data )
{

#if ALLOW_SET_TEXTURE

	ASSERT ( ( sampler >= 0 ) && ( sampler < 8 ) );

#if ( !DEBUG_SEND_ALL_STATES )
	if ( render_d3d_sampler_state_table[sampler][type].value != data )
#endif
	{

		deferred_sampler_state_changes[number_of_deferred_d3d_sampler_state_changes].sampler = sampler;
		deferred_sampler_state_changes[number_of_deferred_d3d_sampler_state_changes].type = type;
		deferred_sampler_state_changes[number_of_deferred_d3d_sampler_state_changes].data = data;

		number_of_deferred_d3d_sampler_state_changes++;
		deferred_d3d_changes = TRUE;
	}

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_deferred_state_changes ( void )
{

	number_of_deferred_d3d_renderstate_changes = 0;

	number_of_deferred_d3d_texture_changes = 0;

	number_of_deferred_d3d_texture_stage_state_changes = 0;

	number_of_deferred_d3d_sampler_state_changes = 0;

	deferred_d3d_changes = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void commit_deferred_state_changes ( void )
{

#if ALLOW_DEFERRED_CHANGES

	if ( deferred_d3d_changes )
	{
		int
			count;

		flush_triangle_primitives ();
		flush_line_primitives ();

#if DEBUG_STATE_CHANGE_FLUSHES

		debug_log ( "Deferred state changes causing flush" );

#endif

		for ( count = 0; count < number_of_deferred_d3d_renderstate_changes; count++ )
		{
#if DEBUG_STATE_CHANGE_FLUSHES
			debug_log ( "Renderstate: %s: %d", get_render_state_name ( deferred_renderstate_changes[count].state ), deferred_renderstate_changes[count].int_data );
#endif

			immediate_set_render_state ( deferred_renderstate_changes[count].state,
				deferred_renderstate_changes[count].int_data );
		}

		for ( count = 0; count < number_of_deferred_d3d_texture_changes; count++ )
		{
#if ALLOW_SET_TEXTURE

			immediate_set_texture ( deferred_texture_changes[count].stage,
				deferred_texture_changes[count].texture );

#if DEBUG_STATE_CHANGE_FLUSHES

			debug_log ( "Texture change to %08x", deferred_texture_changes[count].texture );

#endif

#endif
		}

		for ( count = 0; count < number_of_deferred_d3d_texture_stage_state_changes; count++ )
		{
			immediate_set_texture_state ( deferred_texture_stage_state_changes[count].stage,
				deferred_texture_stage_state_changes[count].state,
				deferred_texture_stage_state_changes[count].data );

#if DEBUG_STATE_CHANGE_FLUSHES

			debug_log ( "Texture stage %d state %s value %d", stage, get_texture_stage_state_name ( state ), deferred_texture_stage_state_changes[count].data );

#endif

		}

		for ( count = 0; count < number_of_deferred_d3d_sampler_state_changes; count++ )
		{
			immediate_set_sampler_state ( deferred_sampler_state_changes[count].sampler,
				deferred_sampler_state_changes[count].type,
				deferred_sampler_state_changes[count].data );

#if DEBUG_STATE_CHANGE_FLUSHES

			debug_log ( "Sampler %d state %s value %d", stage, get_texture_stage_state_name ( state ), deferred_texture_stage_state_changes[count].data );

#endif

		}

		deferred_d3d_changes = FALSE;
	}

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_d3d_current_texture_pointer ( vertex_buffer_texture_data *data )
{

//	ASSERT ( !deferred_d3d_changes );
//	raw_commit_deferred_state_changes ();

	if ( render_d3d_texture_stage_state_table[0][D3DTSS_COLOROP].value == D3DTOP_DISABLE )
	{

		data->texture = 0;
		data->texture_settings = 0;
	}
	else
	{

		data->texture = texture_stage_interfaces[0].texture;

		data->mipmap_filter = render_d3d_sampler_state_table[0][D3DSAMP_MIPFILTER].value;
		data->linear_filter = render_d3d_sampler_state_table[0][D3DSAMP_MAGFILTER].value;
		data->clamp_u = render_d3d_sampler_state_table[0][D3DSAMP_ADDRESSU].value;
		data->clamp_v = render_d3d_sampler_state_table[0][D3DSAMP_ADDRESSV].value;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_current_texture_pointer ( vertex_buffer_texture_data *data )
{
	if ( data->texture )
	{

		if ( texture_stage_interfaces[0].texture != data->texture )
		{
			immediate_set_texture ( 0, data->texture );
		}

		set_d3d_texture_stage_state_no_flush ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

		set_d3d_sampler_state_no_flush ( 0, D3DSAMP_MIPFILTER, data->mipmap_filter );

		set_d3d_sampler_state_no_flush ( 0, D3DSAMP_MAGFILTER, data->linear_filter );

		set_d3d_sampler_state_no_flush ( 0, D3DSAMP_MINFILTER, data->linear_filter );

		set_d3d_sampler_state_no_flush ( 0, D3DSAMP_ADDRESSU, data->clamp_u );

		set_d3d_sampler_state_no_flush ( 0, D3DSAMP_ADDRESSV, data->clamp_v );
	}
	else
	{
		set_d3d_texture_stage_state_no_flush ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void assert_check_texture_match ( void )
{

	if ( d3d.triangle_buffer->texture.texture )
	{

		ASSERT ( d3d.triangle_buffer->texture.texture == texture_stage_interfaces[0].texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void assert_not_alpha_blending ( void )
{

	ASSERT ( render_d3d_state_table[D3DRS_ALPHABLENDENABLE].value == 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RENDER_STATE_TABLE_NAMES
{

	DWORD
		state;

	const char
		*name;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RENDER_STATE_TABLE_NAMES render_state_names[] =
{
	{ D3DRS_ZENABLE, "D3DRS_ZENABLE" },
	{ D3DRS_FILLMODE, "D3DRS_FILLMODE" },
	{ D3DRS_SHADEMODE, "D3DRS_SHADEMODE" },
	{ D3DRS_ZWRITEENABLE, "D3DRS_ZWRITEENABLE" },
	{ D3DRS_ALPHATESTENABLE, "D3DRS_ALPHATESTENABLE" },
	{ D3DRS_LASTPIXEL, "D3DRS_LASTPIXEL" },
	{ D3DRS_SRCBLEND, "D3DRS_SRCBLEND" },
	{ D3DRS_DESTBLEND, "D3DRS_DESTBLEND" },
	{ D3DRS_CULLMODE, "D3DRS_CULLMODE" },
	{ D3DRS_ZFUNC, "D3DRS_ZFUNC" },
	{ D3DRS_ALPHAREF, "D3DRS_ALPHAREF" },
	{ D3DRS_ALPHAFUNC, "D3DRS_ALPHAFUNC" },
	{ D3DRS_DITHERENABLE, "D3DRS_DITHERENABLE" },
	{ D3DRS_ALPHABLENDENABLE, "D3DRS_ALPHABLENDENABLE" },
	{ D3DRS_FOGENABLE, "D3DRS_FOGENABLE" },
	{ D3DRS_SPECULARENABLE, "D3DRS_SPECULARENABLE" },
	{ D3DRS_FOGCOLOR, "D3DRS_FOGCOLOR" },
	{ D3DRS_FOGTABLEMODE, "D3DRS_FOGTABLEMODE" },
	{ D3DRS_FOGSTART, "D3DRS_FOGSTART" },
	{ D3DRS_FOGEND, "D3DRS_FOGEND" },
	{ D3DRS_FOGDENSITY, "D3DRS_FOGDENSITY" },
	{ D3DRS_RANGEFOGENABLE, "D3DRS_RANGEFOGENABLE" },
	{ D3DRS_STENCILENABLE, "D3DRS_STENCILENABLE" },
	{ D3DRS_STENCILFAIL, "D3DRS_STENCILFAIL" },
	{ D3DRS_STENCILZFAIL, "D3DRS_STENCILZFAIL" },
	{ D3DRS_STENCILPASS, "D3DRS_STENCILPASS" },
	{ D3DRS_STENCILFUNC, "D3DRS_STENCILFUNC" },
	{ D3DRS_STENCILREF, "D3DRS_STENCILREF" },
	{ D3DRS_STENCILMASK, "D3DRS_STENCILMASK" },
	{ D3DRS_STENCILWRITEMASK, "D3DRS_STENCILWRITEMASK" },
	{ D3DRS_TEXTUREFACTOR, "D3DRS_TEXTUREFACTOR" },
	{ D3DRS_WRAP0, "D3DRS_WRAP0" },
	{ D3DRS_WRAP1, "D3DRS_WRAP1" },
	{ D3DRS_WRAP2, "D3DRS_WRAP2" },
	{ D3DRS_WRAP3, "D3DRS_WRAP3" },
	{ D3DRS_WRAP4, "D3DRS_WRAP4" },
	{ D3DRS_WRAP5, "D3DRS_WRAP5" },
	{ D3DRS_WRAP6, "D3DRS_WRAP6" },
	{ D3DRS_WRAP7, "D3DRS_WRAP7" },
	{ D3DRS_CLIPPING, "D3DRS_CLIPPING" },
	{ D3DRS_LIGHTING, "D3DRS_LIGHTING" },
	{ D3DRS_AMBIENT, "D3DRS_AMBIENT" },
	{ D3DRS_FOGVERTEXMODE, "D3DRS_FOGVERTEXMODE" },
	{ D3DRS_COLORVERTEX, "D3DRS_COLORVERTEX" },
	{ D3DRS_LOCALVIEWER, "D3DRS_LOCALVIEWER" },
	{ D3DRS_NORMALIZENORMALS, "D3DRS_NORMALIZENORMALS" },
	{ D3DRS_DIFFUSEMATERIALSOURCE, "D3DRS_DIFFUSEMATERIALSOURCE" },
	{ D3DRS_SPECULARMATERIALSOURCE, "D3DRS_SPECULARMATERIALSOURCE" },
	{ D3DRS_AMBIENTMATERIALSOURCE, "D3DRS_AMBIENTMATERIALSOURCE" },
	{ D3DRS_EMISSIVEMATERIALSOURCE, "D3DRS_EMISSIVEMATERIALSOURCE" },
	{ D3DRS_VERTEXBLEND, "D3DRS_VERTEXBLEND" },
	{ D3DRS_CLIPPLANEENABLE, "D3DRS_CLIPPLANEENABLE" },
	{ D3DRS_POINTSIZE, "D3DRS_POINTSIZE" },
	{ D3DRS_POINTSIZE_MIN, "D3DRS_POINTSIZE_MIN" },
	{ D3DRS_POINTSPRITEENABLE, "D3DRS_POINTSPRITEENABLE" },
	{ D3DRS_POINTSCALEENABLE, "D3DRS_POINTSCALEENABLE" },
	{ D3DRS_POINTSCALE_A, "D3DRS_POINTSCALE_A" },
	{ D3DRS_POINTSCALE_B, "D3DRS_POINTSCALE_B" },
	{ D3DRS_POINTSCALE_C, "D3DRS_POINTSCALE_C" },
	{ D3DRS_MULTISAMPLEANTIALIAS, "D3DRS_MULTISAMPLEANTIALIAS" },
	{ D3DRS_MULTISAMPLEMASK, "D3DRS_MULTISAMPLEMASK" },
	{ D3DRS_PATCHEDGESTYLE, "D3DRS_PATCHEDGESTYLE" },
	{ D3DRS_DEBUGMONITORTOKEN, "D3DRS_DEBUGMONITORTOKEN" },
	{ D3DRS_POINTSIZE_MAX, "D3DRS_POINTSIZE_MAX" },
	{ D3DRS_INDEXEDVERTEXBLENDENABLE, "D3DRS_INDEXEDVERTEXBLENDENABLE" },
	{ D3DRS_COLORWRITEENABLE, "D3DRS_COLORWRITEENABLE" },
	{ D3DRS_TWEENFACTOR, "D3DRS_TWEENFACTOR" },
	{ D3DRS_BLENDOP, "D3DRS_BLENDOP" },
	{ D3DRS_POSITIONDEGREE, "D3DRS_POSITIONDEGREE" },
	{ D3DRS_NORMALDEGREE, "D3DRS_NORMALDEGREE" },
	{ D3DRS_SCISSORTESTENABLE, "D3DRS_SCISSORTESTENABLE" },
	{ D3DRS_SLOPESCALEDEPTHBIAS, "D3DRS_SLOPESCALEDEPTHBIAS" },
	{ D3DRS_ANTIALIASEDLINEENABLE, "D3DRS_ANTIALIASEDLINEENABLE" },
	{ D3DRS_MINTESSELLATIONLEVEL, "D3DRS_MINTESSELLATIONLEVEL" },
	{ D3DRS_MAXTESSELLATIONLEVEL, "D3DRS_MAXTESSELLATIONLEVEL" },
	{ D3DRS_ADAPTIVETESS_X, "D3DRS_ADAPTIVETESS_X" },
	{ D3DRS_ADAPTIVETESS_Y, "D3DRS_ADAPTIVETESS_Y" },
	{ D3DRS_ADAPTIVETESS_Z, "D3DRS_ADAPTIVETESS_Z" },
	{ D3DRS_ADAPTIVETESS_W, "D3DRS_ADAPTIVETESS_W" },
	{ D3DRS_ENABLEADAPTIVETESSELLATION, "D3DRS_ENABLEADAPTIVETESSELLATION" },
	{ D3DRS_TWOSIDEDSTENCILMODE, "D3DRS_TWOSIDEDSTENCILMODE" },
	{ D3DRS_CCW_STENCILFAIL, "D3DRS_CCW_STENCILFAIL" },
	{ D3DRS_CCW_STENCILZFAIL, "D3DRS_CCW_STENCILZFAIL" },
	{ D3DRS_CCW_STENCILPASS, "D3DRS_CCW_STENCILPASS" },
	{ D3DRS_CCW_STENCILFUNC, "D3DRS_CCW_STENCILFUNC" },
	{ D3DRS_COLORWRITEENABLE1, "D3DRS_COLORWRITEENABLE1" },
	{ D3DRS_COLORWRITEENABLE2, "D3DRS_COLORWRITEENABLE2" },
	{ D3DRS_COLORWRITEENABLE3, "D3DRS_COLORWRITEENABLE3" },
	{ D3DRS_BLENDFACTOR, "D3DRS_BLENDFACTOR" },
	{ D3DRS_SRGBWRITEENABLE, "D3DRS_SRGBWRITEENABLE" },
	{ D3DRS_DEPTHBIAS, "D3DRS_DEPTHBIAS" },
	{ D3DRS_WRAP8, "D3DRS_WRAP8" },
	{ D3DRS_WRAP9, "D3DRS_WRAP9" },
	{ D3DRS_WRAP10, "D3DRS_WRAP10" },
	{ D3DRS_WRAP11, "D3DRS_WRAP11" },
	{ D3DRS_WRAP12, "D3DRS_WRAP12" },
	{ D3DRS_WRAP13, "D3DRS_WRAP13" },
	{ D3DRS_WRAP14, "D3DRS_WRAP14" },
	{ D3DRS_WRAP15, "D3DRS_WRAP15" },
	{ D3DRS_SEPARATEALPHABLENDENABLE, "D3DRS_SEPARATEALPHABLENDENABLE" },
	{ D3DRS_SRCBLENDALPHA, "D3DRS_SRCBLENDALPHA" },
	{ D3DRS_DESTBLENDALPHA, "D3DRS_DESTBLENDALPHA" },
	{ D3DRS_BLENDOPALPHA, "D3DRS_BLENDOPALPHA" },
};

struct RENDER_STATE_TABLE_NAMES texture_stage_state_names[] =
{
	{ D3DTSS_COLOROP, "D3DTSS_COLOROP" },
	{ D3DTSS_COLORARG1, "D3DTSS_COLORARG1" },
	{ D3DTSS_COLORARG2, "D3DTSS_COLORARG2" },
	{ D3DTSS_ALPHAOP, "D3DTSS_ALPHAOP" },
	{ D3DTSS_ALPHAARG1, "D3DTSS_ALPHAARG1" },
	{ D3DTSS_ALPHAARG2, "D3DTSS_ALPHAARG2" },
	{ D3DTSS_BUMPENVMAT00, "D3DTSS_BUMPENVMAT00" },
	{ D3DTSS_BUMPENVMAT01, "D3DTSS_BUMPENVMAT01" },
	{ D3DTSS_BUMPENVMAT10, "D3DTSS_BUMPENVMAT10" },
	{ D3DTSS_BUMPENVMAT11, "D3DTSS_BUMPENVMAT11" },
	{ D3DTSS_TEXCOORDINDEX, "D3DTSS_TEXCOORDINDEX" },
	{ D3DTSS_BUMPENVLSCALE, "D3DTSS_BUMPENVLSCALE" },
	{ D3DTSS_BUMPENVLOFFSET, "D3DTSS_BUMPENVLOFFSET" },
	{ D3DTSS_TEXTURETRANSFORMFLAGS, "D3DTSS_TEXTURETRANSFORMFLAGS" },
	{ D3DTSS_COLORARG0, "D3DTSS_COLORARG0" },
	{ D3DTSS_ALPHAARG0, "D3DTSS_ALPHAARG0" },
	{ D3DTSS_RESULTARG, "D3DTSS_RESULTARG" },
	{ D3DTSS_CONSTANT, "D3DTSS_CONSTANT" },
};

struct RENDER_STATE_TABLE_NAMES sampler_state_names[] =
{
	{ D3DSAMP_ADDRESSU, "D3DSAMP_ADDRESSU" },
	{ D3DSAMP_ADDRESSV, "D3DSAMP_ADDRESSV" },
	{ D3DSAMP_ADDRESSW, "D3DSAMP_ADDRESSW" },
	{ D3DSAMP_BORDERCOLOR, "D3DSAMP_BORDERCOLOR" },
	{ D3DSAMP_MAGFILTER, "D3DSAMP_MAGFILTER" },
	{ D3DSAMP_MINFILTER, "D3DSAMP_MINFILTER" },
	{ D3DSAMP_MIPFILTER, "D3DSAMP_MIPFILTER" },
	{ D3DSAMP_MIPMAPLODBIAS, "D3DSAMP_MIPMAPLODBIAS" },
	{ D3DSAMP_MAXMIPLEVEL, "D3DSAMP_MAXMIPLEVEL" },
	{ D3DSAMP_MAXANISOTROPY, "D3DSAMP_MAXANISOTROPY" },
	{ D3DSAMP_SRGBTEXTURE, "D3DSAMP_SRGBTEXTURE" },
	{ D3DSAMP_ELEMENTINDEX, "D3DSAMP_ELEMENTINDEX" },
	{ D3DSAMP_DMAPOFFSET, "D3DSAMP_DMAPOFFSET" },
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char * get_render_state_name ( int state )
{

	int
		count;

	for ( count = 0; count < ( sizeof ( render_state_names ) ); count++ )
	{

		if ( render_state_names[count].state == state )
		{

			return ( render_state_names[count].name );
		}
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char * get_texture_stage_state_name ( int state )
{

	int
		count;

	for ( count = 0; count < ( sizeof ( texture_stage_state_names ) ); count++ )
	{

		if ( texture_stage_state_names[count].state == state )
		{

			return ( texture_stage_state_names[count].name );
		}
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char * get_sampler_state_name ( int state )
{

	int
		count;

	for ( count = 0; count < ( sizeof ( sampler_state_names ) ); count++ )
	{

		if ( sampler_state_names[count].state == state )
		{

			return ( sampler_state_names[count].name );
		}
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_all_d3d_states ( void )
{
#if 0

	int
		count,
		size;

	size = sizeof ( render_state_names ) / sizeof ( struct RENDER_STATE_TABLE_NAMES );

	for ( count = 0; count < size; count++ )
	{

		DWORD
			value;

		I//Direct3DDevice7_GetRenderState ( d3d.device, render_state_names[count].state, &value );

		debug_log ( "%s: %d", render_state_names[count].name, value );
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

