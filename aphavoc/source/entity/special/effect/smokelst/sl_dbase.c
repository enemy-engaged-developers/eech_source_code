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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

smoke_list_data
	*smoke_list_database;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_smoke_list_database (void)
{
	smoke_list_data
		*item;

	smoke_list_database = safe_malloc (sizeof (smoke_list_data) * NUM_SMOKE_LIST_TYPES);

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_GREY_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_GREY_TRAIL]);

		// START COLOUR
		item->red_start			=	220;		// red
		item->green_start			=	220;		// green
		item->blue_start 			=	220;		// blue
		item->alpha_start 		=	255;		// alpha
		item->radius_start		=	0.1;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	200;		// red
		item->green_1 				=	200;		// green
		item->blue_1 				=	200;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	5.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	0;			// red
		item->green_2				=	0;			// green
		item->blue_2				=	0;			// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	5.0;		// radius

		// END COLOUR
		item->red_end				=	100;		// red
		item->green_end			=	100;		// green
		item->blue_end				=	100;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	5.0;		// radius

		item->final_vertical_velocity	=	-1.0;
		item->vertical_acceleration	=	1.0;

		item->initial_velocity_noise	=	0.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE_TRAIL;
		item->texture_size				=	16.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_WHITE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_WHITE_TRAIL]);

		// START COLOUR
		item->red_start			=	255;		// red
		item->green_start			=	255;		// green
		item->blue_start 			=	255;		// blue
		item->alpha_start 		=	255;		// alpha
		item->radius_start		=	0.1;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	255;		// red
		item->green_1 				=	255;		// green
		item->blue_1 				=	255;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	5.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	100;		// red
		item->green_2				=	100;		// green
		item->blue_2				=	100;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	5.0;		// radius

		// END COLOUR
		item->red_end				=	100;		// red
		item->green_end			=	100;		// green
		item->blue_end				=	100;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	5.0;		// radius

		item->final_vertical_velocity	=	-1.0;
		item->vertical_acceleration	=	1.0;

		item->initial_velocity_noise	=	0.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE_TRAIL;
		item->texture_size				=	16.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}
	
	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_ADDITIVE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_ADDITIVE_TRAIL]);

		// START COLOUR
		item->red_start			=	100;		// red
		item->green_start			=	50;		// green
		item->blue_start 			=	0;			// blue
		item->alpha_start 		=	0;			// alpha
		item->radius_start		=	0.1;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.1;		// colour change 1 lifescale
		item->red_1					=	100;		// red
		item->green_1 				=	50;		// green
		item->blue_1 				=	0;			// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	2.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.3;		// colour change 2 lifescale
		item->red_2					=	100;		// red
		item->green_2				=	50;		// green
		item->blue_2				=	0;			// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	1.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	0.0;		// radius

		item->final_vertical_velocity	=	-1.0;
		item->vertical_acceleration	=	1.0;

		item->initial_velocity_noise	=	0.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_ADDITIVE_SMOKE_TRAIL;
		item->texture_size				=	16.0;
		item->animation_rate				=	1.0;

		item->additive						=	TRUE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_LARGE_ADDITIVE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_LARGE_ADDITIVE_TRAIL]);

		// START COLOUR
		item->red_start			=	200;		// red
		item->green_start			=	100;		// green
		item->blue_start 			=	30;		// blue
		item->alpha_start 		=	0;			// alpha
		item->radius_start		=	0.1;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.12;		// colour change 1 lifescale
		item->red_1					=	200;		// red
		item->green_1 				=	100;		// green
		item->blue_1 				=	30;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	1.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.2;		// colour change 2 lifescale
		item->red_2					=	200;		// red
		item->green_2				=	100;		// green
		item->blue_2				=	30;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	3.5;		// radius

		// END COLOUR
		item->red_end				=	200;		// red
		item->green_end			=	100;		// green
		item->blue_end				=	60;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	5.0;		// radius

		item->final_vertical_velocity	=	2.5;
		item->vertical_acceleration	=	0.8;

		item->initial_velocity_noise	=	2.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_ADDITIVE_SMOKE_TRAIL;
		item->texture_size				=	16.0;
		item->animation_rate				=	1.0;

		item->additive						=	TRUE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_FIRE
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_FIRE]);

		// START COLOUR
		item->red_start			=	30;		// red
		item->green_start			=	30;		// green
		item->blue_start 			=	30;		// blue
		item->alpha_start 		=	180;		// alpha
		item->radius_start		=	3.5;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.1;		// colour change 1 lifescale
		item->red_1					=	30;		// red
		item->green_1 				=	30;		// green
		item->blue_1 				=	30;		// blue
		item->alpha_1 				=	100;		// alpha
		item->radius_1 			=	8.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.2;		// colour change 2 lifescale
		item->red_2					=	30;		// red
		item->green_2				=	30;		// green
		item->blue_2				=	30;		// blue
		item->alpha_2				=	100;		// alpha
		item->radius_2				=	21.5;		// radius

		// END COLOUR
		item->red_end				=	60;		// red
		item->green_end			=	60;		// green
		item->blue_end				=	60;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	60.0;		// radius

		item->final_vertical_velocity	=	2.5;
		item->vertical_acceleration	=	0.8;

		item->initial_velocity_noise	=	3.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	0.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_SMALL_FIRE
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_SMALL_FIRE]);

		// START COLOUR
		item->red_start			=	30;		// red
		item->green_start			=	30;		// green
		item->blue_start 			=	30;		// blue
		item->alpha_start 		=	180;		// alpha
		item->radius_start		=	0.33;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.1;		// colour change 1 lifescale
		item->red_1					=	30;		// red
		item->green_1 				=	30;		// green
		item->blue_1 				=	30;		// blue
		item->alpha_1 				=	100;		// alpha
		item->radius_1 			=	0.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.2;		// colour change 2 lifescale
		item->red_2					=	30;		// red
		item->green_2				=	30;		// green
		item->blue_2				=	30;		// blue
		item->alpha_2				=	100;		// alpha
		item->radius_2				=	1.5;		// radius

		// END COLOUR
		item->red_end				=	60;		// red
		item->green_end			=	60;		// green
		item->blue_end				=	60;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	3.0;		// radius

		item->final_vertical_velocity	=	0.5;
		item->vertical_acceleration	=	0.25;

		item->initial_velocity_noise	=	0.15;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	0.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	FALSE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_PURPLE_FLARE
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_PURPLE_FLARE]);

		// START COLOUR
		item->red_start			=	255;		// red
		item->green_start			=	160;		// green
		item->blue_start 			=	200;		// blue
		item->alpha_start 		=	255;		// alpha
		item->radius_start		=	5.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.2;		// colour change 1 lifescale
		item->red_1					=	255;		// red
		item->green_1 				=	50;		// green
		item->blue_1 				=	255;		// blue
		item->alpha_1 				=	200;		// alpha
		item->radius_1 			=	13.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.5;		// colour change 2 lifescale
		item->red_2					=	255;		// red
		item->green_2				=	10;		// green
		item->blue_2				=	255;		// blue
		item->alpha_2				=	40;		// alpha
		item->radius_2				=	24.0;		// radius

		// END COLOUR
		item->red_end				=	200;		// red
		item->green_end			=	0;			// green
		item->blue_end				=	200;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	24.0;		// radius

		item->final_vertical_velocity	=	-1.0;
		item->vertical_acceleration	=	0.2;

		item->initial_velocity_noise	=	2.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	0.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	FALSE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_LARGE_DUST_CLOUD
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_LARGE_DUST_CLOUD]);

		// START COLOUR
		item->red_start			=	100;		// red
		item->green_start			=	100;		// green
		item->blue_start 			=	100;		// blue
		item->alpha_start 		=	200;		// alpha
		item->radius_start		=	15.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.2;		// colour change 1 lifescale
		item->red_1					=	160;		// red
		item->green_1 				=	160;		// green
		item->blue_1 				=	160;		// blue
		item->alpha_1 				=	200;		// alpha
		item->radius_1 			=	20.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	120;		// red
		item->green_2				=	120;		// green
		item->blue_2				=	120;		// blue
		item->alpha_2				=	20;		// alpha
		item->radius_2				=	35.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	1.0;		// radius

		item->final_vertical_velocity	=	-1.0;
		item->vertical_acceleration	=	0.2;

		item->initial_velocity_noise	=	5.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	0.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	FALSE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_SMALL_PARTICLE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_SMALL_PARTICLE_TRAIL]);

		// START COLOUR
		item->red_start			=	120;		// red
		item->green_start			=	120;		// green
		item->blue_start 			=	0;			// blue
		item->alpha_start 		=	180;		// alpha
		item->radius_start		=	1.75;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.1;		// colour change 1 lifescale
		item->red_1					=	120;		// red
		item->green_1 				=	0;			// green
		item->blue_1 				=	0;			// blue
		item->alpha_1 				=	100;		// alpha
		item->radius_1 			=	4.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.2;		// colour change 2 lifescale
		item->red_2					=	0;			// red
		item->green_2				=	0;			// green
		item->blue_2				=	0;			// blue
		item->alpha_2				=	100;		// alpha
		item->radius_2				=	5.5;		// radius

		// END COLOUR
		item->red_end				=	40;		// red
		item->green_end			=	40;		// green
		item->blue_end				=	40;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	15.0;		// radius

		item->final_vertical_velocity	=	-1.0;
		item->vertical_acceleration	=	0.5;

		item->initial_velocity_noise	=	1.3;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_MEDIUM_EARTH_PARTICLE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_MEDIUM_EARTH_PARTICLE_TRAIL]);

		// START COLOUR
		item->red_start			=	80;		// red
		item->green_start			=	60;		// green
		item->blue_start 			=	20;		// blue
		item->alpha_start 		=	180;		// alpha
		item->radius_start		=	2.4;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	80;		// red
		item->green_1 				=	60;		// green
		item->blue_1 				=	20;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	15.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	0;			// red
		item->green_2				=	0;			// green
		item->blue_2				=	0;			// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	15.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	15.0;		// radius

		item->final_vertical_velocity	=	-1.0;
		item->vertical_acceleration	=	0.5;

		item->initial_velocity_noise	=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}
	
	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_MEDIUM_WATER_PARTICLE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_MEDIUM_WATER_PARTICLE_TRAIL]);

		// START COLOUR
		item->red_start			=	255;		// red
		item->green_start			=	255;		// green
		item->blue_start 			=	255;		// blue
		item->alpha_start 		=	100;		// alpha
		item->radius_start		=	2.4;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.1;		// colour change 1 lifescale
		item->red_1					=	255;		// red
		item->green_1 				=	255;		// green
		item->blue_1 				=	255;		// blue
		item->alpha_1 				=	60;		// alpha
		item->radius_1 			=	4.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	230;		// red
		item->green_2				=	230;		// green
		item->blue_2				=	230;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	15.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	15.0;		// radius

		item->final_vertical_velocity	=	-1.0;
		item->vertical_acceleration	=	0.5;

		item->initial_velocity_noise	=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DUST_TRAIL_1
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DUST_TRAIL_1]);

		// START COLOUR
		item->red_start			=	120;		// red
		item->green_start			=	110;		// green
		item->blue_start 			=	90;		// blue
		item->alpha_start 		=	64;		// alpha
		item->radius_start		=	1.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.7;		// colour change 1 lifescale
		item->red_1					=	150;		// red
		item->green_1 				=	140;		// green
		item->blue_1 				=	120;		// blue
		item->alpha_1 				=	32;		// alpha
		item->radius_1 			=	5.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	150;		// red
		item->green_2				=	140;		// green
		item->blue_2				=	120;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	10.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	10.0;		// radius

		item->final_vertical_velocity	=	2.0;
		item->vertical_acceleration	=	1.0;

		item->initial_velocity_noise	=	1.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	0.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}
	
	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DUST_TRAIL_2
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DUST_TRAIL_2]);

		// START COLOUR
		item->red_start			=	80;		// red
		item->green_start			=	80;		// green
		item->blue_start 			=	80;		// blue
		item->alpha_start 		=	255;		// alpha
		item->radius_start		=	5.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	180;		// red
		item->green_1 				=	180;		// green
		item->blue_1 				=	180;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	50.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	0;			// red
		item->green_2				=	0;			// green
		item->blue_2				=	0;			// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	50.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	50.0;		// radius

		item->final_vertical_velocity	=	1.0;
		item->vertical_acceleration	=	0.5;

		item->initial_velocity_noise	=	2.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	0.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}
	
	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_REAR_SHIP_WAKE
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_REAR_SHIP_WAKE]);

		// START COLOUR
		item->red_start			=	255;		// red
		item->green_start			=	255;		// green
		item->blue_start 			=	255;		// blue
		item->alpha_start 		=	255;		// alpha
		item->radius_start		=	0.02;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	180;		// red
		item->green_1 				=	210;		// green
		item->blue_1 				=	255;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	50.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	180;		// red
		item->green_2				=	210;		// green
		item->blue_2				=	255;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	1.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	1.0;		// radius

		item->final_vertical_velocity	=	0.0;
		item->vertical_acceleration	=	0.0;

		item->initial_velocity_noise	=	0.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SHIP_WAKE;
		item->texture_size				=	64.0;
		item->animation_rate				=	0.25;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	TRUE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	FALSE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_FRONT_SHIP_WAKE
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_FRONT_SHIP_WAKE]);

		// START COLOUR
		item->red_start			=	255;		// red
		item->green_start			=	255;		// green
		item->blue_start 			=	255;		// blue
		item->alpha_start 		=	255;		// alpha
		item->radius_start		=	5.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	180;		// red
		item->green_1 				=	210;		// green
		item->blue_1 				=	255;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	120.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	0;			// red
		item->green_2				=	0;			// green
		item->blue_2				=	0;			// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	0.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	0.0;		// radius

		item->final_vertical_velocity	=	0.0;
		item->vertical_acceleration	=	0.0;

		item->initial_velocity_noise	=	0.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SHIP_WAKE;
		item->texture_size				=	128.0;
		item->animation_rate				=	0.25;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	TRUE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	FALSE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_AIRCRAFT_LIGHT_DAMAGE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_AIRCRAFT_LIGHT_DAMAGE_TRAIL]);

		// START COLOUR
		item->red_start			=	130;		// red
		item->green_start			=	130;		// green
		item->blue_start 			=	130;		// blue
		item->alpha_start 		=	100;		// alpha
		item->radius_start		=	0.25;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.12;		// colour change 1 lifescale
		item->red_1					=	130;		// red
		item->green_1 				=	130;		// green
		item->blue_1 				=	130;		// blue
		item->alpha_1 				=	100;		// alpha
		item->radius_1 			=	1.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.2;		// colour change 2 lifescale
		item->red_2					=	120;		// red
		item->green_2				=	120;		// green
		item->blue_2				=	120;		// blue
		item->alpha_2				=	80;		// alpha
		item->radius_2				=	3.5;		// radius

		// END COLOUR
		item->red_end				=	80;		// red
		item->green_end			=	80;		// green
		item->blue_end				=	80;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	5.0;		// radius

		item->final_vertical_velocity	=	2.5;
		item->vertical_acceleration	=	0.8;

		item->initial_velocity_noise	=	1.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE_TRAIL;
		item->texture_size				=	16.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_AIRCRAFT_MEDIUM_DAMAGE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_AIRCRAFT_MEDIUM_DAMAGE_TRAIL]);

		// START COLOUR
		item->red_start			=	40;		// red
		item->green_start			=	40;		// green
		item->blue_start 			=	40;		// blue
		item->alpha_start 		=	160;		// alpha
		item->radius_start		=	0.2;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.5;		// colour change 1 lifescale
		item->red_1					=	40;		// red
		item->green_1 				=	40;		// green
		item->blue_1 				=	40;		// blue
		item->alpha_1 				=	90;		// alpha
		item->radius_1 			=	6.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	80;		// red
		item->green_2				=	80;		// green
		item->blue_2				=	80;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	20.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	1.0;		// radius

		item->final_vertical_velocity	=	2.5;
		item->vertical_acceleration	=	0.8;

		item->initial_velocity_noise	=	1.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE_TRAIL;
		item->texture_size				=	16.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE_TRAIL]);

		// START COLOUR
		item->red_start			=	30;		// red
		item->green_start			=	30;		// green
		item->blue_start 			=	30;		// blue
		item->alpha_start 		=	180;		// alpha
		item->radius_start		=	0.2;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.5;		// colour change 1 lifescale
		item->red_1					=	30;		// red
		item->green_1 				=	30;		// green
		item->blue_1 				=	30;		// blue
		item->alpha_1 				=	110;		// alpha
		item->radius_1 			=	6.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	50;		// red
		item->green_2				=	50;		// green
		item->blue_2				=	50;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	20.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	1.0;		// radius

		item->final_vertical_velocity	=	2.5;
		item->vertical_acceleration	=	0.8;

		item->initial_velocity_noise	=	1.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE_TRAIL;
		item->texture_size				=	16.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_AIRCRAFT_ADDITIVE_DAMAGE_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_AIRCRAFT_ADDITIVE_DAMAGE_TRAIL]);

		// START COLOUR
		item->red_start			=	90;		// red
		item->green_start			=	60;		// green
		item->blue_start 			=	20;		// blue
		item->alpha_start 		=	0;			// alpha
		item->radius_start		=	0.2;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.5;		// colour change 1 lifescale
		item->red_1					=	140;		// red
		item->green_1 				=	90;		// green
		item->blue_1 				=	40;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	3.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	0;			// red
		item->green_2				=	0;			// green
		item->blue_2				=	0;			// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	1.0;		// radius

		// END COLOUR
		item->red_end				=	0;			// red
		item->green_end			=	0;			// green
		item->blue_end				=	0;			// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	1.0;		// radius

		item->final_vertical_velocity	=	2.5;
		item->vertical_acceleration	=	0.8;

		item->initial_velocity_noise	=	1.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_ADDITIVE_SMOKE_TRAIL;
		item->texture_size				=	16.0;
		item->animation_rate				=	1.0;

		item->additive						=	TRUE;
		item->draw_type					=	SMOKE_DRAW_TYPE_TRAILS;
		item->flat							=	FALSE;
		item->ground_based				=	FALSE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_AIRCRAFT_SMALL_TOUCHDOWN_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_AIRCRAFT_SMALL_TOUCHDOWN_TRAIL]);

		// START COLOUR
		item->red_start			=	255;		// red
		item->green_start			=	255;		// green
		item->blue_start 			=	255;		// blue
		item->alpha_start 		=	180;		// alpha
		item->radius_start		=	0.1;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	255;		// red
		item->green_1 				=	255;		// green
		item->blue_1 				=	255;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	4.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	255;		// red
		item->green_2				=	255;		// green
		item->blue_2				=	255;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	4.0;		// radius

		// END COLOUR
		item->red_end				=	255;		// red
		item->green_end			=	255;		// green
		item->blue_end				=	255;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	4.0;		// radius

		item->final_vertical_velocity	=	0.2;
		item->vertical_acceleration	=	0.1;

		item->initial_velocity_noise	=	0.05;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	0.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_AIRCRAFT_LARGE_TOUCHDOWN_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_AIRCRAFT_LARGE_TOUCHDOWN_TRAIL]);

		// START COLOUR
		item->red_start			=	255;		// red
		item->green_start			=	255;		// green
		item->blue_start 			=	255;		// blue
		item->alpha_start 		=	180;		// alpha
		item->radius_start		=	0.25;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	255;		// red
		item->green_1 				=	255;		// green
		item->blue_1 				=	255;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	10.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	255;		// red
		item->green_2				=	255;		// green
		item->blue_2				=	255;		// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2				=	10.0;		// radius

		// END COLOUR
		item->red_end				=	255;		// red
		item->green_end			=	255;		// green
		item->blue_end				=	255;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	10.0;		// radius

		item->final_vertical_velocity	=	0.25;
		item->vertical_acceleration	=	0.1;

		item->initial_velocity_noise	=	0.1;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	0.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}


	// Xhit: The following smoke trails type downwash is for the downwash effect (030328)
	// These are mapped from surface_types

	// Xhit: added SMOKE_LIST_TYPE_DOWNWASH_DESERT for desert campaigns (030515)

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_DESERT
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_DESERT]);

		// START COLOUR
		item->red_start			=	120;	// red
		item->green_start			=	100;	// green
		item->blue_start 			=	40;	// blue
		item->alpha_start 		=	200;	// alpha
		item->radius_start		=	6.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	120;	// red
		item->green_1 				=	100;	// green
		item->blue_1 				=	40;	// blue
		item->alpha_1 				=	140;	// alpha
		item->radius_1 			=	12.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	120;	// red
		item->green_2				=	100;	// green
		item->blue_2				=	40;	// blue
		item->alpha_2				=	100;	// alpha
		item->radius_2				=	17.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise		=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}


	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_SAND
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_SAND]);

		// START COLOUR
		item->red_start			=	120;	// red
		item->green_start			=	100;	// green
		item->blue_start 			=	40;	// blue
		item->alpha_start 		=	120;	// alpha
		item->radius_start		=	4.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	120;	// red
		item->green_1 				=	100;	// green
		item->blue_1 				=	40;	// blue
		item->alpha_1 				=	60;	// alpha
		item->radius_1 			=	8.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	120;	// red
		item->green_2				=	100;	// green
		item->blue_2				=	40;	// blue
		item->alpha_2				=	30;	// alpha
		item->radius_2				=	16.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise		=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_GRASS
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_GRASS]);

		// START COLOUR
		item->red_start			=	40;	// red
		item->green_start			=	80;	// green
		item->blue_start 			=	20;	// blue
		item->alpha_start 		=	16;	// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	40;	// red
		item->green_1 				=	80;	// green
		item->blue_1 				=	20;	// blue
		item->alpha_1 				=	8;		// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	40;	// red
		item->green_2				=	80;	// green
		item->blue_2				=	20;	// blue
		item->alpha_2				=	2;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise		=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_ASPHALT
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_ASPHALT]);

		// START COLOUR
		item->red_start			=	120;	// red
		item->green_start			=	100;	// green
		item->blue_start 			=	80;		// blue
		item->alpha_start 		=	16;		// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	120;	// red
		item->green_1 				=	100;	// green
		item->blue_1 				=	80;		// blue
		item->alpha_1 				=	8;		// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	120;	// red
		item->green_2				=	100;	// green
		item->blue_2				=	80;		// blue
		item->alpha_2				=	2;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise		=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}


	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_WATER
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_WATER]);

		// START COLOUR
		item->red_start				=	255;		// red
		item->green_start				=	255;		// green
		item->blue_start 				=	255;		// blue
		item->alpha_start 			=	20;		// alpha
		item->radius_start			=	2.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1		=	1.0;		// colour change 1 lifescale
		item->red_1						=	180;		// red
		item->green_1 					=	210;		// green
		item->blue_1 					=	255;		// blue
		item->alpha_1 					=	10;		// alpha
		item->radius_1 				=	4.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2		=	1.0;		// colour change 2 lifescale
		item->red_2						=	180;		// red
		item->green_2					=	210;		// green
		item->blue_2					=	255;		// blue
		item->alpha_2					=	2;			// alpha
		item->radius_2					=	8.0;		// radius

		// END COLOUR
		item->red_end					=	0;			// red
		item->green_end				=	0;			// green
		item->blue_end					=	0;			// blue
		item->alpha_end				=	0;			// alpha
		item->radius_end				=	1.0;		// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	1.0;

		item->initial_velocity_noise		=	0.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	TRUE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_SOIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_SOIL]);

		// START COLOUR
		item->red_start			=	100;	// red
		item->green_start			=	90;		// green
		item->blue_start 			=	60;		// blue
		item->alpha_start 		=	20;		// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	100;	// red
		item->green_1 				=	90;	// green
		item->blue_1 				=	60;	// blue
		item->alpha_1 				=	10;	// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	100;	// red
		item->green_2				=	90;	// green
		item->blue_2				=	60;	// blue
		item->alpha_2				=	5;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise	=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_FIELD_LIGHTBROWN
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_FIELD_LIGHTBROWN]);

		// START COLOUR
		item->red_start			=	150;	// red
		item->green_start			=	130;	// green
		item->blue_start 			=	90;	// blue
		item->alpha_start 		=	20;	// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	150;	// red
		item->green_1 				=	130;	// green
		item->blue_1 				=	90;	// blue
		item->alpha_1 				=	10;	// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	150;	// red
		item->green_2				=	130;	// green
		item->blue_2				=	90;	// blue
		item->alpha_2				=	5;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise		=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_FIELD_DARKBROWN
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_FIELD_DARKBROWN]);

		// START COLOUR
		item->red_start			=	100;	// red
		item->green_start			=	90;	// green
		item->blue_start 			=	60;	// blue
		item->alpha_start 		=	20;	// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	100;	// red
		item->green_1 				=	90;	// green
		item->blue_1 				=	60;	// blue
		item->alpha_1 				=	10;	// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	100;	// red
		item->green_2				=	90;	// green
		item->blue_2				=	60;	// blue
		item->alpha_2				=	5;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise	=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_FIELD_LIGHTGREEN
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_FIELD_LIGHTGREEN]);

		// START COLOUR
		item->red_start			=	80;	// red
		item->green_start			=	170;	// green
		item->blue_start 			=	40;	// blue
		item->alpha_start 		=	20;	// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	80;	// red
		item->green_1 				=	170;	// green
		item->blue_1 				=	40;	// blue
		item->alpha_1 				=	10;	// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	80;	// red
		item->green_2				=	170;	// green
		item->blue_2				=	40;	// blue
		item->alpha_2				=	5;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise	=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_FIELD_DARKGREEN
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_FIELD_DARKGREEN]);

		// START COLOUR
		item->red_start			=	40;	// red
		item->green_start			=	80;	// green
		item->blue_start 			=	20;	// blue
		item->alpha_start 		=	20;	// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	40;	// red
		item->green_1 				=	80;	// green
		item->blue_1 				=	20;	// blue
		item->alpha_1 				=	10;	// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	40;	// red
		item->green_2				=	80;	// green
		item->blue_2				=	20;	// blue
		item->alpha_2				=	5;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise		=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_ROCK
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_ROCK]);

		// START COLOUR
		item->red_start			=	100;	// red
		item->green_start			=	100;	// green
		item->blue_start 			=	100;	// blue
		item->alpha_start 		=	16;	// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	100;	// red
		item->green_1 				=	100;	// green
		item->blue_1 				=	100;	// blue
		item->alpha_1 				=	8;		// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	100;	// red
		item->green_2				=	100;	// green
		item->blue_2				=	100;	// blue
		item->alpha_2				=	2;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise	=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_DOWNWASH_SNOW
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_DOWNWASH_SNOW]);

		// START COLOUR
		item->red_start			=	210;	// red
		item->green_start			=	210;	// green
		item->blue_start 			=	210;	// blue
		item->alpha_start 		=	20;	// alpha
		item->radius_start		=	2.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	210;	// red
		item->green_1 				=	210;	// green
		item->blue_1 				=	210;	// blue
		item->alpha_1 				=	10;	// alpha
		item->radius_1 			=	4.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	210;	// red
		item->green_2				=	210;	// green
		item->blue_2				=	210;	// blue
		item->alpha_2				=	5;		// alpha
		item->radius_2				=	8.0;	// radius

		// END COLOUR
		item->red_end				=	0;		// red
		item->green_end			=	0;		// green
		item->blue_end				=	0;		// blue
		item->alpha_end			=	0;		// alpha
		item->radius_end			=	10.0;	// radius

		item->final_vertical_velocity		=	-1.0;
		item->vertical_acceleration		=	0.5;

		item->initial_velocity_noise		=	1.5;

		item->texture						=	TEXTURE_ANIMATION_INDEX_SMOKE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	FALSE;
		item->draw_type					=	SMOKE_DRAW_TYPE_SPRITES;
		item->flat							=	FALSE;
		item->ground_based				=	TRUE;
		item->lock_to_parent				=	TRUE;
		item->wind_affected				=	TRUE;
	}

	//
	// allocate arrays for smoke list drawing
	//

	initialise_smoke_list_draw_arrays ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_smoke_list_database (void)
{
	safe_free (smoke_list_database);

	//
	// free arrays for smoke list drawing
	//

	deinitialise_smoke_list_draw_arrays ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
