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
#include "3d/3dfunc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_RENDER_STATES 256

#define MAX_RENDER_STATE_CHANGES 256

#define MAX_TEXTURE_STAGES 8

#define MAX_TEXTURE_STAGE_STATES 32

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
	render_d3d_texture_stage_state_table[MAX_TEXTURE_STAGES][MAX_TEXTURE_STAGE_STATES];

static texture_state_information
	texture_stage_interfaces[MAX_TEXTURE_STAGES];

static D3DMATERIAL7
	d3d_material;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char * get_render_state_name ( int state );

const char * get_texture_stage_state_name ( int state );

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
immediate_set_material ( D3DMATERIAL7 *material )
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
	
		force_set_d3d_int_state ( D3DRENDERSTATE_LASTPIXEL, TRUE );
		force_set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
		force_set_d3d_int_state ( D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID );
		force_set_d3d_int_state ( D3DRENDERSTATE_DITHERENABLE, TRUE );
		force_set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_ANTIALIAS, D3DANTIALIAS_NONE );
		force_set_d3d_int_state ( D3DRENDERSTATE_BLENDENABLE, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_COLORKEYENABLE, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_ALPHATESTENABLE, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
		force_set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
		force_set_d3d_int_state ( D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE );
		force_set_d3d_int_state ( D3DRENDERSTATE_STIPPLEDALPHA, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );
		force_set_d3d_int_state ( D3DRENDERSTATE_ZVISIBLE, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_NONE );
		force_set_d3d_int_state ( D3DRENDERSTATE_FOGCOLOR, RGB_MAKE ( 255, 255, 255 ) );
		force_set_d3d_float_state ( D3DRENDERSTATE_FOGTABLESTART, 0.0 );
		force_set_d3d_float_state ( D3DRENDERSTATE_FOGTABLEDENSITY, 0.0 );
		force_set_d3d_float_state ( D3DRENDERSTATE_FOGTABLEEND, 0.0 );
	
		if ( TRUE /*ddraw.lpZBuffer*/ )
		{
	
			force_set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, TRUE );
			force_set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
			force_set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, zbuffer_default_comparison );
		}
		else
		{
	
			force_set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, FALSE);
			force_set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			force_set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, zbuffer_default_comparison );
		}
	
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
			force_set_d3d_texture_stage_state ( stage, D3DTSS_ADDRESS, D3DTADDRESS_WRAP );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BORDERCOLOR, 0 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_MAGFILTER, D3DTFG_POINT );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_MINFILTER, D3DTFN_POINT );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_MIPFILTER, D3DTFP_NONE );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_MIPMAPLODBIAS, *( ( int * ) &bias ) );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_MAXMIPLEVEL, 0 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_MAXANISOTROPY, 1 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BUMPENVLSCALE, 0 );
			force_set_d3d_texture_stage_state ( stage, D3DTSS_BUMPENVLOFFSET, 0 );
		}
	
		force_set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_EXTENTS, FALSE );
		force_set_d3d_int_state ( D3DRENDERSTATE_NORMALIZENORMALS, TRUE );
		force_set_d3d_int_state ( D3DRENDERSTATE_LOCALVIEWER, FALSE );
	
		force_set_d3d_int_state ( D3DRENDERSTATE_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL );
		force_set_d3d_int_state ( D3DRENDERSTATE_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL );
		force_set_d3d_int_state ( D3DRENDERSTATE_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL );
		force_set_d3d_int_state ( D3DRENDERSTATE_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL );

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

		set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
	
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

		set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
		set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
	}

	if ( fog )
	{

		set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, TRUE );
		set_d3d_int_state ( D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_NONE );
		set_d3d_float_state ( D3DRENDERSTATE_FOGTABLESTART, d3d_fog_start );
		set_d3d_float_state ( D3DRENDERSTATE_FOGTABLEEND, d3d_fog_end );
		set_d3d_float_state ( D3DRENDERSTATE_FOGTABLEDENSITY, d3d_fog_density );
		set_d3d_int_state ( D3DRENDERSTATE_FOGCOLOR, d3d_fog_colour.colour );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, FALSE );
	}

	if ( ztest )
	{

		set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, TRUE);
		set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, zbuffer_default_comparison );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, FALSE);
		set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, zbuffer_default_comparison );
	}

	if ( zwrite )
	{

		set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, FALSE );
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

		set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, zbuffer_default_comparison );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_culling ( int flag )
{

	if ( flag )
	{

		set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_wrapping ( int stage, int flag )
{

	if ( flag )
	{

		set_d3d_texture_stage_state ( stage, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
		set_d3d_texture_stage_state ( stage, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	}
	else
	{

		set_d3d_texture_stage_state ( stage, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
		set_d3d_texture_stage_state ( stage, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_filtering ( int flag )
{

	if ( flag )
	{

		set_d3d_texture_stage_state (0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		set_d3d_texture_stage_state (0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		set_d3d_texture_stage_state (0, D3DTSS_MIPFILTER, D3DTFP_LINEAR);
	}
	else
	{

		set_d3d_texture_stage_state (0, D3DTSS_MAGFILTER, D3DTFG_POINT);
		set_d3d_texture_stage_state (0, D3DTSS_MINFILTER, D3DTFN_POINT);
		set_d3d_texture_stage_state (0, D3DTSS_MIPFILTER, D3DTFP_NONE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_mag_filtering ( int flag )
{

	if ( flag )
	{

		set_d3d_texture_stage_state (0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	}
	else
	{

		set_d3d_texture_stage_state (0, D3DTSS_MAGFILTER, D3DTFG_POINT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_min_filtering ( int flag )
{

	if ( flag )
	{

		set_d3d_texture_stage_state (0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
	}
	else
	{

		set_d3d_texture_stage_state (0, D3DTSS_MINFILTER, D3DTFN_POINT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_mip_filtering ( int flag )
{

	if ( flag )
	{

		set_d3d_texture_stage_state (0, D3DTSS_MIPFILTER, D3DTFP_POINT);
	}
	else
	{

		set_d3d_texture_stage_state (0, D3DTSS_MIPFILTER, D3DTFP_NONE);
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
					
					debug_log ( "Stage: %d, State: %s, count: %d", count,
																					get_texture_stage_state_name ( state ),
																					render_d3d_texture_stage_state_table[count][state].count );
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
	
		for ( count = 0; count < D3DRENDERSTATE_STIPPLEPATTERN00; count++ )
		{

			DWORD
				value;

			I//Direct3DDevice7_GetRenderState ( d3d.device3, count, &value );

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

				I//Direct3DDevice7_GetTextureStageState ( d3d.device3, count, state, &value );

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

	d3d_material.dcvDiffuse.r = r;	d3d_material.dcvDiffuse.g = g;	d3d_material.dcvDiffuse.b = b;	d3d_material.dcvDiffuse.a = a;
	d3d_material.dcvAmbient.r = r;	d3d_material.dcvAmbient.g = g;	d3d_material.dcvAmbient.b = b;	d3d_material.dcvAmbient.a = a;
	d3d_material.dcvEmissive.r = 0;	d3d_material.dcvEmissive.g = 0;	d3d_material.dcvEmissive.b = 0;	d3d_material.dcvEmissive.a = 0;
	d3d_material.dcvSpecular.r = s * r;	d3d_material.dcvSpecular.g = s * g;	d3d_material.dcvSpecular.b = s * b;	d3d_material.dcvSpecular.a = a;
	d3d_material.dvPower = 50 * s * (a + 1);

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

	d3d_material.dcvDiffuse.r = 0;	d3d_material.dcvDiffuse.g = 0;	d3d_material.dcvDiffuse.b = 0;	d3d_material.dcvDiffuse.a = a;
	d3d_material.dcvAmbient.r = 0;	d3d_material.dcvAmbient.g = 0;	d3d_material.dcvAmbient.b = 0;	d3d_material.dcvAmbient.a = a;
	d3d_material.dcvEmissive.r = r;	d3d_material.dcvEmissive.g = g;	d3d_material.dcvEmissive.b = b;	d3d_material.dcvEmissive.a = a;
	d3d_material.dcvSpecular.r = 0;	d3d_material.dcvSpecular.g = 0;	d3d_material.dcvSpecular.b = 0;	d3d_material.dcvSpecular.a = a;

	immediate_set_material ( &d3d_material );
}

void set_d3d_material_default ( void )
{
	d3d_material.dcvDiffuse.r = 1;	d3d_material.dcvDiffuse.g = 1;	d3d_material.dcvDiffuse.b = 1;	d3d_material.dcvDiffuse.a = 1;
	d3d_material.dcvAmbient.r = 1;	d3d_material.dcvAmbient.g = 1;	d3d_material.dcvAmbient.b = 1;	d3d_material.dcvAmbient.a = 1;
	d3d_material.dcvEmissive.r = 0;	d3d_material.dcvEmissive.g = 0;	d3d_material.dcvEmissive.b = 0;	d3d_material.dcvEmissive.a = 1;
	d3d_material.dcvSpecular.r = 1;	d3d_material.dcvSpecular.g = 1;	d3d_material.dcvSpecular.b = 1;	d3d_material.dcvSpecular.a = 1;
	d3d_material.dvPower = 1;

	immediate_set_material ( &d3d_material );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_plain_renderstate ( void )
{

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture ( 0, NULL );

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_gouraud_shaded_renderstate ( void )
{

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture ( 0, NULL );

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_flat_shaded_textured_renderstate ( struct SCREEN *texture )
{

	set_d3d_texture ( 0, texture );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_gouraud_shaded_textured_renderstate ( struct SCREEN *texture )
{

	set_d3d_texture ( 0, texture );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );
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

#if 0
int get_d3d_int_state ( D3DRENDERSTATETYPE render_state )
{

	DWORD
		state;

	I//Direct3DDevice7_GetRenderState ( d3d.device, render_state, &state );

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

static deferred_renderstate_change
	deferred_renderstate_changes[MAX_RENDER_STATES];

static deferred_texture_change
	deferred_texture_changes[MAX_TEXTURE_STAGES];

static deferred_texture_stage_state_change
	deferred_texture_stage_state_changes[ ( MAX_TEXTURE_STAGES * MAX_TEXTURE_STAGE_STATES ) ];

static int
	number_of_deferred_d3d_renderstate_changes,
	number_of_deferred_d3d_texture_changes,
	number_of_deferred_d3d_texture_stage_state_changes,
	deferred_d3d_changes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_deferred_d3d_int_state ( D3DRENDERSTATETYPE state, DWORD data )
{

	ASSERT ( state < MAX_RENDER_STATES );

#if ( !ALLOW_RENDERSTATE_SHADEMODE_CHANGES )

	if ( state == D3DRENDERSTATE_SHADEMODE )
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

void reset_deferred_state_changes ( void )
{

	number_of_deferred_d3d_renderstate_changes = 0;

	number_of_deferred_d3d_texture_changes = 0;

	number_of_deferred_d3d_texture_stage_state_changes = 0;

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

		data->mipmap_filter = render_d3d_texture_stage_state_table[0][D3DTSS_MIPFILTER].value;
		data->linear_filter = render_d3d_texture_stage_state_table[0][D3DTSS_MAGFILTER].value;
		data->clamp_u = render_d3d_texture_stage_state_table[0][D3DTSS_ADDRESSU].value;
		data->clamp_v = render_d3d_texture_stage_state_table[0][D3DTSS_ADDRESSV].value;
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

		set_d3d_texture_stage_state_no_flush ( 0, D3DTSS_MIPFILTER, data->mipmap_filter );

		set_d3d_texture_stage_state_no_flush ( 0, D3DTSS_MAGFILTER, data->linear_filter );

		set_d3d_texture_stage_state_no_flush ( 0, D3DTSS_MINFILTER, data->linear_filter );

		set_d3d_texture_stage_state_no_flush ( 0, D3DTSS_ADDRESSU, data->clamp_u );

		set_d3d_texture_stage_state_no_flush ( 0, D3DTSS_ADDRESSV, data->clamp_v );
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

	ASSERT ( render_d3d_state_table[D3DRENDERSTATE_ALPHABLENDENABLE].value == 0 );
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

	{ D3DRENDERSTATE_TEXTUREHANDLE, "D3DRENDERSTATE_TEXTUREHANDLE" },
	{ D3DRENDERSTATE_ANTIALIAS, "D3DRENDERSTATE_ANTIALIAS" },
	{ D3DRENDERSTATE_TEXTUREADDRESS, "D3DRENDERSTATE_TEXTUREADDRESS" },
	{ D3DRENDERSTATE_TEXTUREPERSPECTIVE, "D3DRENDERSTATE_TEXTUREPERSPECTIVE" },
	{ D3DRENDERSTATE_WRAPU, "D3DRENDERSTATE_WRAPU" },
	{ D3DRENDERSTATE_WRAPV, "D3DRENDERSTATE_WRAPV" },
	{ D3DRENDERSTATE_ZENABLE, "D3DRENDERSTATE_ZENABLE" },
	{ D3DRENDERSTATE_FILLMODE, "D3DRENDERSTATE_FILLMODE" },
	{ D3DRENDERSTATE_SHADEMODE, "D3DRENDERSTATE_SHADEMODE" },
	{ D3DRENDERSTATE_LINEPATTERN, "D3DRENDERSTATE_LINEPATTERN" },
	{ D3DRENDERSTATE_MONOENABLE, "D3DRENDERSTATE_MONOENABLE" },
	{ D3DRENDERSTATE_ROP2, "D3DRENDERSTATE_ROP2" },
	{ D3DRENDERSTATE_PLANEMASK, "D3DRENDERSTATE_PLANEMASK" },
	{ D3DRENDERSTATE_ZWRITEENABLE, "D3DRENDERSTATE_ZWRITEENABLE" },
	{ D3DRENDERSTATE_ALPHATESTENABLE, "D3DRENDERSTATE_ALPHATESTENABLE" },
	{ D3DRENDERSTATE_LASTPIXEL, "D3DRENDERSTATE_LASTPIXEL" },
	{ D3DRENDERSTATE_TEXTUREMAG, "D3DRENDERSTATE_TEXTUREMAG" },
	{ D3DRENDERSTATE_TEXTUREMIN, "D3DRENDERSTATE_TEXTUREMIN" },
	{ D3DRENDERSTATE_SRCBLEND, "D3DRENDERSTATE_SRCBLEND" },
	{ D3DRENDERSTATE_DESTBLEND, "D3DRENDERSTATE_DESTBLEND" },
	{ D3DRENDERSTATE_TEXTUREMAPBLEND, "D3DRENDERSTATE_TEXTUREMAPBLEND" },
	{ D3DRENDERSTATE_CULLMODE, "D3DRENDERSTATE_CULLMODE" },
	{ D3DRENDERSTATE_ZFUNC, "D3DRENDERSTATE_ZFUNC" },
	{ D3DRENDERSTATE_ALPHAREF, "D3DRENDERSTATE_ALPHAREF" },
	{ D3DRENDERSTATE_ALPHAFUNC, "D3DRENDERSTATE_ALPHAFUNC" },
	{ D3DRENDERSTATE_DITHERENABLE, "D3DRENDERSTATE_DITHERENABLE" },
	{ D3DRENDERSTATE_ALPHABLENDENABLE, "D3DRENDERSTATE_ALPHABLENDENABLE" },
	{ D3DRENDERSTATE_FOGENABLE, "D3DRENDERSTATE_FOGENABLE" },
	{ D3DRENDERSTATE_SPECULARENABLE, "D3DRENDERSTATE_SPECULARENABLE" },
	{ D3DRENDERSTATE_ZVISIBLE, "D3DRENDERSTATE_ZVISIBLE" },
	{ D3DRENDERSTATE_SUBPIXEL, "D3DRENDERSTATE_SUBPIXEL" },
	{ D3DRENDERSTATE_SUBPIXELX, "D3DRENDERSTATE_SUBPIXELX" },
	{ D3DRENDERSTATE_STIPPLEDALPHA, "D3DRENDERSTATE_STIPPLEDALPHA" },
	{ D3DRENDERSTATE_FOGCOLOR, "D3DRENDERSTATE_FOGCOLOR" },
	{ D3DRENDERSTATE_FOGTABLEMODE, "D3DRENDERSTATE_FOGTABLEMODE" },
	{ D3DRENDERSTATE_FOGTABLESTART, "D3DRENDERSTATE_FOGTABLESTART" },
	{ D3DRENDERSTATE_FOGTABLEEND, "D3DRENDERSTATE_FOGTABLEEND" },
	{ D3DRENDERSTATE_FOGTABLEDENSITY, "D3DRENDERSTATE_FOGTABLEDENSITY" },
	{ D3DRENDERSTATE_STIPPLEENABLE, "D3DRENDERSTATE_STIPPLEENABLE" },
	{ D3DRENDERSTATE_EDGEANTIALIAS, "D3DRENDERSTATE_EDGEANTIALIAS" },
	{ D3DRENDERSTATE_COLORKEYENABLE, "D3DRENDERSTATE_COLORKEYENABLE" },
	{ D3DRENDERSTATE_BORDERCOLOR, "D3DRENDERSTATE_BORDERCOLOR" },
	{ D3DRENDERSTATE_TEXTUREADDRESSU, "D3DRENDERSTATE_TEXTUREADDRESSU" },
	{ D3DRENDERSTATE_TEXTUREADDRESSV, "D3DRENDERSTATE_TEXTUREADDRESSV" },
	{ D3DRENDERSTATE_MIPMAPLODBIAS, "D3DRENDERSTATE_MIPMAPLODBIAS" },
	{ D3DRENDERSTATE_ZBIAS, "D3DRENDERSTATE_ZBIAS" },
	{ D3DRENDERSTATE_RANGEFOGENABLE, "D3DRENDERSTATE_RANGEFOGENABLE" },
	{ D3DRENDERSTATE_ANISOTROPY, "D3DRENDERSTATE_ANISOTROPY" },
	{ D3DRENDERSTATE_FLUSHBATCH, "D3DRENDERSTATE_FLUSHBATCH" },
	{ D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT, "D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT" },
	{ D3DRENDERSTATE_STENCILENABLE, "D3DRENDERSTATE_STENCILENABLE" },
	{ D3DRENDERSTATE_STENCILFAIL, "D3DRENDERSTATE_STENCILFAIL" },
	{ D3DRENDERSTATE_STENCILZFAIL, "D3DRENDERSTATE_STENCILZFAIL" },
	{ D3DRENDERSTATE_STENCILPASS, "D3DRENDERSTATE_STENCILPASS" },
	{ D3DRENDERSTATE_STENCILFUNC, "D3DRENDERSTATE_STENCILFUNC" },
	{ D3DRENDERSTATE_STENCILREF, "D3DRENDERSTATE_STENCILREF" },
	{ D3DRENDERSTATE_STENCILMASK, "D3DRENDERSTATE_STENCILMASK" },
	{ D3DRENDERSTATE_STENCILWRITEMASK, "D3DRENDERSTATE_STENCILWRITEMASK" },
	{ D3DRENDERSTATE_TEXTUREFACTOR, "D3DRENDERSTATE_TEXTUREFACTOR" },
	{ D3DRENDERSTATE_STIPPLEPATTERN00, "D3DRENDERSTATE_STIPPLEPATTERN00" },
	{ D3DRENDERSTATE_STIPPLEPATTERN01, "D3DRENDERSTATE_STIPPLEPATTERN01" },
	{ D3DRENDERSTATE_STIPPLEPATTERN02, "D3DRENDERSTATE_STIPPLEPATTERN02" },
	{ D3DRENDERSTATE_STIPPLEPATTERN03, "D3DRENDERSTATE_STIPPLEPATTERN03" },
	{ D3DRENDERSTATE_STIPPLEPATTERN04, "D3DRENDERSTATE_STIPPLEPATTERN04" },
	{ D3DRENDERSTATE_STIPPLEPATTERN05, "D3DRENDERSTATE_STIPPLEPATTERN05" },
	{ D3DRENDERSTATE_STIPPLEPATTERN06, "D3DRENDERSTATE_STIPPLEPATTERN06" },
	{ D3DRENDERSTATE_STIPPLEPATTERN07, "D3DRENDERSTATE_STIPPLEPATTERN07" },
	{ D3DRENDERSTATE_STIPPLEPATTERN08, "D3DRENDERSTATE_STIPPLEPATTERN08" },
	{ D3DRENDERSTATE_STIPPLEPATTERN09, "D3DRENDERSTATE_STIPPLEPATTERN09" },
	{ D3DRENDERSTATE_STIPPLEPATTERN10, "D3DRENDERSTATE_STIPPLEPATTERN10" },
	{ D3DRENDERSTATE_STIPPLEPATTERN11, "D3DRENDERSTATE_STIPPLEPATTERN11" },
	{ D3DRENDERSTATE_STIPPLEPATTERN12, "D3DRENDERSTATE_STIPPLEPATTERN12" },
	{ D3DRENDERSTATE_STIPPLEPATTERN13, "D3DRENDERSTATE_STIPPLEPATTERN13" },
	{ D3DRENDERSTATE_STIPPLEPATTERN14, "D3DRENDERSTATE_STIPPLEPATTERN14" },
	{ D3DRENDERSTATE_STIPPLEPATTERN15, "D3DRENDERSTATE_STIPPLEPATTERN15" },
	{ D3DRENDERSTATE_STIPPLEPATTERN16, "D3DRENDERSTATE_STIPPLEPATTERN16" },
	{ D3DRENDERSTATE_STIPPLEPATTERN17, "D3DRENDERSTATE_STIPPLEPATTERN17" },
	{ D3DRENDERSTATE_STIPPLEPATTERN18, "D3DRENDERSTATE_STIPPLEPATTERN18" },
	{ D3DRENDERSTATE_STIPPLEPATTERN19, "D3DRENDERSTATE_STIPPLEPATTERN19" },
	{ D3DRENDERSTATE_STIPPLEPATTERN20, "D3DRENDERSTATE_STIPPLEPATTERN20" },
	{ D3DRENDERSTATE_STIPPLEPATTERN21, "D3DRENDERSTATE_STIPPLEPATTERN21" },
	{ D3DRENDERSTATE_STIPPLEPATTERN22, "D3DRENDERSTATE_STIPPLEPATTERN22" },
	{ D3DRENDERSTATE_STIPPLEPATTERN23, "D3DRENDERSTATE_STIPPLEPATTERN23" },
	{ D3DRENDERSTATE_STIPPLEPATTERN24, "D3DRENDERSTATE_STIPPLEPATTERN24" },
	{ D3DRENDERSTATE_STIPPLEPATTERN25, "D3DRENDERSTATE_STIPPLEPATTERN25" },
	{ D3DRENDERSTATE_STIPPLEPATTERN26, "D3DRENDERSTATE_STIPPLEPATTERN26" },
	{ D3DRENDERSTATE_STIPPLEPATTERN27, "D3DRENDERSTATE_STIPPLEPATTERN27" },
	{ D3DRENDERSTATE_STIPPLEPATTERN28, "D3DRENDERSTATE_STIPPLEPATTERN28" },
	{ D3DRENDERSTATE_STIPPLEPATTERN29, "D3DRENDERSTATE_STIPPLEPATTERN29" },
	{ D3DRENDERSTATE_STIPPLEPATTERN30, "D3DRENDERSTATE_STIPPLEPATTERN30" },
	{ D3DRENDERSTATE_STIPPLEPATTERN31, "D3DRENDERSTATE_STIPPLEPATTERN31" },
	{ D3DRENDERSTATE_WRAP0, "D3DRENDERSTATE_WRAP0" },
	{ D3DRENDERSTATE_WRAP1, "D3DRENDERSTATE_WRAP1" },
	{ D3DRENDERSTATE_WRAP2, "D3DRENDERSTATE_WRAP2" },
	{ D3DRENDERSTATE_WRAP3, "D3DRENDERSTATE_WRAP3" },
	{ D3DRENDERSTATE_WRAP4, "D3DRENDERSTATE_WRAP4" },
	{ D3DRENDERSTATE_WRAP5, "D3DRENDERSTATE_WRAP5" },
	{ D3DRENDERSTATE_WRAP6, "D3DRENDERSTATE_WRAP6" },
	{ D3DRENDERSTATE_WRAP7, "D3DRENDERSTATE_WRAP7" },
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
	{ D3DTSS_ADDRESS, "D3DTSS_ADDRESS" },
	{ D3DTSS_ADDRESSU, "D3DTSS_ADDRESSU" },
	{ D3DTSS_ADDRESSV, "D3DTSS_ADDRESSV" },
	{ D3DTSS_BORDERCOLOR, "D3DTSS_BORDERCOLOR" },
	{ D3DTSS_MAGFILTER, "D3DTSS_MAGFILTER" },
	{ D3DTSS_MINFILTER, "D3DTSS_MINFILTER" },
	{ D3DTSS_MIPFILTER, "D3DTSS_MIPFILTER" },
	{ D3DTSS_MIPMAPLODBIAS, "D3DTSS_MIPMAPLODBIAS" },
	{ D3DTSS_MAXMIPLEVEL, "D3DTSS_MAXMIPLEVEL" },
	{ D3DTSS_MAXANISOTROPY, "D3DTSS_MAXANISOTROPY" },
	{ D3DTSS_BUMPENVLSCALE, "D3DTSS_BUMPENVLSCALE" },
	{ D3DTSS_BUMPENVLOFFSET, "D3DTSS_BUMPENVLOFFSET" }
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

