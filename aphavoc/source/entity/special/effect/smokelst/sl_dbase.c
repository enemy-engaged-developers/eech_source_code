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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

smoke_list_data
	*smoke_list_database;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 01DEC10 Casm Smoke database import/export begin
#define SMOKE_LIST_DECLARATION(x)
#define SMOKE_LIST(x) #x,
#define SMOKE_LIST_(x) NULL
#define META_SMOKE_LIST_DECLARATION(x)
#define META_SMOKE_LIST(x)
#define META_SMOKE_LIST_(x)
static const char* default_smoke_list_types_names[] =
{
#include "sl_types.h"
};
#undef SMOKE_LIST_DECLARATION
#undef SMOKE_LIST
#undef SMOKE_LIST_
#undef META_SMOKE_LIST_DECLARATION
#undef META_SMOKE_LIST
#undef META_SMOKE_LIST_

// 07DEC11 Casm Loading any number of custom smoke list types
static int
	total_number_of_smoke_list_types,
	smoke_list_types_available;

char
	**smoke_list_types_names;

static void initialise_smoke_list_types_names (void)
{
	int
		count,
		size;

	smoke_list_types_names = (char **)safe_malloc ((total_number_of_smoke_list_types + smoke_list_types_available) * sizeof (char *));
	for (count = 0; count < NUM_SMOKE_LIST_TYPES; count++)
	{
		size = strlen(default_smoke_list_types_names[count]) + 1;
		smoke_list_types_names[count] = (char*) safe_malloc (size);
		memcpy (smoke_list_types_names[count], default_smoke_list_types_names[count], size);
	}
	for (; count < total_number_of_smoke_list_types + smoke_list_types_available; count++)
	{
		smoke_list_types_names[count] = NULL;
	}
}

static void deinitialise_smoke_list_types_names (void)
{
	int
		count;

	if (!smoke_list_types_names)
	{
		return;
	}

	for (count = 0; count < total_number_of_smoke_list_types + smoke_list_types_available; count++)
	{
		if (smoke_list_types_names[count])
		{
			safe_free (smoke_list_types_names[count]);
		}
	}

	safe_free (smoke_list_types_names);
	smoke_list_types_names = NULL;
}

int get_smoke_type_by_name ( const char *name )
{
	int
		count;

	for (count = 0; count < total_number_of_smoke_list_types; count++)
	{
		if (!stricmp (name, smoke_list_types_names[count]))
		{
			return count;
		}
	}

	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SMOKE_LIST_DATABASE_FILENAME "SMOKES.CSV"

static void export_smoke_list_database (void)
{
	FILE
		*file;
	int
		count;
	const smoke_list_data
		*smoke;

	file = safe_fopen (SMOKE_LIST_DATABASE_FILENAME, "w");
	fprintf (file, "SMOKE;1\n");
	fprintf (file,
		"#Smoke index;Smoke name;Texture animation;"
		"Start colour (red;green;blue;alpha;radius);"
		"Colour change #1 (change;red;green;blue;alpha;radius);"
		"Colour change #2 (change;red;green;blue;alpha;radius);"
		"End colour (red;green;blue;alpha;radius);"
		"Vertical velocity(final;acceleration;initial noise);"
		"Texture size;Animation rate;"
		"Additive;Draw type;Flat;Ground based;Lock to parent;Wind affected"
		"\n");
	for (count = 0; count < total_number_of_smoke_list_types; count++)
	{
		if (count == SMOKE_LIST_TYPE_DOWNWASH_START)
		{
			continue;
		}

		smoke = &smoke_list_database[count];
		fprintf (file,
			"%i;%s;%s;"
			"%i;%i;%i;%i;%f;"
			"%f;%i;%i;%i;%i;%f;"
			"%f;%i;%i;%i;%i;%f;"
			"%i;%i;%i;%i;%f;"
			"%f;%f;%f;"
			"%f;%f;%i;%i;%i;%i;%i;%i\n",
			count, smoke_list_types_names[count], texture_animation_names[smoke->texture],

			smoke->red_start,
			smoke->green_start,
			smoke->blue_start,
			smoke->alpha_start,
			smoke->radius_start,

			smoke->colour_change_1,
			smoke->red_1,
			smoke->green_1,
			smoke->blue_1,
			smoke->alpha_1,
			smoke->radius_1,

			smoke->colour_change_2,
			smoke->red_2,
			smoke->green_2,
			smoke->blue_2,
			smoke->alpha_2,
			smoke->radius_2,

			smoke->red_end,
			smoke->green_end,
			smoke->blue_end,
			smoke->alpha_end,
			smoke->radius_end,

			smoke->final_vertical_velocity,
			smoke->vertical_acceleration,
			smoke->initial_velocity_noise,
			smoke->texture_size,
			smoke->animation_rate,
			smoke->additive,
			smoke->draw_type,
			smoke->flat,
			smoke->ground_based,
			smoke->lock_to_parent,
			smoke->wind_affected);
	}
	safe_fclose (file);
}

static void import_smoke_list_database (void)
{
	FILE
		*file;
	char
		buf[2048],
		*ptr,
		*smoke_list_type_name,
		*texture_animation;
	int
		count;
	smoke_list_data
		*smoke;
	int
		red_start,
		green_start,
		blue_start,
		alpha_start,
		red_1,
		green_1,
		blue_1,
		alpha_1,
		red_2,
		green_2,
		blue_2,
		alpha_2,
		red_end,
		green_end,
		blue_end,
		alpha_end,
		additive,
		draw_type,
		flat,
		ground_based,
		lock_to_parent,
		wind_affected;

	file = safe_fopen (SMOKE_LIST_DATABASE_FILENAME, "r");
	fgets (buf, sizeof (buf), file);
	if (!strcmp (buf, "SMOKE;1\n"))
	{
		while (fgets (buf, sizeof (buf), file))
		{
			ptr = strchr (buf, '#');
			if (ptr)
			{
				*ptr = '\0';
			}
			ptr = strchr (buf, ';');
			if (!ptr)
			{
				continue;
			}
			smoke_list_type_name = ptr + 1;
			ptr = strchr (smoke_list_type_name, ';');
			if (!ptr)
			{
				continue;
			}
			*ptr = '\0';
			texture_animation = ptr + 1;
			ptr = strchr (texture_animation, ';');
			if (!ptr)
			{
				continue;
			}
			*ptr = '\0';
			if (sscanf (buf, "%i", &count) != 1 || count < 0)
			{
				continue;
			}
			count = get_smoke_type_by_name (smoke_list_type_name);
			if (count < 0)
			{
				if (!smoke_list_types_available)
				{
					continue;
				}
				count = total_number_of_smoke_list_types;
			}
			smoke = &smoke_list_database [count];
			if (sscanf (ptr + 1,
				"%i;%i;%i;%i;%f;"
				"%f;%i;%i;%i;%i;%f;"
				"%f;%i;%i;%i;%i;%f;"
				"%i;%i;%i;%i;%f;"
				"%f;%f;%f;"
				"%f;%f;%i;%i;%i;%i;%i;%i",
				&red_start,
				&green_start,
				&blue_start,
				&alpha_start,
				&smoke->radius_start,

				&smoke->colour_change_1,
				&red_1,
				&green_1,
				&blue_1,
				&alpha_1,
				&smoke->radius_1,

				&smoke->colour_change_2,
				&red_2,
				&green_2,
				&blue_2,
				&alpha_2,
				&smoke->radius_2,

				&red_end,
				&green_end,
				&blue_end,
				&alpha_end,
				&smoke->radius_end,

				&smoke->final_vertical_velocity,
				&smoke->vertical_acceleration,
				&smoke->initial_velocity_noise,

				&smoke->texture_size,
				&smoke->animation_rate,
				&additive,
				&draw_type,
				&flat,
				&ground_based,
				&lock_to_parent,
				&wind_affected) != 33)
			{
				continue;
			}
			smoke->red_start = (unsigned char)bound (red_start, 0, 255);
			smoke->green_start = (unsigned char)bound (green_start, 0, 255);
			smoke->blue_start = (unsigned char)bound (blue_start, 0, 255);
			smoke->alpha_start = (unsigned char)bound (alpha_start, 0, 255);
			smoke->red_1 = (unsigned char)bound (red_1, 0, 255);
			smoke->green_1 = (unsigned char)bound (green_1, 0, 255);
			smoke->blue_1 = (unsigned char)bound (blue_1, 0, 255);
			smoke->alpha_1 = (unsigned char)bound (alpha_1, 0, 255);
			smoke->red_2 = (unsigned char)bound (red_2, 0, 255);
			smoke->green_2 = (unsigned char)bound (green_2, 0, 255);
			smoke->blue_2 = (unsigned char)bound (blue_2, 0, 255);
			smoke->alpha_2 = (unsigned char)bound (alpha_2, 0, 255);
			smoke->red_end = (unsigned char)bound (red_end, 0, 255);
			smoke->green_end = (unsigned char)bound (green_end, 0, 255);
			smoke->blue_end = (unsigned char)bound (blue_end, 0, 255);
			smoke->alpha_end = (unsigned char)bound (alpha_end, 0, 255);
			smoke->texture = (texture_animation_indices)add_new_animation (texture_animation);
			smoke->additive = additive != 0;
			smoke->draw_type = draw_type != 0;
			smoke->flat = flat != 0;
			smoke->ground_based = ground_based != 0;
			smoke->lock_to_parent = lock_to_parent != 0;
			smoke->wind_affected = wind_affected != 0;

			if (count == total_number_of_smoke_list_types)
			{
				count = strlen (smoke_list_type_name) + 1;
				smoke_list_types_names[total_number_of_smoke_list_types] = (char*) safe_malloc (count);
				memcpy (smoke_list_types_names[total_number_of_smoke_list_types], smoke_list_type_name, count);
				total_number_of_smoke_list_types++;
				smoke_list_types_available--;
			}
		}
	}
	safe_fclose (file);
}
// 01DEC10 Casm Smoke database import/export end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_smoke_list_database (void)
{
	smoke_list_data
		*item;

	total_number_of_smoke_list_types = NUM_SMOKE_LIST_TYPES;
	smoke_list_types_available = 50;

	initialise_smoke_list_types_names ();

	smoke_list_database = (smoke_list_data *) safe_malloc (sizeof (smoke_list_data) * (total_number_of_smoke_list_types + smoke_list_types_available));

	////////////////////////////////////////
	//
	//	SMOKE_LIST_TYPE_GREY_TRAIL
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_GREY_TRAIL]);

		// START COLOUR
		item->red_start			=	200;		// red
		item->green_start			=	200;		// green
		item->blue_start 			=	200;		// blue
		item->alpha_start 		=	255;		// alpha
		item->radius_start		=	0.1;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;		// colour change 1 lifescale
		item->red_1					=	220;		// red
		item->green_1 				=	220;		// green
		item->blue_1 				=	220;		// blue
		item->alpha_1 				=	0;			// alpha
		item->radius_1 			=	10.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	200;			// red
		item->green_2				=	200;			// green
		item->blue_2				=	200;			// blue
		item->alpha_2				=	0;			// alpha
		item->radius_2 			=	20.0;		// radius

		// END COLOUR
		item->red_end				=	100;		// red
		item->green_end			=	100;		// green
		item->blue_end				=	100;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end 			=	30.0;		// radius

		item->final_vertical_velocity	=	1.5;
		item->vertical_acceleration	=	-0.5;

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
		item->red_start			=	80;		// red
		item->green_start			=	30;		// green
		item->blue_start 			=	30;		// blue
		item->alpha_start 		=	0;		// alpha
		item->radius_start		=	10.5;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.05;		// colour change 1 lifescale
		item->red_1					=	40;		// red
		item->green_1 				=	40;		// green
		item->blue_1 				=	40;		// blue
		item->alpha_1 				=	90;		// alpha
		item->radius_1 			=	30.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.125;		// colour change 2 lifescale
		item->red_2					=	 60;		// red
		item->green_2				=	 60;		// green
		item->blue_2				=	 60;		// blue
		item->alpha_2				=	30;		// alpha
		item->radius_2				=	101.5;		// radius

		// END COLOUR
		item->red_end				=	80;		// red
		item->green_end			=	80;		// green
		item->blue_end				=	80;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	300.0;		// radius

		item->final_vertical_velocity	=	2.5;
		item->vertical_acceleration	=	0.7;

		item->initial_velocity_noise	=	12.0;

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
	//	SMOKE_LIST_TYPE_FLAME
	//
	////////////////////////////////////////
	{
		item = &(smoke_list_database [SMOKE_LIST_TYPE_FLAME]);

		// START COLOUR
		item->red_start			=	80;		// red
		item->green_start			=	80;		// green
		item->blue_start 			=	50;		// blue
		item->alpha_start 		=	100;		// alpha
		item->radius_start		=	3.5;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.1;		// colour change 1 lifescale
		item->red_1					=	80;		// red
		item->green_1 				=	50;		// green
		item->blue_1 				=	40;		// blue
		item->alpha_1 				=	160;		// alpha
		item->radius_1 			=	5.5;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.2;		// colour change 2 lifescale
		item->red_2					=	60;		// red
		item->green_2				=	30;		// green
		item->blue_2				=	15;		// blue
		item->alpha_2				=	60;		// alpha
		item->radius_2				=	8.5;		// radius

		// END COLOUR
		item->red_end				=	30;		// red
		item->green_end			=	10;		// green
		item->blue_end				=	10;		// blue
		item->alpha_end			=	0;			// alpha
		item->radius_end			=	11.0;		// radius

		item->final_vertical_velocity	=	2.5;
		item->vertical_acceleration	=	2.2;

		item->initial_velocity_noise	=	1.0;

		item->texture						=	TEXTURE_ANIMATION_INDEX_CANNON_FLARE;
		item->texture_size				=	1.0;
		item->animation_rate				=	1.0;

		item->additive						=	TRUE;
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
		item->red_start			=	232;		// red
		item->green_start			=	232;		// green
		item->blue_start 			=	232;		// blue
		item->alpha_start 		=	255;		// alpha
		item->radius_start		=	5.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.2;		// colour change 1 lifescale
		item->red_1					=	210;		// red
		item->green_1 				=	210;		// green
		item->blue_1 				=	200;		// blue
		item->alpha_1 				=	200;		// alpha
		item->radius_1 			=	13.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	0.5;		// colour change 2 lifescale
		item->red_2					=	160;		// red
		item->green_2				=	160;		// green
		item->blue_2				=	160;		// blue
		item->alpha_2				=	40;		// alpha
		item->radius_2				=	24.0;		// radius

		// END COLOUR
		item->red_end				=	132;		// red
		item->green_end			=	132;			// green
		item->blue_end				=	132;		// blue
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
		item->alpha_start 		=	100;		// alpha
		item->radius_start		=	25.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	0.2;		// colour change 1 lifescale
		item->red_1					=	160;		// red
		item->green_1 				=	160;		// green
		item->blue_1 				=	160;		// blue
		item->alpha_1 				=	200;		// alpha
		item->radius_1 			=	50.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;		// colour change 2 lifescale
		item->red_2					=	120;		// red
		item->green_2				=	120;		// green
		item->blue_2				=	120;		// blue
		item->alpha_2				=	0;		// alpha
		item->radius_2				=	95.0;		// radius

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
		item->red_start			=	160;	// red
		item->green_start			=	140;	// green
		item->blue_start 			=	100;	// blue
		item->alpha_start 		=	40;	// alpha
		item->radius_start		=	6.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	 220;	// red
		item->green_1 				=	180;	// green
		item->blue_1 				=	120;	// blue
		item->alpha_1 				=	80;	// alpha
		item->radius_1 			=	12.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	 160;	// red
		item->green_2				=	 120;	// green
		item->blue_2				=	80;	// blue
		item->alpha_2				=	20;	// alpha
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
		item->animation_rate				=	1.5;

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
		item->alpha_start 		=	50;	// alpha
		item->radius_start		=	4.0;	// radius

		// COLOUR CHANGE 1
		item->colour_change_1	=	1.0;	// colour change 1 lifescale
		item->red_1					=	120;	// red
		item->green_1 				=	100;	// green
		item->blue_1 				=	40;	// blue
		item->alpha_1 				=	40;	// alpha
		item->radius_1 			=	8.0;	// radius

		// COLOUR CHANGE 2
		item->colour_change_2	=	1.0;	// colour change 2 lifescale
		item->red_2					=	120;	// red
		item->green_2				=	100;	// green
		item->blue_2				=	40;	// blue
		item->alpha_2				=	10;	// alpha
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
		item->alpha_start 			=	60;		// alpha
		item->radius_start			=	2.0;		// radius

		// COLOUR CHANGE 1
		item->colour_change_1		=	1.0;		// colour change 1 lifescale
		item->red_1						=	180;		// red
		item->green_1 					=	210;		// green
		item->blue_1 					=	255;		// blue
		item->alpha_1 					=	40;		// alpha
		item->radius_1 				=	4.0;		// radius

		// COLOUR CHANGE 2
		item->colour_change_2		=	1.0;		// colour change 2 lifescale
		item->red_2						=	180;		// red
		item->green_2					=	210;		// green
		item->blue_2					=	255;		// blue
		item->alpha_2					=	20;			// alpha
		item->radius_2					=	8.0;		// radius

		// END COLOUR
		item->red_end					=	0;			// red
		item->green_end				=	0;			// green
		item->blue_end					=	0;			// blue
		item->alpha_end				=	0;			// alpha
		item->radius_end				=	10.0;		// radius

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

	// 01DEC10 Casm Smoke database import/export
	if (file_exist (SMOKE_LIST_DATABASE_FILENAME))
	{
		import_smoke_list_database ();
	}
	else
	{
		export_smoke_list_database ();
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

	deinitialise_smoke_list_types_names ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
