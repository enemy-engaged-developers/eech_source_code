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

meta_explosion_data
	meta_explosion_database[NUM_META_EXPLOSION_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_misc_explosion_database(void);

static void initialise_armour_piercing_explosion_database(void);

static void initialise_high_explosive_explosion_database(void);

static void initialise_earth_explosion_database(void);

static void initialise_water_explosion_database(void);

static void initialise_object_dust_explosion_database(void);

static void initialise_object_explosive_explosion_database(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 01DEC10 Casm Explosion database import/export begin
#define META_EXPLOSION_DECLARATION(x)
#define META_EXPLOSION(x) #x,
#define META_EXPLOSION_(x) NULL
const char* meta_explosion_names[] =
{
#include "xp_types.h"
};
#undef META_EXPLOSION_DECLARATION
#undef META_EXPLOSION
#undef META_EXPLOSION_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define EXPLOSION_DATABASE_FILENAME "EXPLOS.CSV"

static void export_explosion_database(void)
{
	FILE
		*file;
	int
		count1,
		count2;
	const meta_explosion_data
		*ex;
	const meta_explosion_component
		*co;

	file = safe_fopen(EXPLOSION_DATABASE_FILENAME, "w");
	fprintf(file, "EXPLOSION;1\n");
	fprintf(file,
		"#Explosion index;Explosion name;Damage radius;Show on map\n"
		"#SPRITES;Animated texture;Sprites count;"
			"Colour (red;green;blue;alpha);"
			"Additive;Blast hemisphere only;"
			"Delay max;Lifetime min;Lifetime max;Scale min;Scale max;"
			"Blast radius;Animation frequency\n"
		"#OBJECTS;Object 3D shape;Objects count;"
			"Colour (red;green;blue;alpha);"
			"Additive;Blast hemisphere only;"
			"Delay max;Lifetime min;Lifetime max;Scale min;Scale max;"
			"Blast radius\n"
		"#PARTICLES;Trail type;Particle count;"
			"Initial speed\n"
		"#SMOKE_TRAILS;Trail type;Trail count;"
			"Generator lifetime;Frequency;Smoke lifetime;"
			"Initial velosity (x;y;z)\n"
		"#SOUND_EFFECT;Sound type;Sound volume\n"
		);
	for (count1 = 1; count1 < NUM_META_EXPLOSION_TYPES; count1++)
	{
		ex = &meta_explosion_database[count1];
		fprintf (file,
			"%i;%s;%f;%i\n",
			count1, meta_explosion_names[count1], ex->damage_radius, ex->show_on_map);
		for (count2 = 0; count2 < ex->number_of_components; count2++)
		{
			co = &ex->component[count2];
			switch (co->type)
			{
			case EXPLOSION_SPRITES:
				{
					fprintf(file,
						"SPRITES;%s;%i;"
						"%i;%i;%i;%i;"
						"%i;%i;"
						"%f;%f;%f;%f;%f;"
						"%f;%f\n",
						texture_animation_names[co->animated_texture], co->sprite_count,
						co->red, co->green, co->blue, co->alpha,
						co->additive, co->blast_hemisphere_only,
						co->delay_max, co->lifetime_min, co->lifetime_max, co->scale_min, co->scale_max,
						co->blast_radius, co->animation_frequency);
					break;
				}
			case EXPLOSION_OBJECTS:
				{
					fprintf(file,
						"OBJECTS;%s;%i;"
						"%i;%i;%i;%i;"
						"%i;%i;"
						"%f;%f;%f;%f;%f;"
						"%f\n",
						object_3d_enumeration_names[co->object_3d_shape], co->object_count,
						co->red, co->green, co->blue, co->alpha,
						co->additive, co->blast_hemisphere_only,
						co->delay_max, co->lifetime_min, co->lifetime_max, co->scale_min, co->scale_max,
						co->blast_radius);
					break;
				}
			case EXPLOSION_PARTICLES:
				{
					fprintf(file,
						"PARTICLES;%s;%i;"
						"%f\n",
						smoke_list_names[co->trail_type], co->particle_count,
						co->initial_speed);
					break;
				}
			case EXPLOSION_SMOKE_TRAILS:
				{
					fprintf(file,
						"SMOKE_TRAILS;%s;%i;"
						"%f;%f;%f;"
						"%f;%f;%f\n",
						smoke_list_names[co->trail_type], co->trail_count,
						co->generator_lifetime, co->frequency, co->smoke_lifetime,
						co->initial_velocity.x, co->initial_velocity.y, co->initial_velocity.z);
					break;
				}
			case EXPLOSION_SOUND_EFFECT:
				{
					char
						buf[128],
						*ptr;
					strcpy(buf, application_sound_effects[co->sound_type].name);
					ptr = strchr(buf, '.');
					if (ptr)
					{
						*ptr = '\0';
					}
					strupr(buf);
					fprintf(file,
						"SOUND_EFFECT;%s;%f\n",
						buf, co->sound_volume);
					break;
				}
			default:
				ASSERT(FALSE);
			}
		}
	}
	safe_fclose(file);
}

static void import_explosion_database(void)
{
	FILE
		*file;
	char
		buf[2048],
		*ptr,
		*name;
	int
		count,
		allocated,
		type;
	meta_explosion_data
		*ex;
	meta_explosion_component
		*co;
	int
		red,
		green,
		blue,
		alpha,
		additive,
		blast_hemisphere_only;

	file = safe_fopen(EXPLOSION_DATABASE_FILENAME, "r");
	fgets(buf, sizeof(buf), file);
	if (!strcmp(buf, "EXPLOSION;1\n"))
	{
		ex = NULL;
		while (fgets(buf, sizeof(buf), file))
		{
			ptr = strchr(buf, '#');
			if (ptr)
			{
				*ptr = '\0';
			}
			ptr = strchr(buf, ';');
			if (!ptr)
			{
				continue;
			}
			*ptr = '\0';
			name = ptr + 1;
			ptr = strchr(name, ';');
			if (!ptr)
			{
				continue;
			}
			*ptr = '\0';
			ptr++;

			type = NUM_EXPLOSION_COMPONENT_TYPES;
			if (!strcmp(buf, "SPRITES"))
			{
				type = EXPLOSION_SPRITES;
			}
			else if (!strcmp(buf, "OBJECTS"))
			{
				type = EXPLOSION_OBJECTS;
			}
			else if (!strcmp(buf, "PARTICLES"))
			{
				type = EXPLOSION_PARTICLES;
			}
			else if (!strcmp(buf, "SMOKE_TRAILS"))
			{
				type = EXPLOSION_SMOKE_TRAILS;
			}
			else if (!strcmp(buf, "SOUND_EFFECT"))
			{
				type = EXPLOSION_SOUND_EFFECT;
			}

			if (type == NUM_EXPLOSION_COMPONENT_TYPES)
			{
				ex = NULL;
				if (sscanf(buf, "%i", &count) != 1 || count <= 0 || count >= NUM_META_EXPLOSION_TYPES)
				{
					continue;
				}
				ex = &meta_explosion_database[count];
				if (sscanf(ptr, "%f;%i", &ex->damage_radius, &ex->show_on_map) != 2)
				{
					ex = NULL;
					continue;
				}
				allocated = ex->number_of_components;
				ex->number_of_components = 0;
			}
			else
			{
				if (!ex)
				{
					continue;
				}

				if (ex->number_of_components >= allocated)
				{
					allocated = allocated ? 2 * allocated : 8;
					co = (meta_explosion_component*)safe_malloc(sizeof(meta_explosion_component) * allocated);
					if (ex->number_of_components)
					{
						memcpy(co, ex->component, sizeof(meta_explosion_component) * ex->number_of_components);
						safe_free(ex->component);
					}
					ex->component = co;
				}
				co = &ex->component[ex->number_of_components];
				switch (co->type = (explosion_component_types)type)
				{
				case EXPLOSION_SPRITES:
					{
						co->animated_texture = (texture_animation_indices)get_object_3d_texture_animation_index_from_name(name);
						if (co->animated_texture < 0)
						{
							continue;
						}
						if (sscanf(ptr,
							"%i;"
							"%i;%i;%i;%i;"
							"%i;%i;"
							"%f;%f;%f;%f;%f;"
							"%f;%f",
							&co->sprite_count,
							&red, &green, &blue, &alpha,
							&additive, &blast_hemisphere_only,
							&co->delay_max, &co->lifetime_min, &co->lifetime_max, &co->scale_min, &co->scale_max,
							&co->blast_radius, &co->animation_frequency) != 14)
						{
							continue;
						}
						co->red = (unsigned char)bound (red, 0, 255);
						co->green = (unsigned char)bound (green, 0, 255);
						co->blue = (unsigned char)bound (blue, 0, 255);
						co->alpha = (unsigned char)bound (alpha, 0, 255);
						co->additive = additive != 0;
						co->blast_hemisphere_only = blast_hemisphere_only != 0;
						break;
					}
				case EXPLOSION_OBJECTS:
					{
						co->object_3d_shape = get_object_3d_index_from_name(name);
						if (!co->object_3d_shape)
						{
							continue;
						}
						if (sscanf(ptr,
							"%i;"
							"%i;%i;%i;%i;"
							"%i;%i;"
							"%f;%f;%f;%f;%f;"
							"%f",
							&co->object_count,
							&red, &green, &blue, &alpha,
							&additive, &blast_hemisphere_only,
							&co->delay_max, &co->lifetime_min, &co->lifetime_max, &co->scale_min, &co->scale_max,
							&co->blast_radius) != 13)
						{
							continue;
						}
						co->red = (unsigned char)bound (red, 0, 255);
						co->green = (unsigned char)bound (green, 0, 255);
						co->blue = (unsigned char)bound (blue, 0, 255);
						co->alpha = (unsigned char)bound (alpha, 0, 255);
						co->additive = additive != 0;
						co->blast_hemisphere_only = blast_hemisphere_only != 0;
						break;
					}
				case EXPLOSION_PARTICLES:
					{
						co->trail_type = get_smoke_type_by_name(name);
						if (co->trail_type < 0)
						{
							continue;
						}
						if (sscanf(ptr,
							"%i;"
							"%f",
							&co->particle_count,
							&co->initial_speed) != 2)
						{
							continue;
						}
						break;
					}
				case EXPLOSION_SMOKE_TRAILS:
					{
						co->trail_type = get_smoke_type_by_name(name);
						if (co->trail_type < 0)
						{
							continue;
						}
						if (sscanf(ptr,
							"%i;"
							"%f;%f;%f;"
							"%f;%f;%f",
							&co->trail_count,
							&co->generator_lifetime, &co->frequency, &co->smoke_lifetime,
							&co->initial_velocity.x, &co->initial_velocity.y, &co->initial_velocity.z) != 7)
						{
							continue;
						}
						break;
					}
				case EXPLOSION_SOUND_EFFECT:
					{
						int
							count;
						co->sound_type = -1;
						for (count = 0; count < NUM_SOUND_SAMPLE_INDICES; count++)
						{
							if (application_sound_effects[count].name)
							{
								char
									buf[128],
									*ptr;
								strcpy(buf, application_sound_effects[count].name);
								ptr = strchr(buf, '.');
								if (ptr)
								{
									*ptr = '\0';
								}
								if (!stricmp(buf, name))
								{
									co->sound_type = count;
									break;
								}
							}
						}
						if (co->sound_type < 0)
						{
							continue;
						}
						if (sscanf(ptr,
							"%f",
							&co->sound_volume) != 1)
						{
							continue;
						}
						break;
					}
				default:
					ASSERT(FALSE);
					continue;
				}
				ex->number_of_components++;
			}
		}
	}
	safe_fclose(file);
}
// 01DEC10 Casm Explosion database import/export end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_explosion_database(void)
{
	initialise_misc_explosion_database();

	initialise_armour_piercing_explosion_database();

	initialise_high_explosive_explosion_database();

	initialise_earth_explosion_database();

	initialise_water_explosion_database();

	initialise_object_dust_explosion_database();

	initialise_weapon_explosion_criteria_tables();

	initialise_object_explosive_explosion_database();

	// 01DEC10 Casm Explosion database import/export
	if (file_exist(EXPLOSION_DATABASE_FILENAME))
	{
		import_explosion_database();
	}
	else
	{
		export_explosion_database();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_misc_explosion_database(void)
{

	meta_explosion_component
		*explosion_info;

	meta_explosion_data
		*this_explosion;

	////////////////////////////////////////
	//
	// NONE
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ META_EXPLOSION_TYPE_NONE ]);

	this_explosion->number_of_components	=	0;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = NULL;

	////////////////////////////////////////
	//
	// TEST
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ TEST_META_EXPLOSION ]);

	this_explosion->number_of_components	=	3;

	this_explosion->damage_radius				=	20.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_MISSILE_FLARE;

	explosion_info->sprite_count 				=	5;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	FALSE;

	explosion_info->delay_max 					=	1.5;

	explosion_info->lifetime_min 				=	0.5;
	explosion_info->lifetime_max 				=	0.5;

	explosion_info->scale_min 					=	25.0;
	explosion_info->scale_max 					=	40.0;

	explosion_info->blast_radius		 		=	40.0;

	explosion_info->animation_frequency		=	1.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						= EXPLOSION_SPRITES;

	explosion_info->animated_texture 		= TEXTURE_ANIMATION_INDEX_MISSILE_FLARE;

	explosion_info->sprite_count 				= 6;

	explosion_info->red 							= 255;
	explosion_info->green 						= 255;
	explosion_info->blue 						= 255;
	explosion_info->alpha 						= 255;

	explosion_info->additive 					= TRUE;

	explosion_info->blast_hemisphere_only	= FALSE;

	explosion_info->delay_max 					= 1.5;

	explosion_info->lifetime_min 				= 0.5;
	explosion_info->lifetime_max 				= 0.5;

	explosion_info->scale_min 					= 25.0;
	explosion_info->scale_max 					= 40.0;

	explosion_info->blast_radius		 		= 10.0;

	explosion_info->animation_frequency		=	1.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 4;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_SMALL_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 30.0;

	////////////////////////////////////////
	//
	// PURPLE FLARE
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ PURPLE_FLARE_META_EXPLOSION ]);

	this_explosion->number_of_components	=	1;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_PURPLE_FLARE;

	explosion_info->trail_count 				=	1;

	explosion_info->generator_lifetime		= 70.0;
	explosion_info->frequency					= 0.33333;
	explosion_info->smoke_lifetime			= 30.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.0;
	explosion_info->initial_velocity.z		= 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_armour_piercing_explosion_database(void)
{

	meta_explosion_component
		*explosion_info;

	meta_explosion_data
		*this_explosion;

	////////////////////////////////////////
	//
	// SMALL A.P. EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_AP_META_EXPLOSION ]);

	this_explosion->number_of_components	=	1;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	1;

	explosion_info->red 							=	200;
	explosion_info->green 						= 	200;
	explosion_info->blue 						=	200;
	explosion_info->alpha 						=	200;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	FALSE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	0.5;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	0.5;
	explosion_info->scale_max 					=	1.5;

	explosion_info->blast_radius		 		=	0.5;

	explosion_info->animation_frequency		=	2.0;

	////////////////////////////////////////
	//
	// MEDIUM A.P. EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_AP_META_EXPLOSION ]);

	this_explosion->number_of_components	=	2;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	TRUE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	2;

	explosion_info->red 							=	140;
	explosion_info->green 						= 	140;
	explosion_info->blue 						=	140;
	explosion_info->alpha 						=	200;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	FALSE;

	explosion_info->delay_max 					=	0.25;

	explosion_info->lifetime_min 				=	0.75;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	2.0;
	explosion_info->scale_max 					=	5.0;

	explosion_info->blast_radius		 		=	2.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	2;

	explosion_info->red 							=	200;
	explosion_info->green 						= 	200;
	explosion_info->blue 						=	200;
	explosion_info->alpha 						=	200;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	FALSE;

	explosion_info->delay_max 					=	0.25;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	3.0;

	explosion_info->scale_min 					=	2.0;
	explosion_info->scale_max 					=	5.0;

	explosion_info->blast_radius		 		=	2.5;

	explosion_info->animation_frequency		=	2.0;

	////////////////////////////////////////
	//
	// LARGE A.P. EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_AP_META_EXPLOSION ]);

	this_explosion->number_of_components	=	2;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	TRUE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	5;

	explosion_info->red 							=	140;
	explosion_info->green 						= 	140;
	explosion_info->blue 						=	140;
	explosion_info->alpha 						=	200;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	FALSE;

	explosion_info->delay_max 					=	2.5;

	explosion_info->lifetime_min 				=	1.5;
	explosion_info->lifetime_max 				=	3.0;

	explosion_info->scale_min 					=	2.0;
	explosion_info->scale_max 					=	6.5;

	explosion_info->blast_radius		 		=	4.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	6;

	explosion_info->red 							=	180;
	explosion_info->green 						= 	180;
	explosion_info->blue 						=	180;
	explosion_info->alpha 						=	120;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	FALSE;

	explosion_info->delay_max 					=	2.5;

	explosion_info->lifetime_min 				=	3.2;
	explosion_info->lifetime_max 				=	5.5;

	explosion_info->scale_min 					=	3.0;
	explosion_info->scale_max 					=	7.0;

	explosion_info->blast_radius		 		=	4.5;

	explosion_info->animation_frequency		=	2.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_high_explosive_explosion_database(void)
{

	meta_explosion_component
		*explosion_info;

	meta_explosion_data
		*this_explosion;

	////////////////////////////////////////
	//
	// SMALL HE EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_HE_META_EXPLOSION ]);

	this_explosion->number_of_components	=	6;

	this_explosion->damage_radius				=	10.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_DEBRI;

	explosion_info->object_count 				=	0;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	2.0;
	explosion_info->scale_max 					=	2.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_CANNON_FLARE;

	explosion_info->sprite_count 				=	2;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.4;

	explosion_info->lifetime_min 				=	0.875;
	explosion_info->lifetime_max 				=	0.875;

	explosion_info->scale_min 					=	10.0;
	explosion_info->scale_max 					=	2.5;

	explosion_info->blast_radius		 		=	3.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_FIREBALL;

	explosion_info->object_count 				=	0;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	5.0;
	explosion_info->scale_max 					=	5.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 3
	//

	explosion_info = &(this_explosion->component[ 3 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_MISSILE_FLARE;

	explosion_info->sprite_count 				=	0;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.5;

	explosion_info->lifetime_min 				=	0.5;
	explosion_info->lifetime_max 				=	0.5;

	explosion_info->scale_min 					=	30.0;
	explosion_info->scale_max 					=	5.0;

	explosion_info->blast_radius		 		=	4.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 4
	//

	explosion_info = &(this_explosion->component[ 4 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_SMALL_EXPLOSION;
	explosion_info->sound_volume 				= 0.8;

	////////////////////////////////////////
	//
	// MEDIUM HE EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_HE_META_EXPLOSION ]);

	this_explosion->number_of_components	=	6;

	this_explosion->damage_radius				=	30.0;

	this_explosion->show_on_map				=	TRUE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_DEBRI;

	explosion_info->object_count 				=	1;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.5;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	3.0;
	explosion_info->scale_max 					=	3.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_FIREBALL;

	explosion_info->object_count 				=	0;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.5;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	8.0;
	explosion_info->scale_max 					=	8.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_CANNON_FLARE;

	explosion_info->sprite_count 				=	1;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	40.0;
	explosion_info->scale_max 					=	7.5;

	explosion_info->blast_radius		 		=	0.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 3
	//

	explosion_info = &(this_explosion->component[ 3 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_CANNON_FLARE;

	explosion_info->sprite_count 				=	1;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.3;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	30.0;
	explosion_info->scale_max 					=	5.0;

	explosion_info->blast_radius		 		=	6.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 4
	//

	explosion_info = &(this_explosion->component[ 4 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_MEDIUM_EXPLOSION;
	explosion_info->sound_volume 				= 1.0;

	//
	// Werewolf: distant explosion sound
	//

	explosion_info = &(this_explosion->component[ 5 ]);
	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;
	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_1;
	explosion_info->sound_volume 				= 1.0;

	////////////////////////////////////////
	//
	// LARGE HE EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_HE_META_EXPLOSION ]);

	this_explosion->number_of_components	=	8;

	this_explosion->damage_radius				=	60.0;

	this_explosion->show_on_map				=	TRUE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_DEBRI;

	explosion_info->object_count 				=	1;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.75;
	explosion_info->lifetime_max 				=	1.75;

	explosion_info->scale_min 					=	4.0;
	explosion_info->scale_max 					=	4.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_FIREBALL;

	explosion_info->object_count 				=	1;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.75;
	explosion_info->lifetime_max 				=	1.75;

	explosion_info->scale_min 					=	10.0;
	explosion_info->scale_max 					=	10.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_CANNON_FLARE;

	explosion_info->sprite_count 				=	3;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	1.0;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	50.0;
	explosion_info->scale_max 					=	10.0;

	explosion_info->blast_radius		 		=	18.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 3
	//

	explosion_info = &(this_explosion->component[ 3 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_MISSILE_FLARE;

	explosion_info->sprite_count 				=	3;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.75;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	40.0;
	explosion_info->scale_max 					=	8.0;

	explosion_info->blast_radius		 		=	17.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 4
	//

	explosion_info = &(this_explosion->component[ 4 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_LARGE_EXPLOSION;
	explosion_info->sound_volume 				= 1.0;

	//
	// component 5
	//

	explosion_info = &(this_explosion->component[ 5 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_FIREBALL;

	explosion_info->object_count 				=	0;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.5;

	explosion_info->lifetime_min 				=	1.75;
	explosion_info->lifetime_max 				=	1.75;

	explosion_info->scale_min 					=	10.0;
	explosion_info->scale_max 					=	10.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 6
	//

	explosion_info = &(this_explosion->component[ 6 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 0;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_SMALL_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 30.0;

	//
	// Werewolf: distant explosion sound
	//

	explosion_info = &(this_explosion->component[ 7 ]);
	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;
	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_1;
	explosion_info->sound_volume 				= 1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_earth_explosion_database(void)
{

	meta_explosion_component
		*explosion_info;

	meta_explosion_data
		*this_explosion;

	////////////////////////////////////////
	//
	// SMALL EARTH EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_EARTH_META_EXPLOSION ]);

	this_explosion->number_of_components	=	2;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	2;

	explosion_info->red 							=	80;
	explosion_info->green 						= 	60;
	explosion_info->blue 						=	20;
	explosion_info->alpha 						=	140;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.25;

	explosion_info->lifetime_min 				=	0.75;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	4.0;
	explosion_info->scale_max 					=	6.0;

	explosion_info->blast_radius		 		=	5.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_GROUND_STRAFE;
	explosion_info->sound_volume 				= 1.0;

	////////////////////////////////////////
	//
	// MEDIUM EARTH EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_EARTH_META_EXPLOSION ]);

	this_explosion->number_of_components	=	2;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	2;

	explosion_info->red 							=	80;
	explosion_info->green 						= 	60;
	explosion_info->blue 						=	20;
	explosion_info->alpha 						=	140;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.25;

	explosion_info->lifetime_min 				=	0.75;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	4.0;
	explosion_info->scale_max 					=	6.0;

	explosion_info->blast_radius		 		=	5.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 4;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_MEDIUM_EARTH_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 15.0;

	////////////////////////////////////////
	//
	// LARGE EARTH EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_EARTH_META_EXPLOSION ]);

	this_explosion->number_of_components	=	2;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	5;

	explosion_info->red 							=	80;
	explosion_info->green 						= 	60;
	explosion_info->blue 						=	20;
	explosion_info->alpha 						=	140;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.25;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	2.5;

	explosion_info->scale_min 					=	6.0;
	explosion_info->scale_max 					=	8.0;

	explosion_info->blast_radius		 		=	6.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 6;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_MEDIUM_EARTH_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 20.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_water_explosion_database(void)
{

	meta_explosion_component
		*explosion_info;

	meta_explosion_data
		*this_explosion;

	////////////////////////////////////////
	//
	// SMALL WATER EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_WATER_META_EXPLOSION ]);

	this_explosion->number_of_components	=	2;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 3;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_MEDIUM_WATER_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 5.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_SMALL_WATER_SPLASH;
	explosion_info->sound_volume 				= 0.75;

	////////////////////////////////////////
	//
	// MEDIUM WATER EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_WATER_META_EXPLOSION ]);

	this_explosion->number_of_components	=	3;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	2;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	140;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.25;

	explosion_info->lifetime_min 				=	0.75;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	4.0;
	explosion_info->scale_max 					=	6.0;

	explosion_info->blast_radius		 		=	5.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 4;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_MEDIUM_WATER_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 15.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_LARGE_WATER_SPLASH;
	explosion_info->sound_volume 				= 0.7;

	////////////////////////////////////////
	//
	// LARGE WATER EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_WATER_META_EXPLOSION ]);

	this_explosion->number_of_components	=	3;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	5;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	140;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.25;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	2.5;

	explosion_info->scale_min 					=	6.0;
	explosion_info->scale_max 					=	8.0;

	explosion_info->blast_radius		 		=	6.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 6;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_MEDIUM_WATER_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 25.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_LARGE_WATER_SPLASH;
	explosion_info->sound_volume 				= 1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_object_dust_explosion_database(void)
{

	meta_explosion_component
		*explosion_info;

	meta_explosion_data
		*this_explosion;

	////////////////////////////////////////
	//
	// SMALL DUST EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_DUST_META_EXPLOSION ]);

	this_explosion->number_of_components	=	1;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	6;

	explosion_info->red 							=	200;
	explosion_info->green 						= 	200;
	explosion_info->blue 						=	200;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.75;

	explosion_info->lifetime_min 				=	0.35;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	5.0;
	explosion_info->scale_max 					=	8.0;

	explosion_info->blast_radius		 		=	-1.0;

	explosion_info->animation_frequency		=	0.0;

	////////////////////////////////////////
	//
	// MEDIUM DUST EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_DUST_META_EXPLOSION ]);

	this_explosion->number_of_components	=	4;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	6;

	explosion_info->red 							=	200;
	explosion_info->green 						= 	200;
	explosion_info->blue 						=	200;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.75;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	2.0;

	explosion_info->scale_min 					=	7.0;
	explosion_info->scale_max 					=	10.0;

	explosion_info->blast_radius		 		=	-1.0;

	explosion_info->animation_frequency		=	0.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	6;

	explosion_info->red 							=	140;
	explosion_info->green 						= 	140;
	explosion_info->blue 						=	140;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.75;

	explosion_info->lifetime_min 				=	0.5;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	7.0;
	explosion_info->scale_max 					=	10.0;

	explosion_info->blast_radius		 		=	-1.0;

	explosion_info->animation_frequency		=	0.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_RUBBLE;
	explosion_info->sound_volume 				= 0.65;

	//
	// component 3
	//

	explosion_info = &(this_explosion->component[ 3 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_LARGE_DUST_CLOUD;

	explosion_info->trail_count 				=	1;

	explosion_info->generator_lifetime		= 10.0;
	explosion_info->frequency					= 0.6;
	explosion_info->smoke_lifetime			= 30.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.2;
	explosion_info->initial_velocity.z		= 0.0;

	////////////////////////////////////////
	//
	// LARGE DUST EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_DUST_META_EXPLOSION ]);

	this_explosion->number_of_components	=	5;

	this_explosion->damage_radius				=	0.0;

	this_explosion->show_on_map				=	FALSE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	4;

	explosion_info->red 							=	200;
	explosion_info->green 						= 	200;
	explosion_info->blue 						=	200;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.5;
	explosion_info->lifetime_max 				=	4.0;

	explosion_info->scale_min 					=	25.0;
	explosion_info->scale_max 					=	45.0;

	explosion_info->blast_radius		 		=	-1.0;

	explosion_info->animation_frequency		=	0.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_SMOKE;

	explosion_info->sprite_count 				=	4;

	explosion_info->red 							=	140;
	explosion_info->green 						= 	140;
	explosion_info->blue 						=	140;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	FALSE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	1.0;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	3.5;

	explosion_info->scale_min 					=	20.0;
	explosion_info->scale_max 					=	30.0;

	explosion_info->blast_radius		 		=	-1.0;

	explosion_info->animation_frequency		=	1.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 4;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_DUST_TRAIL_2;

	explosion_info->initial_speed 			= 20.0;

//	explosion_info->trail_scale 				= 15.0;

	//
	// component 3
	//

	explosion_info = &(this_explosion->component[ 3 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_LARGE_DUST_CLOUD;

	explosion_info->trail_count 				=	1;

	explosion_info->generator_lifetime		= 20.0;
	explosion_info->frequency					= 0.5;
	explosion_info->smoke_lifetime			= 40.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.2;
	explosion_info->initial_velocity.z		= 0.0;

	//
	// component 4
	//

	explosion_info = &(this_explosion->component[ 4 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_RUBBLE;
	explosion_info->sound_volume 				= 1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_object_explosive_explosion_database(void)
{

	meta_explosion_component
		*explosion_info;

	meta_explosion_data
		*this_explosion;

	////////////////////////////////////////
	//
	// SMALL EXPLOSIVE OBJECT EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_EXPLOSIVE_OBJECT_META_EXPLOSION ]);

	this_explosion->number_of_components	=	4;

	this_explosion->damage_radius				=	10.0;

	this_explosion->show_on_map				=	TRUE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_DEBRI;

	explosion_info->object_count 				=	1;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	2.0;
	explosion_info->scale_max 					=	2.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_CANNON_FLARE;

	explosion_info->sprite_count 				=	3;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.4;

	explosion_info->lifetime_min 				=	0.875;
	explosion_info->lifetime_max 				=	0.875;

	explosion_info->scale_min 					=	10.0;
	explosion_info->scale_max 					=	2.5;

	explosion_info->blast_radius		 		=	3.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_SMALL_EXPLOSION;
	explosion_info->sound_volume 				= 1.0;

	//
	// Werewolf: distant explosion sound
	//

	explosion_info = &(this_explosion->component[ 3 ]);
	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;
	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_1;
	explosion_info->sound_volume 				= 1.0;

	////////////////////////////////////////
	//
	// MEDIUM EXPLOSIVE OBJECT EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_EXPLOSIVE_OBJECT_META_EXPLOSION ]);

	this_explosion->number_of_components	=	9;

	this_explosion->damage_radius				=	30.0;

	this_explosion->show_on_map				=	TRUE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_DEBRI;

	explosion_info->object_count 				=	1;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.5;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	4.0;
	explosion_info->scale_max 					=	5.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_FIREBALL;

	explosion_info->object_count 				=	1;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.5;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	8.0;
	explosion_info->scale_max 					=	10.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_CANNON_FLARE;

	explosion_info->sprite_count 				=	2;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	40.0;
	explosion_info->scale_max 					=	7.5;

	explosion_info->blast_radius		 		=	0.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 3
	//

	explosion_info = &(this_explosion->component[ 3 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 2;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_SMALL_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 30.0;

	//
	// component 4
	//

	explosion_info = &(this_explosion->component[ 4 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_MEDIUM_EXPLOSION;
	explosion_info->sound_volume 				= 1.0;

	//
	// component 5: Black smoke
	//

	explosion_info = &(this_explosion->component[ 5 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_FIRE;

	explosion_info->trail_count 				=	1;

	if (command_line_persistent_smoke)
		explosion_info->generator_lifetime		= 400.0;
	else
		explosion_info->generator_lifetime		= 5.0;
	explosion_info->frequency					= 1.0;
	explosion_info->smoke_lifetime			= 100.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.1;
	explosion_info->initial_velocity.z		= 0.0;

	//
	// component 6: Flame
	//

	explosion_info = &(this_explosion->component[ 6 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_FLAME;

	explosion_info->trail_count 				=	1;

	if (command_line_persistent_smoke)
		explosion_info->generator_lifetime		= 120.0;
	else
		explosion_info->generator_lifetime		= 5.0;
	explosion_info->frequency					= 0.3;
	explosion_info->smoke_lifetime			= 4.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.2;
	explosion_info->initial_velocity.z		= 0.0;

	//
	// component 7: Flame
	//

	explosion_info = &(this_explosion->component[ 7 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_FLAME;

	explosion_info->trail_count 				=	1;

	if (command_line_persistent_smoke)
		explosion_info->generator_lifetime		= 200.0;
	else
		explosion_info->generator_lifetime		= 5.0;
	explosion_info->frequency					= 0.2;
	explosion_info->smoke_lifetime			= 3.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.2;
	explosion_info->initial_velocity.z		= 0.0;

	//
	// Werewolf: distant explosion sound
	//

	explosion_info = &(this_explosion->component[ 8 ]);
	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;
	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_1;
	explosion_info->sound_volume 				= 1.0;

	////////////////////////////////////////
	//
	// LARGE EXPLOSIVE OBJECT EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_EXPLOSIVE_OBJECT_META_EXPLOSION ]);

	this_explosion->number_of_components	=	10;

	this_explosion->damage_radius				=	60.0;

	this_explosion->show_on_map				=	TRUE;

	this_explosion->component = (meta_explosion_component *) malloc_fast_mem( sizeof( meta_explosion_component ) * this_explosion->number_of_components );

	//
	// component 0
	//

	explosion_info = &(this_explosion->component[ 0 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_DEBRI;

	explosion_info->object_count 				=	1;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	2.0;
	explosion_info->lifetime_max 				=	2.0;

	explosion_info->scale_min 					=	8.0;
	explosion_info->scale_max 					=	10.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 1
	//

	explosion_info = &(this_explosion->component[ 1 ]);

	explosion_info->type 						=	EXPLOSION_OBJECTS;

	explosion_info->object_3d_shape 			=	OBJECT_3D_EFFECT_FIREBALL;

	explosion_info->object_count 				=	1;

	explosion_info->red 							=	160;
	explosion_info->green 						= 	160;
	explosion_info->blue 						=	160;
	explosion_info->alpha 						=	180;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.0;

	explosion_info->lifetime_min 				=	1.75;
	explosion_info->lifetime_max 				=	1.75;

	explosion_info->scale_min 					=	12.0;
	explosion_info->scale_max 					=	15.0;

	explosion_info->blast_radius		 		=	0.0;

	//
	// component 2
	//

	explosion_info = &(this_explosion->component[ 2 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_CANNON_FLARE;

	explosion_info->sprite_count 				=	5;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	1.0;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.5;

	explosion_info->scale_min 					=	50.0;
	explosion_info->scale_max 					=	10.0;

	explosion_info->blast_radius		 		=	18.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 3
	//

	explosion_info = &(this_explosion->component[ 3 ]);

	explosion_info->type 						=	EXPLOSION_SPRITES;

	explosion_info->animated_texture 		=	TEXTURE_ANIMATION_INDEX_MISSILE_FLARE;

	explosion_info->sprite_count 				=	3;

	explosion_info->red 							=	255;
	explosion_info->green 						= 	255;
	explosion_info->blue 						=	255;
	explosion_info->alpha 						=	255;

	explosion_info->additive 					=	TRUE;

	explosion_info->blast_hemisphere_only	=	TRUE;

	explosion_info->delay_max 					=	0.75;

	explosion_info->lifetime_min 				=	1.0;
	explosion_info->lifetime_max 				=	1.0;

	explosion_info->scale_min 					=	40.0;
	explosion_info->scale_max 					=	8.0;

	explosion_info->blast_radius		 		=	17.0;

	explosion_info->animation_frequency		=	2.0;

	//
	// component 4
	//

	explosion_info = &(this_explosion->component[ 4 ]);

	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;

	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_LARGE_EXPLOSION;
	explosion_info->sound_volume 				= 1.0;

	//
	// component 5
	//

	explosion_info = &(this_explosion->component[ 5 ]);

	explosion_info->type 						= EXPLOSION_PARTICLES;

	explosion_info->particle_count 			= 8;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_SMALL_PARTICLE_TRAIL;

	explosion_info->initial_speed 			= 30.0;

	//
	// component 6
	//

	explosion_info = &(this_explosion->component[ 6 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_FIRE;

	explosion_info->trail_count 				=	1;

	if (command_line_persistent_smoke)
		explosion_info->generator_lifetime		= 1200.0;
	else
		explosion_info->generator_lifetime		= 10.0;
	explosion_info->frequency					= 1.0;
	explosion_info->smoke_lifetime			= 200.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.2;
	explosion_info->initial_velocity.z		= 0.0;

	//
	// component 7: Flame
	//

	explosion_info = &(this_explosion->component[ 7 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_FLAME;

	explosion_info->trail_count 				=	1;

	if (command_line_persistent_smoke)
		explosion_info->generator_lifetime		= 120.0;
	else
		explosion_info->generator_lifetime		= 5.0;
	explosion_info->frequency					= 0.3;
	explosion_info->smoke_lifetime			= 4.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.2;
	explosion_info->initial_velocity.z		= 0.0;

	//
	// component 8: Flame
	//

	explosion_info = &(this_explosion->component[ 8 ]);

	explosion_info->type 						= EXPLOSION_SMOKE_TRAILS;

	explosion_info->trail_type 				= SMOKE_LIST_TYPE_FLAME;

	explosion_info->trail_count 				=	1;

	if (command_line_persistent_smoke)
		explosion_info->generator_lifetime		= 200.0;
	else
		explosion_info->generator_lifetime		= 10.0;
	explosion_info->frequency					= 0.2;
	explosion_info->smoke_lifetime			= 3.0;

	explosion_info->initial_velocity.x		= 0.0;
	explosion_info->initial_velocity.y		= 0.2;
	explosion_info->initial_velocity.z		= 0.0;

	//
	// Werewolf: distant explosion sound
	//

	explosion_info = &(this_explosion->component[ 9 ]);
	explosion_info->type 						= EXPLOSION_SOUND_EFFECT;
	explosion_info->sound_type 				= SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_1;
	explosion_info->sound_volume 				= 1.0;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_explosion_database(void)
{

	meta_explosion_data
		*this_explosion;

	deinitialise_weapon_explosion_criteria_tables();

	////////////////////////////////////////
	//
	// TEST
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ TEST_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// PURPLE FLARE
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ PURPLE_FLARE_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// SMALL AP EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_AP_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// MEDIUM AP EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_AP_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// LARGE AP EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_AP_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// SMALL HE EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_HE_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// MEDIUM HE EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_HE_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// LARGE HE EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_HE_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// SMALL EARTH EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_EARTH_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// MEDIUM EARTH EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_EARTH_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// LARGE EARTH EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_EARTH_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// SMALL WATER EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_WATER_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// MEDIUM WATER EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_WATER_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// LARGE WATER EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_WATER_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// SMALL DUST EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_DUST_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// MEDIUM DUST EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_DUST_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// LARGE DUST EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_DUST_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// SMALL EXPLOSIVE OBJECT EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ SMALL_EXPLOSIVE_OBJECT_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// MEDIUM EXPLOSIVE OBJECT EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ MEDIUM_EXPLOSIVE_OBJECT_META_EXPLOSION ]);

	free_mem( this_explosion->component );

	////////////////////////////////////////
	//
	// LARGE EXPLOSIVE OBJECT EXPLOSION
	//
	////////////////////////////////////////

	this_explosion = &(meta_explosion_database[ LARGE_EXPLOSIVE_OBJECT_META_EXPLOSION ]);

	free_mem( this_explosion->component );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




