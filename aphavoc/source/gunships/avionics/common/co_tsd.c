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

//VJ 030429 TSD render mod
// common functions used by all choppers

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "ai/ai_misc/ai_dbase.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define COLOUR_BASE 64
#define COLOUR_SCALE(a)    min(COLOUR_BASE,(int)(COLOUR_BASE*a/elevation_factor)+1)
#define GET_TERRAIN_COLOUR(a, c, f) if (terrain_elev > 0)\
			   								{\
			   									a = map_palette[c];\
													a.r *= f; a.g *= f; a.b *= f;\
												}\
			   								else\
			   									a = map_palette[0]

static rgb_colour
		paper_colour[COLOUR_BASE+1],
		terrain_colour[4][COLOUR_BASE+1];

static int
	draw_large_mfd;

static int
	tsd_render_palette,
	contour_spacing,
	contour_samples;

static rgb_colour* map_palette;

//VJ 030424 TSD render mod default to on
#define OPTIMISE_CONTOURS	1

#define OPTIMISE_PATHS		1

#define DEBUG_ASPECT 0

#if OPTIMISE_CONTOURS
static int
	num_contour_loops,
	num_contour_lines;
#endif


#define TSD_ASE_RANGE_2000		((float) 2000.0)
#define TSD_ASE_RANGE_5000		((float) 5000.0)
#define TSD_ASE_RANGE_10000	((float) 10000.0)
#define TSD_ASE_RANGE_25000	((float) 25000.0)
#define HIND_MOVING_MAP_RANGE_50000	((float) 50000.0)

static rgb_colour
	map_river_colour,
	map_road_colour,
	map_contour_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Initialise_TSD_render_terrain(void)
{
	draw_large_mfd = TRUE;

	tsd_render_palette = command_line_tsd_palette;
	set_rgb_colour(map_river_colour, 0, 0,  96, 255);
	set_rgb_colour(map_road_colour, 32, 32,  20, 255);
	set_rgb_colour(map_contour_colour, 80, 64,  20, 255);
//water

//colours as atlas: green yellow red white, strong
/*
	set_rgb_colour(terrain_colour[0][0],100, 150, 240, 255);
	set_rgb_colour(terrain_colour[0][1],89,152,41,255);
	set_rgb_colour(terrain_colour[0][2],93,142,41,255);
	set_rgb_colour(terrain_colour[0][3],97,132,41,255);
	set_rgb_colour(terrain_colour[0][4],100,122,41,255);
	set_rgb_colour(terrain_colour[0][5],104,122,41,255);
	set_rgb_colour(terrain_colour[0][6],108,122,41,255);
	set_rgb_colour(terrain_colour[0][7],112,122,41,255);
	set_rgb_colour(terrain_colour[0][8],115,122,41,255);
	set_rgb_colour(terrain_colour[0][9],133,133,46,255);
	set_rgb_colour(terrain_colour[0][10],143,143,51,255);
	set_rgb_colour(terrain_colour[0][11],153,153,56,255);
	set_rgb_colour(terrain_colour[0][12],163,163,61,255);
	set_rgb_colour(terrain_colour[0][13],173,173,66,255);
	set_rgb_colour(terrain_colour[0][14],184,184,71,255);
	set_rgb_colour(terrain_colour[0][15],194,194,77,255);
	set_rgb_colour(terrain_colour[0][16],204,204,82,255);
	set_rgb_colour(terrain_colour[0][17],194,189,77,255);
	set_rgb_colour(terrain_colour[0][18],184,173,71,255);
	set_rgb_colour(terrain_colour[0][19],173,158,66,255);
	set_rgb_colour(terrain_colour[0][20],163,143,61,255);
	set_rgb_colour(terrain_colour[0][21],153,128,56,255);
	set_rgb_colour(terrain_colour[0][22],143,112,51,255);
	set_rgb_colour(terrain_colour[0][23],133,97,46,255);
	set_rgb_colour(terrain_colour[0][24],122,82,41,255);
	set_rgb_colour(terrain_colour[0][25],130,93,56,255);
	set_rgb_colour(terrain_colour[0][26],138,105,71,255);
	set_rgb_colour(terrain_colour[0][27],146,116,87,255);
	set_rgb_colour(terrain_colour[0][28],153,128,102,255);
	set_rgb_colour(terrain_colour[0][29],161,139,117,255);
	set_rgb_colour(terrain_colour[0][30],169,151,133,255);
	set_rgb_colour(terrain_colour[0][31],176,162,148,255);
	set_rgb_colour(terrain_colour[0][32],184,174,163,255);
*/
set_rgb_colour(terrain_colour[0][0],100, 150, 240, 255);
set_rgb_colour(terrain_colour[0][1 ],89,152,41,255);
set_rgb_colour(terrain_colour[0][2 ],91,147,41,255);
set_rgb_colour(terrain_colour[0][3 ],93,142,41,255);
set_rgb_colour(terrain_colour[0][4 ],95,137,41,255);
set_rgb_colour(terrain_colour[0][5 ],97,132,41,255);
set_rgb_colour(terrain_colour[0][6 ],99,127,41,255);
set_rgb_colour(terrain_colour[0][7 ],100,122,41,255);
set_rgb_colour(terrain_colour[0][8 ],102,122,41,255);
set_rgb_colour(terrain_colour[0][9 ],104,122,41,255);
set_rgb_colour(terrain_colour[0][10],106,122,41,255);
set_rgb_colour(terrain_colour[0][11],108,122,41,255);
set_rgb_colour(terrain_colour[0][12],110,122,41,255);
set_rgb_colour(terrain_colour[0][13],112,122,41,255);
set_rgb_colour(terrain_colour[0][14],114,122,41,255);
set_rgb_colour(terrain_colour[0][15],115,122,41,255);
set_rgb_colour(terrain_colour[0][16],124,128,44,255);
set_rgb_colour(terrain_colour[0][17],133,133,46,255);
set_rgb_colour(terrain_colour[0][18],138,138,49,255);
set_rgb_colour(terrain_colour[0][19],143,143,51,255);
set_rgb_colour(terrain_colour[0][20],148,148,54,255);
set_rgb_colour(terrain_colour[0][21],153,153,56,255);
set_rgb_colour(terrain_colour[0][22],158,158,59,255);
set_rgb_colour(terrain_colour[0][23],163,163,61,255);
set_rgb_colour(terrain_colour[0][24],168,168,64,255);
set_rgb_colour(terrain_colour[0][25],173,173,66,255);
set_rgb_colour(terrain_colour[0][26],179,179,69,255);
set_rgb_colour(terrain_colour[0][27],184,184,71,255);
set_rgb_colour(terrain_colour[0][28],189,189,74,255);
set_rgb_colour(terrain_colour[0][29],194,194,77,255);
set_rgb_colour(terrain_colour[0][30],199,199,80,255);
set_rgb_colour(terrain_colour[0][31],204,204,82,255);
set_rgb_colour(terrain_colour[0][32],199,197,80,255);
set_rgb_colour(terrain_colour[0][33],194,189,77,255);
set_rgb_colour(terrain_colour[0][34],189,181,74,255);
set_rgb_colour(terrain_colour[0][35],184,173,71,255);
set_rgb_colour(terrain_colour[0][36],179,166,69,255);
set_rgb_colour(terrain_colour[0][37],173,158,66,255);
set_rgb_colour(terrain_colour[0][38],168,151,64,255);
set_rgb_colour(terrain_colour[0][39],163,143,61,255);
set_rgb_colour(terrain_colour[0][40],158,136,59,255);
set_rgb_colour(terrain_colour[0][41],153,128,56,255);
set_rgb_colour(terrain_colour[0][42],148,120,54,255);
set_rgb_colour(terrain_colour[0][43],143,112,51,255);
set_rgb_colour(terrain_colour[0][44],138,105,49,255);
set_rgb_colour(terrain_colour[0][45],133,97,46,255);
set_rgb_colour(terrain_colour[0][46],128,90,44,255);
set_rgb_colour(terrain_colour[0][47],122,82,41,255);
set_rgb_colour(terrain_colour[0][48],126,88,49,255);
set_rgb_colour(terrain_colour[0][49],130,93,56,255);
set_rgb_colour(terrain_colour[0][50],134,99,64,255);
set_rgb_colour(terrain_colour[0][51],138,105,71,255);
set_rgb_colour(terrain_colour[0][52],142,111,79,255);
set_rgb_colour(terrain_colour[0][53],146,116,87,255);
set_rgb_colour(terrain_colour[0][54],150,122,95,255);
set_rgb_colour(terrain_colour[0][55],153,128,102,255);
set_rgb_colour(terrain_colour[0][56],157,134,110,255);
set_rgb_colour(terrain_colour[0][57],161,139,117,255);
set_rgb_colour(terrain_colour[0][58],165,145,125,255);
set_rgb_colour(terrain_colour[0][59],169,151,133,255);
set_rgb_colour(terrain_colour[0][60],173,157,141,255);
set_rgb_colour(terrain_colour[0][61],176,162,148,255);
set_rgb_colour(terrain_colour[0][62],180,168,156,255);
set_rgb_colour(terrain_colour[0][63],184,174,163,255);
set_rgb_colour(terrain_colour[0][64],184,174,163,255);
                                 
//yellow to brown               
/* 
	set_rgb_colour(terrain_colour[1][0],100, 150, 240, 255);
	set_rgb_colour(terrain_colour[1][1],254,230,175,255);
	set_rgb_colour(terrain_colour[1][2],254,231,170,255);
	set_rgb_colour(terrain_colour[1][3],254,232,165,255);
	set_rgb_colour(terrain_colour[1][4],254,231,161,255);
	set_rgb_colour(terrain_colour[1][5],255,231,156,255);
	set_rgb_colour(terrain_colour[1][6],255,229,153,255);
	set_rgb_colour(terrain_colour[1][7],255,228,149,255);
	set_rgb_colour(terrain_colour[1][8],255,225,145,255);
	set_rgb_colour(terrain_colour[1][9],255,222,142,255);
	set_rgb_colour(terrain_colour[1][10],255,219,139,255);
	set_rgb_colour(terrain_colour[1][11],255,215,136,255);
	set_rgb_colour(terrain_colour[1][12],255,211,133,255);
	set_rgb_colour(terrain_colour[1][13],255,206,129,255);
	set_rgb_colour(terrain_colour[1][14],255,201,126,255);
	set_rgb_colour(terrain_colour[1][15],255,195,123,255);
	set_rgb_colour(terrain_colour[1][16],253,189,120,255);
	set_rgb_colour(terrain_colour[1][17],251,183,116,255);
	set_rgb_colour(terrain_colour[1][18],247,176,112,255);
	set_rgb_colour(terrain_colour[1][19],243,168,108,255);
	set_rgb_colour(terrain_colour[1][20],238,161,103,255);
	set_rgb_colour(terrain_colour[1][21],232,152,99,255);
	set_rgb_colour(terrain_colour[1][22],225,144,94,255);
	set_rgb_colour(terrain_colour[1][23],217,135,88,255);
	set_rgb_colour(terrain_colour[1][24],208,126,82,255);
	set_rgb_colour(terrain_colour[1][25],198,117,75,255);
	set_rgb_colour(terrain_colour[1][26],186,107,68,255);
	set_rgb_colour(terrain_colour[1][27],173,97,61,255);
	set_rgb_colour(terrain_colour[1][28],159,86,52,255);
	set_rgb_colour(terrain_colour[1][29],143,76,43,255);
	set_rgb_colour(terrain_colour[1][30],125,65,34,255);
	set_rgb_colour(terrain_colour[1][31],106,53,23,255);
	set_rgb_colour(terrain_colour[1][32],86,42,12,255);
*/
set_rgb_colour(terrain_colour[1][0 ],100,150,240,255);
set_rgb_colour(terrain_colour[1][1 ],254,230,175,255);
set_rgb_colour(terrain_colour[1][2 ],254,231,173,255);
set_rgb_colour(terrain_colour[1][3 ],254,231,170,255);
set_rgb_colour(terrain_colour[1][4 ],254,232,168,255);
set_rgb_colour(terrain_colour[1][5 ],254,232,165,255);
set_rgb_colour(terrain_colour[1][6 ],254,232,163,255);
set_rgb_colour(terrain_colour[1][7 ],254,231,161,255);
set_rgb_colour(terrain_colour[1][8 ],255,231,159,255);
set_rgb_colour(terrain_colour[1][9 ],255,231,156,255);
set_rgb_colour(terrain_colour[1][10],255,230,155,255);
set_rgb_colour(terrain_colour[1][11],255,229,153,255);
set_rgb_colour(terrain_colour[1][12],255,229,151,255);
set_rgb_colour(terrain_colour[1][13],255,228,149,255);
set_rgb_colour(terrain_colour[1][14],255,227,147,255);
set_rgb_colour(terrain_colour[1][15],255,225,145,255);
set_rgb_colour(terrain_colour[1][16],255,224,144,255);
set_rgb_colour(terrain_colour[1][17],255,222,142,255);
set_rgb_colour(terrain_colour[1][18],255,221,141,255);
set_rgb_colour(terrain_colour[1][19],255,219,139,255);
set_rgb_colour(terrain_colour[1][20],255,217,138,255);
set_rgb_colour(terrain_colour[1][21],255,215,136,255);
set_rgb_colour(terrain_colour[1][22],255,213,135,255);
set_rgb_colour(terrain_colour[1][23],255,211,133,255);
set_rgb_colour(terrain_colour[1][24],255,209,131,255);
set_rgb_colour(terrain_colour[1][25],255,206,129,255);
set_rgb_colour(terrain_colour[1][26],255,204,128,255);
set_rgb_colour(terrain_colour[1][27],255,201,126,255);
set_rgb_colour(terrain_colour[1][28],255,198,125,255);
set_rgb_colour(terrain_colour[1][29],255,195,123,255);
set_rgb_colour(terrain_colour[1][30],254,192,122,255);
set_rgb_colour(terrain_colour[1][31],253,189,120,255);
set_rgb_colour(terrain_colour[1][32],252,186,118,255);
set_rgb_colour(terrain_colour[1][33],251,183,116,255);
set_rgb_colour(terrain_colour[1][34],249,180,114,255);
set_rgb_colour(terrain_colour[1][35],247,176,112,255);
set_rgb_colour(terrain_colour[1][36],245,172,110,255);
set_rgb_colour(terrain_colour[1][37],243,168,108,255);
set_rgb_colour(terrain_colour[1][38],241,165,106,255);
set_rgb_colour(terrain_colour[1][39],238,161,103,255);
set_rgb_colour(terrain_colour[1][40],235,157,101,255);
set_rgb_colour(terrain_colour[1][41],232,152,99,255);
set_rgb_colour(terrain_colour[1][42],229,148,97,255);
set_rgb_colour(terrain_colour[1][43],225,144,94,255);
set_rgb_colour(terrain_colour[1][44],221,140,91,255);
set_rgb_colour(terrain_colour[1][45],217,135,88,255);
set_rgb_colour(terrain_colour[1][46],213,131,85,255);
set_rgb_colour(terrain_colour[1][47],208,126,82,255);
set_rgb_colour(terrain_colour[1][48],203,122,79,255);
set_rgb_colour(terrain_colour[1][49],198,117,75,255);
set_rgb_colour(terrain_colour[1][50],192,112,72,255);
set_rgb_colour(terrain_colour[1][51],186,107,68,255);
set_rgb_colour(terrain_colour[1][52],180,102,65,255);
set_rgb_colour(terrain_colour[1][53],173,97,61,255);
set_rgb_colour(terrain_colour[1][54],166,92,57,255);
set_rgb_colour(terrain_colour[1][55],159,86,52,255);
set_rgb_colour(terrain_colour[1][56],151,81,48,255);
set_rgb_colour(terrain_colour[1][57],143,76,43,255);
set_rgb_colour(terrain_colour[1][58],134,71,39,255);
set_rgb_colour(terrain_colour[1][59],125,65,34,255);
set_rgb_colour(terrain_colour[1][60],116,59,29,255);
set_rgb_colour(terrain_colour[1][61],106,53,23,255);
set_rgb_colour(terrain_colour[1][62],96,48,18,255);
set_rgb_colour(terrain_colour[1][63],86,42,12,255);
set_rgb_colour(terrain_colour[1][64],86,42,12,255);
                                 
//green - yellow - red           
/*
set_rgb_colour(terrain_colour[2][0],100, 150, 240, 255);
	set_rgb_colour(terrain_colour[2][32],90,59,27,255);
	set_rgb_colour(terrain_colour[2][31],105,59,27,255);
	set_rgb_colour(terrain_colour[2][30],119,61,28,255);
	set_rgb_colour(terrain_colour[2][29],131,65,30,255);
	set_rgb_colour(terrain_colour[2][28],141,70,34,255);
	set_rgb_colour(terrain_colour[2][27],150,77,39,255);
	set_rgb_colour(terrain_colour[2][26],157,85,44,255);
	set_rgb_colour(terrain_colour[2][25],163,94,50,255);
	set_rgb_colour(terrain_colour[2][24],169,102,57,255);
	set_rgb_colour(terrain_colour[2][23],173,111,63,255);
	set_rgb_colour(terrain_colour[2][22],176,119,70,255);
	set_rgb_colour(terrain_colour[2][21],179,127,76,255);
	set_rgb_colour(terrain_colour[2][20],182,134,81,255);
	set_rgb_colour(terrain_colour[2][19],184,139,85,255);
	set_rgb_colour(terrain_colour[2][18],186,143,89,255);
	set_rgb_colour(terrain_colour[2][17],188,144,91,255);
	set_rgb_colour(terrain_colour[2][16],191,144,91,255);
	set_rgb_colour(terrain_colour[2][15],207,159,102,255);
	set_rgb_colour(terrain_colour[2][14],214,169,110,255);
	set_rgb_colour(terrain_colour[2][13],217,177,119,255);
	set_rgb_colour(terrain_colour[2][12],216,183,128,255);
	set_rgb_colour(terrain_colour[2][11],212,188,136,255);
	set_rgb_colour(terrain_colour[2][10],205,192,143,255);
	set_rgb_colour(terrain_colour[2][9],194,194,149,255);
	set_rgb_colour(terrain_colour[2][8],181,194,154,255);
	set_rgb_colour(terrain_colour[2][7],166,193,156,255);
	set_rgb_colour(terrain_colour[2][6],149,191,157,255);
	set_rgb_colour(terrain_colour[2][5],130,188,155,255);
	set_rgb_colour(terrain_colour[2][4],110,183,150,255);
	set_rgb_colour(terrain_colour[2][3],88,177,142,255);
	set_rgb_colour(terrain_colour[2][2],65,170,130,255);
	set_rgb_colour(terrain_colour[2][1],42,162,114,255);
*/ 
set_rgb_colour(terrain_colour[2][0],100, 150, 240, 255);
set_rgb_colour(terrain_colour[2][1 ],42,162,114,255);
set_rgb_colour(terrain_colour[2][2 ],54,166,122,255);
set_rgb_colour(terrain_colour[2][3 ],65,170,130,255);
set_rgb_colour(terrain_colour[2][4 ],77,174,136,255);
set_rgb_colour(terrain_colour[2][5 ],88,177,142,255);
set_rgb_colour(terrain_colour[2][6 ],99,180,146,255);
set_rgb_colour(terrain_colour[2][7 ],110,183,150,255);
set_rgb_colour(terrain_colour[2][8 ],120,186,153,255);
set_rgb_colour(terrain_colour[2][9 ],130,188,155,255);
set_rgb_colour(terrain_colour[2][10],140,190,156,255);
set_rgb_colour(terrain_colour[2][11],149,191,157,255);
set_rgb_colour(terrain_colour[2][12],158,192,157,255);
set_rgb_colour(terrain_colour[2][13],166,193,156,255);
set_rgb_colour(terrain_colour[2][14],174,194,155,255);
set_rgb_colour(terrain_colour[2][15],181,194,154,255);
set_rgb_colour(terrain_colour[2][16],188,194,152,255);
set_rgb_colour(terrain_colour[2][17],194,194,149,255);
set_rgb_colour(terrain_colour[2][18],200,193,146,255);
set_rgb_colour(terrain_colour[2][19],205,192,143,255);
set_rgb_colour(terrain_colour[2][20],209,190,140,255);
set_rgb_colour(terrain_colour[2][21],212,188,136,255);
set_rgb_colour(terrain_colour[2][22],214,186,132,255);
set_rgb_colour(terrain_colour[2][23],216,183,128,255);
set_rgb_colour(terrain_colour[2][24],217,180,124,255);
set_rgb_colour(terrain_colour[2][25],217,177,119,255);
set_rgb_colour(terrain_colour[2][26],216,173,115,255);
set_rgb_colour(terrain_colour[2][27],214,169,110,255);
set_rgb_colour(terrain_colour[2][28],211,164,106,255);
set_rgb_colour(terrain_colour[2][29],207,159,102,255);
set_rgb_colour(terrain_colour[2][30],199,152,97,255);
set_rgb_colour(terrain_colour[2][31],191,144,91,255);
set_rgb_colour(terrain_colour[2][32],190,144,91,255);
set_rgb_colour(terrain_colour[2][33],188,144,91,255);
set_rgb_colour(terrain_colour[2][34],187,144,90,255);
set_rgb_colour(terrain_colour[2][35],186,143,89,255);
set_rgb_colour(terrain_colour[2][36],185,141,87,255);
set_rgb_colour(terrain_colour[2][37],184,139,85,255);
set_rgb_colour(terrain_colour[2][38],183,137,83,255);
set_rgb_colour(terrain_colour[2][39],182,134,81,255);
set_rgb_colour(terrain_colour[2][40],181,131,79,255);
set_rgb_colour(terrain_colour[2][41],179,127,76,255);
set_rgb_colour(terrain_colour[2][42],178,123,73,255);
set_rgb_colour(terrain_colour[2][43],176,119,70,255);
set_rgb_colour(terrain_colour[2][44],175,115,67,255);
set_rgb_colour(terrain_colour[2][45],173,111,63,255);
set_rgb_colour(terrain_colour[2][46],171,107,60,255);
set_rgb_colour(terrain_colour[2][47],169,102,57,255);
set_rgb_colour(terrain_colour[2][48],166,98,54,255);
set_rgb_colour(terrain_colour[2][49],163,94,50,255);
set_rgb_colour(terrain_colour[2][50],160,90,47,255);
set_rgb_colour(terrain_colour[2][51],157,85,44,255);
set_rgb_colour(terrain_colour[2][52],154,81,42,255);
set_rgb_colour(terrain_colour[2][53],150,77,39,255);
set_rgb_colour(terrain_colour[2][54],146,74,37,255);
set_rgb_colour(terrain_colour[2][55],141,70,34,255);
set_rgb_colour(terrain_colour[2][56],136,68,32,255);
set_rgb_colour(terrain_colour[2][57],131,65,30,255);
set_rgb_colour(terrain_colour[2][58],125,63,29,255);
set_rgb_colour(terrain_colour[2][59],119,61,28,255);
set_rgb_colour(terrain_colour[2][60],112,60,28,255);
set_rgb_colour(terrain_colour[2][61],105,59,27,255);
set_rgb_colour(terrain_colour[2][62],98,59,27,255);
set_rgb_colour(terrain_colour[2][63],90,59,27,255);
set_rgb_colour(terrain_colour[2][64],90,59,27,255);

// Made with hue: 0.32 - 0.02, value: 0.40 - 0.60, saturation: 0.50 - 0.45
set_rgb_colour(terrain_colour[3][ 0],100,150,240,255);
set_rgb_colour(terrain_colour[3][ 1], 55,102, 51,255);
set_rgb_colour(terrain_colour[3][ 2], 58,103, 51,255);
set_rgb_colour(terrain_colour[3][ 3], 62,105, 52,255);
set_rgb_colour(terrain_colour[3][ 4], 67,106, 53,255);
set_rgb_colour(terrain_colour[3][ 5], 71,108, 54,255);
set_rgb_colour(terrain_colour[3][ 6], 75,109, 55,255);
set_rgb_colour(terrain_colour[3][ 7], 79,111, 56,255);
set_rgb_colour(terrain_colour[3][ 8], 84,113, 57,255);
set_rgb_colour(terrain_colour[3][ 9], 88,114, 58,255);
set_rgb_colour(terrain_colour[3][10], 92,116, 59,255);
set_rgb_colour(terrain_colour[3][11], 97,117, 60,255);
set_rgb_colour(terrain_colour[3][12],102,119, 61,255);
set_rgb_colour(terrain_colour[3][13],106,121, 62,255);
set_rgb_colour(terrain_colour[3][14],111,122, 63,255);
set_rgb_colour(terrain_colour[3][15],116,124, 64,255);
set_rgb_colour(terrain_colour[3][16],121,125, 65,255);
set_rgb_colour(terrain_colour[3][17],126,127, 66,255);
set_rgb_colour(terrain_colour[3][18],129,126, 67,255);
set_rgb_colour(terrain_colour[3][19],130,124, 69,255);
set_rgb_colour(terrain_colour[3][20],132,123, 70,255);
set_rgb_colour(terrain_colour[3][21],133,121, 71,255);
set_rgb_colour(terrain_colour[3][22],135,118, 72,255);
set_rgb_colour(terrain_colour[3][23],137,116, 73,255);
set_rgb_colour(terrain_colour[3][24],138,114, 74,255);
set_rgb_colour(terrain_colour[3][25],140,112, 75,255);
set_rgb_colour(terrain_colour[3][26],141,110, 76,255);
set_rgb_colour(terrain_colour[3][27],143,107, 77,255);
set_rgb_colour(terrain_colour[3][28],145,105, 78,255);
set_rgb_colour(terrain_colour[3][29],146,102, 79,255);
set_rgb_colour(terrain_colour[3][30],148,100, 80,255);
set_rgb_colour(terrain_colour[3][31],149, 97, 81,255);
set_rgb_colour(terrain_colour[3][32],151, 95, 83,255);
set_rgb_colour(terrain_colour[3][33],152, 92, 84,255);
set_rgb_colour(terrain_colour[3][34],156, 98, 90,255);
set_rgb_colour(terrain_colour[3][35],159,104, 96,255);
set_rgb_colour(terrain_colour[3][36],162,110,103,255);
set_rgb_colour(terrain_colour[3][37],166,116,110,255);
set_rgb_colour(terrain_colour[3][38],169,123,117,255);
set_rgb_colour(terrain_colour[3][39],172,129,124,255);
set_rgb_colour(terrain_colour[3][40],176,136,131,255);
set_rgb_colour(terrain_colour[3][41],179,143,138,255);
set_rgb_colour(terrain_colour[3][42],182,150,146,255);
set_rgb_colour(terrain_colour[3][43],185,158,154,255);
set_rgb_colour(terrain_colour[3][44],189,165,162,255);
set_rgb_colour(terrain_colour[3][45],192,173,170,255);
set_rgb_colour(terrain_colour[3][46],195,181,179,255);
set_rgb_colour(terrain_colour[3][47],199,189,187,255);
set_rgb_colour(terrain_colour[3][48],202,197,196,255);
set_rgb_colour(terrain_colour[3][49],205,205,205,255);
set_rgb_colour(terrain_colour[3][50],208,208,208,255);
set_rgb_colour(terrain_colour[3][51],212,212,212,255);
set_rgb_colour(terrain_colour[3][52],215,215,215,255);
set_rgb_colour(terrain_colour[3][53],218,218,218,255);
set_rgb_colour(terrain_colour[3][54],222,222,222,255);
set_rgb_colour(terrain_colour[3][55],225,225,225,255);
set_rgb_colour(terrain_colour[3][56],228,228,228,255);
set_rgb_colour(terrain_colour[3][57],231,231,231,255);
set_rgb_colour(terrain_colour[3][58],235,235,235,255);
set_rgb_colour(terrain_colour[3][59],238,238,238,255);
set_rgb_colour(terrain_colour[3][60],241,241,241,255);
set_rgb_colour(terrain_colour[3][61],245,245,245,255);
set_rgb_colour(terrain_colour[3][62],248,248,248,255);
set_rgb_colour(terrain_colour[3][63],251,251,251,255);
set_rgb_colour(terrain_colour[3][64],255,255,255,255);

		// Made with hue: 0.32 - 0.02, value: 0.85 - 0.80, saturation: 0.10 - 0.15
set_rgb_colour(paper_colour[ 0],150,200,240,255);
set_rgb_colour(paper_colour[ 1],196,216,195,255);
set_rgb_colour(paper_colour[ 2],197,216,194,255);
set_rgb_colour(paper_colour[ 3],197,215,193,255);
set_rgb_colour(paper_colour[ 4],198,215,192,255);
set_rgb_colour(paper_colour[ 5],199,215,192,255);
set_rgb_colour(paper_colour[ 6],199,214,191,255);
set_rgb_colour(paper_colour[ 7],200,214,190,255);
set_rgb_colour(paper_colour[ 8],201,213,190,255);
set_rgb_colour(paper_colour[ 9],202,213,189,255);
set_rgb_colour(paper_colour[10],203,213,188,255);
set_rgb_colour(paper_colour[11],203,212,188,255);
set_rgb_colour(paper_colour[12],204,212,187,255);
set_rgb_colour(paper_colour[13],205,211,186,255);
set_rgb_colour(paper_colour[14],206,211,186,255);
set_rgb_colour(paper_colour[15],207,211,185,255);
set_rgb_colour(paper_colour[16],208,210,184,255);
set_rgb_colour(paper_colour[17],209,210,184,255);
set_rgb_colour(paper_colour[18],209,209,183,255);
set_rgb_colour(paper_colour[19],209,207,182,255);
set_rgb_colour(paper_colour[20],209,205,182,255);
set_rgb_colour(paper_colour[21],208,203,181,255);
set_rgb_colour(paper_colour[22],208,201,180,255);
set_rgb_colour(paper_colour[23],207,199,180,255);
set_rgb_colour(paper_colour[24],207,197,179,255);
set_rgb_colour(paper_colour[25],207,194,178,255);
set_rgb_colour(paper_colour[26],206,192,178,255);
set_rgb_colour(paper_colour[27],206,190,177,255);
set_rgb_colour(paper_colour[28],205,188,176,255);
set_rgb_colour(paper_colour[29],205,186,176,255);
set_rgb_colour(paper_colour[30],205,183,175,255);
set_rgb_colour(paper_colour[31],204,181,174,255);
set_rgb_colour(paper_colour[32],204,179,174,255);
set_rgb_colour(paper_colour[33],203,177,173,255);
set_rgb_colour(paper_colour[34],205,180,176,255);
set_rgb_colour(paper_colour[35],207,183,180,255);
set_rgb_colour(paper_colour[36],208,186,183,255);
set_rgb_colour(paper_colour[37],210,189,186,255);
set_rgb_colour(paper_colour[38],212,192,190,255);
set_rgb_colour(paper_colour[39],213,196,193,255);
set_rgb_colour(paper_colour[40],215,199,197,255);
set_rgb_colour(paper_colour[41],217,202,200,255);
set_rgb_colour(paper_colour[42],218,206,204,255);
set_rgb_colour(paper_colour[43],220,209,208,255);
set_rgb_colour(paper_colour[44],222,212,211,255);
set_rgb_colour(paper_colour[45],223,216,215,255);
set_rgb_colour(paper_colour[46],225,219,219,255);
set_rgb_colour(paper_colour[47],227,223,222,255);
set_rgb_colour(paper_colour[48],228,226,226,255);
set_rgb_colour(paper_colour[49],230,230,230,255);
set_rgb_colour(paper_colour[50],231,231,231,255);
set_rgb_colour(paper_colour[51],233,233,233,255);
set_rgb_colour(paper_colour[52],235,235,235,255);
set_rgb_colour(paper_colour[53],236,236,236,255);
set_rgb_colour(paper_colour[54],238,238,238,255);
set_rgb_colour(paper_colour[55],240,240,240,255);
set_rgb_colour(paper_colour[56],241,241,241,255);
set_rgb_colour(paper_colour[57],243,243,243,255);
set_rgb_colour(paper_colour[58],245,245,245,255);
set_rgb_colour(paper_colour[59],246,246,246,255);
set_rgb_colour(paper_colour[60],248,248,248,255);
set_rgb_colour(paper_colour[61],250,250,250,255);
set_rgb_colour(paper_colour[62],251,251,251,255);
set_rgb_colour(paper_colour[63],253,253,253,255);
set_rgb_colour(paper_colour[64],254,254,254,255);

}                                

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_map_coords_from_world(vec3d* source_pos, float scale, vec3d* world_pos, float* screen_x, float* screen_y)
{
	*screen_x = (world_pos->x - source_pos->x) * scale;
	*screen_y = (world_pos->z - source_pos->z) * scale;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                 
static void draw_contour_lines (vec3d *p1, vec3d *p2, vec3d *p3)
{                                
	int                           
		y,                         
		y1,                        
		y2,                        
		y3,                        
		dy,                        
		y_tmp,                     
		contour_samples_minus_one; 
                                 
	float                         
		x1,                        
		z1,                        
		x2,                        
		z2,                        
		x3,                        
		z3,                        
		dx1,                       
		dz1,                       
		dx2,                       
		dz2,                       
		x_tmp,                     
		z_tmp,                     
		one_over_dy;               
                                 
	x1 = p1->x;                   
	convert_float_to_int (p1->y, &y1);
	z1 = p1->z;                   
                                 
	x2 = p2->x;                   
	convert_float_to_int (p2->y, &y2);
	z2 = p2->z;                   
                                 
	x3 = p3->x;                   
	convert_float_to_int (p3->y, &y3);
	z3 = p3->z;                   
                                 
	//                            
	// ensure above sea level     
	//                            
                                 
	y1 = max (y1, 0);             
                                 
	y2 = max (y2, 0);             
                                 
	y3 = max (y3, 0);             
                                 
	//                            
	// scale height values for contour line spacing
	//                            
                                 
	y1 /= contour_spacing;        
	y2 /= contour_spacing;        
	y3 /= contour_spacing;        
                                 
	contour_samples_minus_one = contour_samples - 1;
                                 
	//                            
	// check if flat              
	//                            
                                 
	if ((y1 == y2) && (y2 == y3)) 
	{                             
		return;                    
	}                             
                                 
	//                            
	// sort height values (y1 = lowest, y3 = highest)
	//                            
                                 
	if (y1 > y3)                  
	{                             
		x_tmp = x1;                
		y_tmp = y1;                
		z_tmp = z1;                
                                 
		x1 = x3;                   
		y1 = y3;                   
		z1 = z3;                   
                                 
		x3 = x_tmp;                
		y3 = y_tmp;                
		z3 = z_tmp;                
	}                             
                                 
	if (y2 > y3)                  
	{                             
		x_tmp = x2;                
		y_tmp = y2;                
		z_tmp = z2;                
                                 
		x2 = x3;                   
		y2 = y3;                   
		z2 = z3;                   
                                 
		x3 = x_tmp;                
		y3 = y_tmp;                
		z3 = z_tmp;                
	}                             
                                 
	if (y1 > y2)                  
	{                             
		x_tmp = x1;                
		y_tmp = y1;                
		z_tmp = z1;                
                                 
		x1 = x2;                   
		y1 = y2;                   
		z1 = z2;                   
                                 
		x2 = x_tmp;                
		y2 = y_tmp;                
		z2 = z_tmp;                
	}                             
                                 
	//                            
	// draw contour lines         
	//                            
                                 
	if (y1 == y2)                 
	{                             
		dy = y3 - y1;              
                                 
		one_over_dy = 1.0 / (float) dy;
                                 
		dx1 = (x3 - x1) * one_over_dy;
		dz1 = (z3 - z1) * one_over_dy;
		dx2 = (x3 - x2) * one_over_dy;
		dz2 = (z3 - z2) * one_over_dy;
                                 
		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);
                                 
		while (dy--)               
		{                          
			#if OPTIMISE_CONTOURS   
                                 
			num_contour_loops++;    
                                 
			#endif                  
                                 
			if (y == 0)             
			{                       
				#if OPTIMISE_CONTOURS
                                 
				num_contour_lines++; 
                                 
				#endif               
                                 
				y = contour_samples; 
                                 
				draw_2d_line (x1, z1, x2, z2, map_contour_colour);
			}                       
                                 
			y--;                    
                                 
			x1 += dx1;              
			z1 += dz1;              
			x2 += dx2;              
			z2 += dz2;              
		}                          
	}                             
	else if (y2 == y3)            
	{                             
		dy = y2 - y1;              
                                 
		one_over_dy = 1.0 / (float) dy;
                                 
		dx1 = (x2 - x1) * one_over_dy;
		dz1 = (z2 - z1) * one_over_dy;
		dx2 = (x3 - x1) * one_over_dy;
		dz2 = (z3 - z1) * one_over_dy;
                                 
		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);
                                 
		x2 = x1;                   
		z2 = z1;                   
                                 
		while (dy--)               
		{                          
			#if OPTIMISE_CONTOURS   
                                 
			num_contour_loops++;    
                                 
			#endif                  
                                 
			if (y == 0)             
			{                       
				#if OPTIMISE_CONTOURS
                                 
				num_contour_lines++; 
                                 
				#endif               
                                 
				y = contour_samples; 
                                 
				draw_2d_line (x1, z1, x2, z2, map_contour_colour);
                                 
			}                       
                                 
			y--;                    
                                 
			x1 += dx1;              
			z1 += dz1;              
			x2 += dx2;              
			z2 += dz2;              
		}                          
	}                             
	else                          
	{                             
		dy = y3 - y1;              
                                 
		one_over_dy = 1.0 / (float) dy;
                                 
		dx1 = (x3 - x1) * one_over_dy;
		dz1 = (z3 - z1) * one_over_dy;
                                 
		dy = y2 - y1;              
                                 
		one_over_dy = 1.0 / (float) dy;
                                 
		dx2 = (x2 - x1) * one_over_dy;
		dz2 = (z2 - z1) * one_over_dy;
                                 
		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);
                                 
		x2 = x1;                   
		z2 = z1;                   
                                 
		while (dy--)               
		{                          
			#if OPTIMISE_CONTOURS   
                                 
			num_contour_loops++;    
                                 
			#endif                  
                                 
			if (y == 0)             
			{                       
				#if OPTIMISE_CONTOURS
                                 
				num_contour_lines++; 
                                 
				#endif               
                                 
				y = contour_samples; 
                                 
				draw_2d_line (x1, z1, x2, z2, map_contour_colour);
                                 
			}                       
                                 
			y--;                    
                                 
			x1 += dx1;              
			z1 += dz1;              
			x2 += dx2;              
			z2 += dz2;              
		}                          
                                 
		dy = y3 - y2;              
                                 
		one_over_dy = 1.0 / (float) dy;
                                 
		dx2 = (x3 - x2) * one_over_dy;
		dz2 = (z3 - z2) * one_over_dy;
                                 
		y = contour_samples_minus_one - ((y2 - 1) % contour_samples);
                                 
		while (dy--)               
		{                          
			#if OPTIMISE_CONTOURS   
                                 
			num_contour_loops++;    
                                 
			#endif                  
                                 
			if (y == 0)             
			{                       
				#if OPTIMISE_CONTOURS
                                 
				num_contour_lines++; 
                                 
				#endif               
                                 
				y = contour_samples; 
                                 
				draw_2d_line (x1, z1, x2, z2, map_contour_colour);
			}                       
                                 
			y--;                    
                                 
			x1 += dx1;              
			z1 += dz1;              
			x2 += dx2;              
			z2 += dz2;              
		}                          
	}                             
}                                
                                 
                                 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                 
static void draw_path_lines      
(                                
	int number_of_paths,          
	contour_path *paths,          
	vec3d *nodes,                 
	rgb_colour colour,            
	int detail_level,             
	float x_world_min,            
	float z_world_min,            
	float x_world_mid,            
	float z_world_mid,            
	float x_world_max,            
	float z_world_max,            
	float scale,                  
	int draw_thick_lines,         
	int draw_large_mfd            
)                                
{                                
	int                           
		this_path,                 
		outcode1,                  
		outcode2,                  
		index,                     
		step_size;                 
                                 
	#if OPTIMISE_PATHS            
                                 
	int                           
		num_paths_traversed,       
		num_lines_drawn;           
                                 
	#endif                        
                                 
	float                         
		x1,                        
		z1,                        
		x2,                        
		z2;                        
                                 
	vec3d                         
		*sub_positions;            
                                 
//	ASSERT (number_of_paths > 0);
	if (number_of_paths <= 0)
		return;
                                 
	ASSERT (paths);               
                                 
	ASSERT (nodes);               
                                 
	#if OPTIMISE_PATHS            
                                 
	num_paths_traversed = 0;      
                                 
	num_lines_drawn = 0;          
                                 
	#endif                        
                                 
	step_size = max (detail_level << 3, 1);
                                 
	for (this_path = 0; this_path < number_of_paths; this_path++)
	{                             
		if                         
		(                          
			(paths[this_path].type != TEMP_TERRAIN_TYPE_COASTAL_RIVER) &&
			(paths[this_path].type != TEMP_TERRAIN_TYPE_LAKE) &&
			(paths[this_path].type != TEMP_TERRAIN_TYPE_OFFROAD)
		)                          
		{                          
			//                      
			// trivially reject path
			//                      
                                 
			outcode1 = 0;           
                                 
			if (paths[this_path].xmin < x_world_min) outcode1 |= CLIP_LEFT;
			if (paths[this_path].xmin > x_world_max) outcode1 |= CLIP_RIGHT;
			if (paths[this_path].zmin < z_world_min) outcode1 |= CLIP_TOP;
			if (paths[this_path].zmin > z_world_max) outcode1 |= CLIP_BOTTOM;
                                 
			outcode2 = 0;           
                                 
			if (paths[this_path].xmax < x_world_min) outcode2 |= CLIP_LEFT;
			if (paths[this_path].xmax > x_world_max) outcode2 |= CLIP_RIGHT;
			if (paths[this_path].zmax < z_world_min) outcode2 |= CLIP_TOP;
			if (paths[this_path].zmax > z_world_max) outcode2 |= CLIP_BOTTOM;
                                 
			if (!(outcode1 & outcode2))
			{                       
				#if OPTIMISE_PATHS   
                                 
				num_paths_traversed++;
                                 
				#endif               
                                 
				//                   
				// this also catches conditions where (count == 0)
				//                   
                                 
				if (paths[this_path].count <= step_size)
				{                    
					////////////////////////////////////////
					//                
					// draw path as a single line
					//                
					////////////////////////////////////////
                                 
					x1 = (nodes[paths[this_path].from].x - x_world_mid) * scale;
					z1 = (nodes[paths[this_path].from].z - z_world_mid) * scale;
                                 
					x2 = (nodes[paths[this_path].to].x - x_world_mid) * scale;
					z2 = (nodes[paths[this_path].to].z - z_world_mid) * scale;
                                 
					if (draw_thick_lines && draw_large_mfd)
					{                 
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}                 
					else              
					{                 
						draw_2d_line (x1, z1, x2, z2, colour);
					}                 
                                 
					#if OPTIMISE_PATHS
                                 
					num_lines_drawn++;
                                 
					#endif            
				}                    
				else                 
				{                    
					////////////////////////////////////////
					//                
					// draw path with variable detail level
					//                
					////////////////////////////////////////
                                 
					sub_positions = paths[this_path].points;
                                 
					index = step_size - 1;;
                                 
					//                
					// draw line from start node to first sub-position
					//                
                                 
					x1 = (nodes[paths[this_path].from].x - x_world_mid) * scale;
					z1 = (nodes[paths[this_path].from].z - z_world_mid) * scale;
                                 
					x2 = (sub_positions[index].x - x_world_mid) * scale;
					z2 = (sub_positions[index].z - z_world_mid) * scale;
                                 
					if (draw_thick_lines && draw_large_mfd)
					{                 
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}                 
					else              
					{                 
						draw_2d_line (x1, z1, x2, z2, colour);
					}                 
                                 
					#if OPTIMISE_PATHS
                                 
					num_lines_drawn++;
                                 
					#endif            
                                 
					//                
					// draw sub-position lines
					//                
                                 
					index += step_size;
                                 
					while (index < paths[this_path].count)
					{                 
						x1 = x2;       
						z1 = z2;       
                                 
						x2 = (sub_positions[index].x - x_world_mid) * scale;
						z2 = (sub_positions[index].z - z_world_mid) * scale;
                                 
						if (draw_thick_lines && draw_large_mfd)
						{              
							draw_2d_half_thick_line (x1, z1, x2, z2, colour);
						}              
						else           
						{              
							draw_2d_line (x1, z1, x2, z2, colour);
						}              
                                 
						#if OPTIMISE_PATHS
                                 
						num_lines_drawn++;
                                 
						#endif         
                                 
						index += step_size;
					}                 
                                 
					//                
					// draw line from last sub-position to end node
					//                
                                 
					x1 = x2;          
					z1 = z2;          
                                 
					x2 = (nodes[paths[this_path].to].x - x_world_mid) * scale;
					z2 = (nodes[paths[this_path].to].z - z_world_mid) * scale;
                                 
					if (draw_thick_lines && draw_large_mfd)
					{                 
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}                 
					else              
					{                 
						draw_2d_line (x1, z1, x2, z2, colour);
					}                 
                                 
					#if OPTIMISE_PATHS
                                 
					num_lines_drawn++;
                                 
					#endif            
				}                    
			}                       
		}                          
	}                             
                                 
	#if OPTIMISE_PATHS            
                                 
	debug_filtered_log ("paths=%d, paths drawn=%d, lines drawn=%d", number_of_paths, num_paths_traversed, num_lines_drawn);
                                 
	#endif                        
}                                
                                 
                                 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                 
//VJ 030511 added a simple shader based on the aspect of a gridcell
float get_aspect(float z1, float z2, float z3, float z4)
{                                
//z1, z2 in x direction, z3, z4 in z direction
	float _b, _c, aspect, asp_corr;
                                 
	// dx/dy = E-W derivative     
	_b = z3+z4 - (z1+z2);         
	// dz/dy = N-S derivative     
	_c = z2+z4 - (z1+z3);         
	aspect = (_c != 0 ? atan(_b/_c) : 0);
	if (_b <= 0 && _c <= 0) asp_corr = 4.7123890;// rad(270);
	if (_b >  0 && _c <= 0) asp_corr = -1.5707963;// rad(-90);
	if (_b <= 0 && _c >  0) asp_corr = -4.7123890;//rad(-270);
	if (_b >  0 && _c >  0) asp_corr = 1.5707963;//rad(90);
	// simple shader              
                                 
	//rad(-45) is sun from NW when chopper is facing N
	aspect = 0.5+0.25*(cos(aspect+asp_corr-0.7853982)+1); //rad(-45)
	return(aspect);               
	                              
}                                
                                 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                 
void draw_tsd_terrain_map (env_2d *mfd_env, float y_translate, float range, float scale, vec3d *position, float heading, int paper_map)
{                                
	int                           
		x_index,                   
		z_index,                   
		row_add_on,                
		x_min_index,               
		z_min_index,               
		x_max_index,               
		z_max_index;               
                                 
	float                         
		x_min,                     
		z_min,                     
		x_mid,                     
		z_mid,                     
		x_max,                     
		z_max,                     
		radius,                    
		distance,                  
		dx0,                       
		dz0,                       
		dx1,                       
		dz1,                       
		dx_grid,                   
		dz_grid,                   
		dx_start,                  
		dz_start,                  
		*this_row_ptr,             
		*next_row_ptr,             
		*this_row_start_ptr,       
		*next_row_start_ptr,       
		*aspectrow,                
		*old_aspectrow;            
                                 
	float                         
		terrain_elev=0,            
		elevation_factor=terrain_3d_map_maximum_height*0.97;
                                 
	rgb_colour                    
		terrain_col;               
                                 
	int step = 1, aspect_index, nr_aspect_steps, do_it = 0;
	int stepmask;                 
	                              
//VJ 051006 simplified code, lower detail but better framerate
	unsigned int doaspect = (tsd_render_mode == TSD_RENDER_CONTOUR_SHADED_RELIEF_MODE ||
  							tsd_render_mode == TSD_RENDER_SHADED_RELIEF_MODE);

	if (paper_map)
		map_palette = paper_colour;
	else
		map_palette = terrain_colour[tsd_render_palette];
                                 
	ASSERT (position);            

                                 
	//                            
	// rotate map                 
	//                            
                                 
	set_2d_window_rotation (mfd_env, heading);
                                 
	//                            
	// get map centre position    
	//                            
                                 
	distance = y_translate / scale;
                                 
	x_mid = position->x + (distance * sin (heading));
	z_mid = position->z + (distance * cos (heading));
                                 
	//                            
	// get map area (increased by one grid, where hypotenuse is approx (x + z))
	//                            
                                 
	radius = range + terrain_3d_simple_elevation_x_grid_size + terrain_3d_simple_elevation_z_grid_size;
                                 
	x_min = x_mid - radius;       
	z_min = z_mid - radius;       
                                 
	x_max = x_mid + radius;       
	z_max = z_mid + radius;       
                                 
	//                            
	// clip map area              
	//                            
                                 
	x_min = max (x_min, MIN_MAP_X);
	z_min = max (z_min, MIN_MAP_Z);
                                 
	x_max = min (x_max, MAX_MAP_X);
	z_max = min (z_max, MAX_MAP_Z);
                                 
                                 
	//                            
	// get simple terrain map indices
	//                            
                                 
	convert_float_to_int ((x_min * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_min_index);
	convert_float_to_int ((z_min * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_min_index);
                                 
	convert_float_to_int ((x_max * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_max_index);
	convert_float_to_int ((z_max * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_max_index);
                                 
//VJ 051006 simplified code, lower detail but better framerate
//this gives the better framerate in fact, simply drawing much less triangles
 //  if (range > TSD_ASE_RANGE_10000)
   //  step = 2;                   
//VJ 061213 toggle TSD colour grid detail level
  if (global_tsd_detail == 0)
  	if(range >= TSD_ASE_RANGE_10000)
     step = 2;                   
                                 
   stepmask = ~(step - 1);       
                                 
	//                            
	// scan map                   
	//                            
                                 
	x_min_index &= stepmask;      
	z_min_index &= stepmask;      
                                 
	x_max_index += step - 1;      
	z_max_index += step - 1;      
                                 
	x_max_index &= stepmask;      
	z_max_index &= stepmask;      
                                 
	if (x_max_index >= terrain_3d_simple_elevation_width)
	{                             
		x_max_index = terrain_3d_simple_elevation_width & stepmask;
	}                             
                                 
	if (z_max_index >= terrain_3d_simple_elevation_height)
	{                             
		z_max_index = terrain_3d_simple_elevation_height & stepmask;
	}                             
                                 
	if ((x_min_index < x_max_index) && (z_min_index < z_max_index))
	{                             
		this_row_start_ptr = &terrain_3d_simple_elevation_grid[(z_min_index * terrain_3d_simple_elevation_width) + x_min_index];
                                 
		row_add_on = terrain_3d_simple_elevation_width * step;
                                 
		next_row_start_ptr = this_row_start_ptr + row_add_on;
                                 
		dx_start = ((((float) x_min_index) * terrain_3d_simple_elevation_x_grid_size) - x_mid) * scale;
		dz_start = ((((float) z_min_index) * terrain_3d_simple_elevation_z_grid_size) - z_mid) * scale;
                                 
		dx_grid = terrain_3d_simple_elevation_x_grid_size * (float) step * scale;
		dz_grid = terrain_3d_simple_elevation_z_grid_size * (float) step * scale;
                                 
		dz0 = dz_start;            
		dz1 = dz_start + dz_grid;  
                                 
		//VJ 030511 store shade of pixels above and to the left for averaging
		if (doaspect)              
	  	{                          
			nr_aspect_steps = (int)((z_max_index-z_min_index)/dz_grid);
			aspectrow = (float*)malloc(sizeof(float)*nr_aspect_steps);
			old_aspectrow = (float*)malloc(sizeof(float)*nr_aspect_steps);
		}                          
		                           
		for (z_index = z_min_index; z_index < z_max_index; z_index += step)
		{                          
                                 
			dx0 = dx_start;         
			dx1 = dx_start + dx_grid;
                                                                 
			this_row_ptr = this_row_start_ptr;
			next_row_ptr = next_row_start_ptr;
                                 
	    aspect_index = 0;       
			for (x_index = x_min_index; x_index < x_max_index; x_index += step)
			{                       
				int c = 0;           
				float oa = 1.0, aspect=1.0, old_aspect_x=1.0;
                                 
				//VJ 030511 aspect is in fact a shade factor beteen 0.5 and 1.0
   			if (doaspect)        
	   		{                    
	   			oa = get_aspect(this_row_ptr[0],this_row_ptr[1],next_row_ptr[0],next_row_ptr[1]);
					aspect = oa;      
					
			   	if (x_index > x_min_index && z_index == z_min_index)
            	{                 
            		aspect = (3*aspect+old_aspect_x)/4.0;
            	}     
            	            
			   	if (z_index > z_min_index)
            	{                 
            		aspect = (4*aspect+old_aspect_x+old_aspectrow[aspect_index])/6.0;//old_aspectrow[aspect_index-1]
            	}          
            
            	#if DEBUG_ASPECT  
						terrain_col.r = (int)(aspect*255);
						terrain_col.g = (int)(aspect*255);
						terrain_col.b = 0;//(int)aspect*255;
						terrain_col.a = 255;
			   		draw_2d_filled_triangle (dx0,dz0,dx0,dz1,dx1,dz1,terrain_col);
			   		draw_2d_filled_triangle (dx0,dz0,dx1,dz1,dx1,dz0,terrain_col);
			   	#endif            
				}               
				     
			// VJ 060125 split each grid cell into 4 triagles when at a low radar range
			// else draw 1 square grid cell, gives better framerate at 10 and 25 km radar range
	    if (global_tsd_detail == 1)
			  do_it = 1;	    	
			if (range < TSD_ASE_RANGE_10000)
			  do_it = 1;
			  
			if (do_it == 1)	
			{
				float mid_z = 0.5*(dz0+dz1);  
				float mid_x = 0.5*(dx0+dx1);
			   float mid_y = (this_row_ptr[0]+this_row_ptr[1]+next_row_ptr[0]+next_row_ptr[1])/4.0;
			                        
			   terrain_elev = (this_row_ptr[0]+this_row_ptr[1]+mid_y)/3.0;
			   c = COLOUR_SCALE(terrain_elev);
			  	GET_TERRAIN_COLOUR(terrain_col, c, aspect);
			   draw_2d_filled_triangle (dx0,dz0,mid_x,mid_z,dx1,dz0,terrain_col);
			                              
			   terrain_elev = (this_row_ptr[1]+next_row_ptr[1]+mid_y)/3.0;
			   c = COLOUR_SCALE(terrain_elev);
			  	GET_TERRAIN_COLOUR(terrain_col, c, aspect);
			   draw_2d_filled_triangle (dx1,dz0,mid_x,mid_z,dx1,dz1,terrain_col);
			                              
			   terrain_elev = (this_row_ptr[0]+next_row_ptr[0]+mid_y)/3.0;
			   c = COLOUR_SCALE(terrain_elev);
			  	GET_TERRAIN_COLOUR(terrain_col, c, aspect);
			   draw_2d_filled_triangle (dx0,dz0,dx0,dz1,mid_x,mid_z,terrain_col);
			                              
			   terrain_elev = (next_row_ptr[0]+next_row_ptr[1]+mid_y)/3.0;
			   c = COLOUR_SCALE(terrain_elev);
			  	GET_TERRAIN_COLOUR(terrain_col, c, aspect);
			   draw_2d_filled_triangle (dx0,dz1,dx1,dz1,mid_x,mid_z,terrain_col);
			}                             
			else
			{                            
			   terrain_elev = (this_row_ptr[0]+this_row_ptr[1]+next_row_ptr[0]+next_row_ptr[1])/4.0;
		   	c = COLOUR_SCALE(terrain_elev);
		   	GET_TERRAIN_COLOUR(terrain_col, c, aspect);
			   draw_2d_filled_triangle (dx0,dz0,dx1,dz1,dx1,dz0,terrain_col);
			   draw_2d_filled_triangle (dx0,dz0,dx0,dz1,dx1,dz1,terrain_col);
  
			}
				//                   
				// next column       
				//                   
                                 
				dx0 += dx_grid;      
				dx1 += dx_grid;      
                                 
				this_row_ptr += step;
				next_row_ptr += step;
                                 
				//                   
				// save old aspect for averaging
				//                   
				if (doaspect)        
	  			{                    
	            old_aspect_x = oa;//aspect;            
					aspectrow[aspect_index] = oa;//aspect;
				}	                  
			}                       
                                 
			if (doaspect)           
	  		{                       
				for (aspect_index = 0; aspect_index < nr_aspect_steps; aspect_index++)
					old_aspectrow[aspect_index] = aspectrow[aspect_index];
			}                       
			// copy all the old stuff	
                                 
			//                      
			// next row             
			//                      
                                 
			dz0 += dz_grid;         
			dz1 += dz_grid;         
                                 
			this_row_start_ptr += row_add_on;
			next_row_start_ptr += row_add_on;
		}                          
                                 
		//VJ 030511 free rows      
		if (doaspect)              
	  	{                          
			free(aspectrow);        
			aspectrow = NULL;       
			free(old_aspectrow);    
			old_aspectrow = NULL;   
		}                          
	}                             
	
	set_2d_window_rotation (mfd_env, 0.0);
}                                
                                 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                 
void draw_tsd_contour_map (env_2d *mfd_env, float y_translate, float range, float scale, vec3d *position, float heading, int draw_large_mfd, int force_contours)
{                                
	int                           
		x_index,                   
		z_index,                   
		row_add_on,                
		x_min_index,               
		z_min_index,               
		x_max_index,               
		z_max_index,               
		path_detail_level,         
		contour_granularity,       
		contour_granularity_mask;  
                                 
	float                         
		x_min,                     
		z_min,                     
		x_mid,                     
		z_mid,                     
		x_max,                     
		z_max,                     
		radius,                    
		distance,                  
		dx0,                       
		dz0,                       
		dx1,                       
		dz1,                       
		dx_grid,                   
		dz_grid,                   
		dx_start,                  
		dz_start,                  
		*this_row_ptr,             
		*next_row_ptr,             
		*this_row_start_ptr,       
		*next_row_start_ptr;       
                                 
	vec3d                         
		p1,                        
		p2,                        
		p3;                        
                                 
	ASSERT (position);            
                                 
	#if OPTIMISE_CONTOURS         
                                 
	num_contour_loops = 0;        
                                 
	num_contour_lines = 0;        
                                 
	#endif                        

	//                            
	// rotate map                 
	//                            
                                 
	set_2d_window_rotation (mfd_env, heading);
                                 
	//                            
	// get map centre position    
	//                            
                                 
	distance = y_translate / scale;
                                 
	x_mid = position->x + (distance * sin (heading));
	z_mid = position->z + (distance * cos (heading));
                                 
	//                            
	// get map area (increased by one grid, where hypotenuse is approx (x + z))
	//                            
                                 
	radius = range + terrain_3d_simple_elevation_x_grid_size + terrain_3d_simple_elevation_z_grid_size;
                                 
	x_min = x_mid - radius;       
	z_min = z_mid - radius;       
                                 
	x_max = x_mid + radius;       
	z_max = z_mid + radius;       
                                 
	//                            
	// clip map area              
	//                            
                                 
	x_min = max (x_min, MIN_MAP_X);
	z_min = max (z_min, MIN_MAP_Z);
                                 
	x_max = min (x_max, MAX_MAP_X);
	z_max = min (z_max, MAX_MAP_Z);
                                 
	////////////////////////////////////////
	//                            
	// DRAW CONTOURS              
	//                            
	////////////////////////////////////////
                                 
	//                            
	// get simple terrain map indices
	//                            
                                 
	convert_float_to_int ((x_min * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_min_index);
	convert_float_to_int ((z_min * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_min_index);
                                 
	convert_float_to_int ((x_max * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_max_index);
	convert_float_to_int ((z_max * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_max_index);
                                 
	////////////////////////////////////////
	//                            
	// contour_granularity: chunks the terrain grid
	// contour_samples    : culls the number of contour line samples
	// contour_spacing    : height between contour lines (meters)
	// path_detail_level  : 0 = highest detail (ie draw all sub-lines)
	//                            
	////////////////////////////////////////
                                 
	////////////////////////////////////////
	if (range == TSD_ASE_RANGE_2000)
	////////////////////////////////////////
	{                             
		contour_granularity = 1;   
                                 
		contour_samples = 5;       
                                 
		contour_spacing = 100;     
                                 
		if (draw_large_mfd)        
		{                          
			path_detail_level = 0;  
		}                          
		else                       
		{                          
			path_detail_level = 2;  
		}                          
	}                             
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_5000)
	////////////////////////////////////////
	{                             
		if (draw_large_mfd)        
		{                          
			contour_granularity = 1;
                                 
			contour_samples = 10;   
                                 
			path_detail_level = 0;  
		}                          
		else                       
		{                          
			contour_granularity = 2;
                                 
			contour_samples = 10;   
                                 
			path_detail_level = 2;  
		}                          
                                 
		contour_spacing = 100;     
	}                             
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_10000)
	////////////////////////////////////////
	{                             
		if (draw_large_mfd)        
		{                          
			contour_granularity = 2;
                                 
			contour_samples = 10;   
                                 
			path_detail_level = 1;  
		}                          
		else                       
		{                          
			contour_granularity = 4;
                                 
			contour_samples = 20;   
                                 
			path_detail_level = 3;  
		}                          
                                 
		contour_spacing = 100;     
	}                             
                                 
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_25000)
	////////////////////////////////////////
	{                             
		if (draw_large_mfd)        
		{                          
			contour_granularity = 4;
                                 
			contour_samples = 10;   
                                 
			path_detail_level = 2;  
		}                          
		else                       
		{                          
			contour_granularity = 8;
                                 
			contour_samples = 15;   
                                 
			path_detail_level = 4;  
		}                          
                                 
		contour_spacing = 250;
		contour_spacing = 100;     
	}                             
	else if (range == HIND_MOVING_MAP_RANGE_50000)
	{
		contour_granularity = 1;
		                                 
		contour_samples = 5;
		                                 
		path_detail_level = 0;
		
		contour_spacing = 75;
	}
	////////////////////////////////////////
	else                          
	///////////////////////////////////////
	{                             
		debug_fatal ("Unknown TSD/ASE range %.2f", range);
	}
	//VJ 030423 TSD render mod    
	if (force_contours || (tsd_render_mode != TSD_RENDER_RELIEF_MODE && tsd_render_mode != TSD_RENDER_SHADED_RELIEF_MODE))
	{                             
                                 
		contour_spacing /= contour_samples;
                                 
		contour_granularity_mask = ~(contour_granularity - 1);
                                 
		//                         
		// scan map                
		//                         
                                 
		x_min_index &= contour_granularity_mask;
		z_min_index &= contour_granularity_mask;
                                 
		x_max_index += contour_granularity - 1;
		z_max_index += contour_granularity - 1;
                                 
		x_max_index &= contour_granularity_mask;
		z_max_index &= contour_granularity_mask;
                                 
		if (x_max_index >= terrain_3d_simple_elevation_width)
		{                          
			x_max_index = terrain_3d_simple_elevation_width & contour_granularity_mask;
		}                          
                                 
		if (z_max_index >= terrain_3d_simple_elevation_height)
		{                          
			z_max_index = terrain_3d_simple_elevation_height & contour_granularity_mask;
		}                          
                                 
		if ((x_min_index < x_max_index) && (z_min_index < z_max_index))
		{                          
			this_row_start_ptr = &terrain_3d_simple_elevation_grid[(z_min_index * terrain_3d_simple_elevation_width) + x_min_index];
                                 
			row_add_on = terrain_3d_simple_elevation_width * contour_granularity;
                                 
			next_row_start_ptr = this_row_start_ptr + row_add_on;
                                 
			dx_start = ((((float) x_min_index) * terrain_3d_simple_elevation_x_grid_size) - x_mid) * scale;
			dz_start = ((((float) z_min_index) * terrain_3d_simple_elevation_z_grid_size) - z_mid) * scale;
                                 
			dx_grid = terrain_3d_simple_elevation_x_grid_size * (float) contour_granularity * scale;
			dz_grid = terrain_3d_simple_elevation_z_grid_size * (float) contour_granularity * scale;
                                 
			dz0 = dz_start;         
			dz1 = dz_start + dz_grid;
                                 
			for (z_index = z_min_index; z_index < z_max_index; z_index += contour_granularity)
			{                       
				dx0 = dx_start;      
				dx1 = dx_start + dx_grid;
                                 
				this_row_ptr = this_row_start_ptr;
				next_row_ptr = next_row_start_ptr;
                                 
				for (x_index = x_min_index; x_index < x_max_index; x_index += contour_granularity)
				{                    
					//                
					// offset [z=0][x=0]
					//                
                                 
					p1.x = dx0;       
					p1.y = this_row_ptr[0];
					p1.z = dz0;       
                                 
					//                
					// offset [z=0][x=1]
					//                
                                 
					p2.x = dx1;       
					p2.y = this_row_ptr[contour_granularity];
					p2.z = dz0;       
                                 
					//                
					// offset [z=1][x=0]
					//                
                                 
					p3.x = dx0;       
					p3.y = next_row_ptr[0];
					p3.z = dz1;       
                                 
                                 
					draw_contour_lines (&p1, &p2, &p3);
                                 
					//                
					// offset [z=1][x=1]
					//                
                                 
					p1.x = dx1;       
					p1.y = next_row_ptr[contour_granularity];
					p1.z = dz1;       
                                 
                                 
					draw_contour_lines (&p1, &p2, &p3);
                                 
					//                
					// next column    
					//                
                                 
					dx0 += dx_grid;   
					dx1 += dx_grid;   
                                 
					this_row_ptr += contour_granularity;
					next_row_ptr += contour_granularity;
				}                    
                                 
				//                   
				// next row          
				//                   
                                 
				dz0 += dz_grid;      
				dz1 += dz_grid;      
                                 
				this_row_start_ptr += row_add_on;
				next_row_start_ptr += row_add_on;
			}                       
		}                          
                                 
		#if OPTIMISE_CONTOURS      
                                 
		debug_filtered_log ("num_contour_loops = %d, num_contour_lines = %d", num_contour_loops, num_contour_lines);
                                 
		#endif                     
                                 
	}//tsd_render_mode != TSD_RENDER_RELIEF_MODE
                                 
   path_detail_level = max(0, path_detail_level-1);
   //VJ 030423 TSD render mod, increase path detail level
                                 
	////////////////////////////////////////
	//                            
	// DRAW RIVERS                
	//                            
	////////////////////////////////////////
                                 
	draw_path_lines               
	(                             
		contour_map_number_of_river_paths,
		contour_map_river_paths,   
		contour_map_river_nodes,   
		map_river_colour,          
		path_detail_level,         
		x_min,                     
		z_min,                     
		x_mid,                     
		z_mid,                     
		x_max,                     
		z_max,                     
		scale,                     
		draw_large_mfd,  //VJ 020426 draw roads thick when draw_large_mfd on
		draw_large_mfd             
	);                            
                                 
	////////////////////////////////////////
	//                            
	// DRAW ROADS                 
	//                            
	////////////////////////////////////////
                                 
	draw_path_lines               
	(                             
		contour_map_number_of_road_paths,
		contour_map_road_paths,    
		contour_map_road_nodes,    
		map_road_colour,           
		path_detail_level,         
		x_min,                     
		z_min,                     
		x_mid,                     
		z_mid,                     
		x_max,                     
		z_max,                     
		scale,                     
		//FALSE,                   
		TRUE, //VJ 030423 TSD render mod, roads were not very visible
		draw_large_mfd             
	);                            
                                 
	//                            
	// reset window rotation      
	//                            
                                 
	set_2d_window_rotation (mfd_env, 0.0);
                                 
}                                
                                 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_tsd_map_contour_colour(rgb_colour col)
{
	map_contour_colour = col;
}

void set_tsd_map_river_colour(rgb_colour col)
{
	map_river_colour = col;
}

void set_tsd_map_road_colour(rgb_colour col)
{
	map_road_colour = col;
}


void draw_tsd_map_grid (vec3d* centre_position, float scale, rgb_colour colour)
{
	float
		x1, x2, y1, y2,
		range = 1.0 / scale,
		wxmin,
		wzmin,
		wxmax = 0,
		wzmax = 0,
		width,
		one_over_sector_side_length;

	int
		grid_spacing = 0,
		inew_wxmin,
		inew_wzmin,
		inew_wxmax,
		inew_wzmax,
		grid_loop,
		grid_loopy;

	one_over_sector_side_length = 1.0 / SECTOR_SIDE_LENGTH;

	// 1.5 is a little more than sqrt(2), so that it is long enough even when rotated 45 degrees
	wxmin = max((centre_position->x - range * 1.5f), MIN_MAP_X);
	wxmax = min((centre_position->x + range * 1.5f), MAX_MAP_X);

	wzmin = max((centre_position->z - range * 1.5f), MIN_MAP_Z);
	wzmax = min((centre_position->z + range * 1.5f), MAX_MAP_Z);

	inew_wxmin = (((int) (wxmin * one_over_sector_side_length)) - 1.0) * SECTOR_SIDE_LENGTH;
	inew_wxmax = (((int) (wxmax * one_over_sector_side_length)) + 1.0) * SECTOR_SIDE_LENGTH;

	// Z max and min around wrong way !
	inew_wzmin = (((int) (wzmin * one_over_sector_side_length)) - 1.0) * SECTOR_SIDE_LENGTH;
	inew_wzmax = (((int) (wzmax * one_over_sector_side_length)) + 1.0) * SECTOR_SIDE_LENGTH;

	inew_wxmin = bound (inew_wxmin, 0, MAX_MAP_X);
	inew_wxmax = bound (inew_wxmax, 0, MAX_MAP_X);
	inew_wzmin = bound (inew_wzmin, 0, MAX_MAP_Z);
	inew_wzmax = bound (inew_wzmax, 0, MAX_MAP_Z);

	width = fabs (wxmax - wxmin);

	grid_spacing = 4096;  // the normal grid spacing is 4096 meters
	
	// along the X
	y1 = (wzmin - centre_position->z) * scale;
	y2 = (wzmax - centre_position->z) * scale;
	
	for (grid_loop = inew_wxmin; grid_loop <= inew_wxmax; grid_loop += grid_spacing)
	{
		if ((grid_loop >= wxmin) && (grid_loop <= wxmax))
		{
			x1 = (grid_loop - centre_position->x) * scale;
			draw_2d_line(x1, y1, x1, y2, colour);
		}
	}

	// down the Z
	x1 = (wxmin - centre_position->x) * scale;
	x2 = (wxmax - centre_position->x) * scale;

	for (grid_loop = inew_wzmin; grid_loop <= inew_wzmax; grid_loop += grid_spacing)
	{
		if ((grid_loop >= wzmin) && (grid_loop <= wzmax))
		{
			y1 = (grid_loop - centre_position->z) * scale;
			draw_2d_line(x1, y1, x2, y1, colour);
		}
	}

	set_mono_font_colour (colour);
	set_mono_font_type (MONO_FONT_TYPE_6X10);

	// map sector labels
	for (grid_loop = inew_wxmin; grid_loop <= inew_wxmax; grid_loop += grid_spacing)
		for (grid_loopy = inew_wzmin; grid_loopy <= inew_wzmax; grid_loopy += grid_spacing)
		{
			int 
				grid_no_x = grid_loop / grid_spacing,
				grid_no_y = grid_loopy / grid_spacing;
			char grid[16];

			x1 = (grid_loop - centre_position->x) * scale;
			x2 = (grid_loop - centre_position->x + 0.5 * grid_spacing) * scale;
			y1 = (grid_loopy - centre_position->z) * scale;
			y2 = (grid_loopy - centre_position->z + 0.5 * grid_spacing) * scale;

			if ((grid_no_y & 3) == 0)  // modula 4, every fourth row has labels
			{
				sprintf(grid, "%02d", grid_loop / grid_spacing);
				set_2d_mono_font_position(x2, y1);
				set_mono_font_rel_position (-6.0, -8.0);
				print_mono_font_string(grid);
			}

			if ((grid_no_x & 3) == 0)  // mod 4
			{
				sprintf(grid, "%02d", grid_loopy / grid_spacing);
				set_2d_mono_font_position(x1, y2);
				set_mono_font_rel_position (2.0, -5.0);
				print_mono_font_string(grid);
			}
		}
}

void draw_tsd_map_towns(vec3d* centre_position, float scale)
{
	vec3d
		pos;

	population_name_database_type
		*item;

	item = population_name_database;
	
	while (item)
	{
//		if (item->type == POPULATION_TYPE_TOWN)
		{
			float x, y;

			pos.x = item->x;
			pos.y = 0.0;
			pos.z = item->z;
			
			get_map_coords_from_world(centre_position, scale, &pos, &x, &y);
			
			set_2d_mono_font_position(x, y);
			print_mono_font_string(item->name);
		}

		item = item->next;
	}
}


void cycle_tsd_map_palette()
{
	tsd_render_palette++;
	if (tsd_render_palette == ARRAY_LENGTH(terrain_colour))
	   tsd_render_palette = 0;
	command_line_tsd_palette = tsd_render_palette;
}
