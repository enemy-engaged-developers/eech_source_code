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

typedef enum SMOKE_DRAW_TYPES
{
	SMOKE_DRAW_TYPE_SPRITES,
	SMOKE_DRAW_TYPE_TRAILS
	
} smoke_draw_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SMOKE_LIST_DATA
{
	// START COLOUR
	unsigned char
		red_start,
		green_start,
		blue_start,
		alpha_start;
	float
		radius_start;

	// Colour change #1
	float
		colour_change_1;
	unsigned char
		red_1,
		green_1,
		blue_1,
		alpha_1;
	float
		radius_1;
		
	// Colour change #2
	float
		colour_change_2;
	unsigned char
		red_2,
		green_2,
		blue_2,
		alpha_2;
	float
		radius_2;
		
	// END COLOUR
	unsigned char
		red_end,
		green_end,
		blue_end,
		alpha_end;
	float
		radius_end;

	// maximum upwards velocity ( metres per second )
	float
		final_vertical_velocity,
		vertical_acceleration,
		initial_velocity_noise;

	texture_animation_indices
		texture;

	float
		texture_size;

	float
		animation_rate,
		wind_affected;

	unsigned short int
		additive			:	1,
		draw_type		:	1,
		flat				:	1,
		ground_based	:	1,
		lock_to_parent	:	1;
};

typedef struct SMOKE_LIST_DATA smoke_list_data;


#define smoke_list_vertical_acceleration(a) smoke_list_database[(a)].vertical_acceleration

#define smoke_list_final_vertical_velocity(a) smoke_list_database[(a)].final_vertical_velocity

#define smoke_list_draw_mode(a) smoke_list_database[(a)].draw_type

#define smoke_list_ground_based(a) smoke_list_database[(a)].ground_based

#define smoke_list_initial_velocity_noise(a) smoke_list_database[(a)].initial_velocity_noise

#define smoke_list_animation_rate(a) smoke_list_database[(a)].animation_rate

#define smoke_list_texture(a) smoke_list_database[(a)].texture

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern char** smoke_list_types_names;

int get_smoke_type_by_name ( const char *name );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern smoke_list_data
	*smoke_list_database;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_smoke_list_database (void);

extern void deinitialise_smoke_list_database (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
