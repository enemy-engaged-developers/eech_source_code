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

struct SMOKE_TRAIL_INFORMATION
{

	struct SCREEN
		*texture;

	float
		initial_texture_distance,
		texture_size;

	int
		number_of_points,
		additive;

	struct SMOKE_TRAIL_DATA
		*points;
};

typedef struct SMOKE_TRAIL_INFORMATION smoke_trail_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SMOKE_TRAIL_DATA
{

	vec3d
		point1,
		point2,
		centre;

	float
		texture_u;

	struct REAL_COLOUR
		colour;
};

typedef struct SMOKE_TRAIL_DATA smoke_trail_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* forward declarations for types used below */
struct OBJECT_3D_SMOKE_TRAIL;
/*********************************************/

extern void reset_smoke_trail_rendering_information ( void );

extern smoke_trail_information *get_smoke_trail_header ( void );

extern smoke_trail_data *get_smoke_trail_point_data ( int number_of_points );

extern void insert_zbiased_smoke_trail_into_3d_scene ( int number_of_points, float zbias, int additive, struct SCREEN *texture, float texture_distance, float texture_size, smoke_trail_data *points );

#define insert_smoke_trail_into_3d_scene(NUMBER_OF_POINTS,ADDITIVE,TEXTURE,TEXTURE_DISTANCE,TEXTURE_SIZE,POINTS) insert_zbiased_smoke_trail_into_3d_scene (NUMBER_OF_POINTS, 0.0, ADDITIVE, TEXTURE, TEXTURE_DISTANCE, TEXTURE_SIZE, POINTS )

extern void draw_3d_smoke_trail ( struct OBJECT_3D_SMOKE_TRAIL *smoke );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

