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

//#define BRIEFING_FILE	"..\\common\\data\\briefing.dat"

//#define DEBRIEFING_FILE	"..\\common\\data\\debrief.dat"

#define BRIEF_PATH	"..\\common\\data\\"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BRIEFING_SUBSTITUTION_TYPE
{

	char
		*string,
		*position_ptr;

	void
		((*function) (entity *task, medal_types medal, pilot_rank_types rank, char **text_buffer));
};

typedef struct BRIEFING_SUBSTITUTION_TYPE briefing_substitution_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void build_substitution_info (entity *task, medal_types medal, pilot_rank_types rank, char *text_buffer, char *destination_text);

static void briefing_add_position (entity *en, medal_types medal, pilot_rank_types rank, char **text);

static void briefing_add_sector (entity *en, medal_types medal, pilot_rank_types rank, char **text);

static void briefing_add_keysite (entity *en, medal_types medal, pilot_rank_types rank, char **text);

//static void briefing_add_keysite_type (entity *keysite, medal_types medal, pilot_rank_types rank, char **text);

static void briefing_add_group (entity *task, medal_types medal, pilot_rank_types rank, char **text);

static void briefing_add_target_type (entity *task, medal_types medal, pilot_rank_types rank, char **text);

static void briefing_add_medal (entity *task, medal_types medal, pilot_rank_types rank, char **text);

static void briefing_add_rank (entity *task, medal_types medal, pilot_rank_types rank, char **text);

static task_briefing_type *get_task_briefing_data (entity_sub_types task_type);

static extra_briefing_type *get_extra_briefing_data (extra_briefing_types type, int sub_type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

task_briefing_type
	*task_briefing_database;

extra_briefing_type
	*extra_briefing_database;

char
	*us_medal_type_names [NUM_MEDAL_TYPES],
	*cis_medal_type_names [NUM_MEDAL_TYPES],
	*rank_type_names [NUM_PILOT_RANKS];

unsigned char
	*brief_filenames [] =
	{
		"brief_en.dat",
		"brief_fr.dat",
		"brief_de.dat",
		"brief_it.dat",
		"brief_sp.dat",
		"brief_rs.dat",
		"brief_pl.dat",
	};
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

briefing_substitution_type
	briefing_substitutions [] =
	{
		{
			"GROUP",
			NULL,
			&briefing_add_group,
		},
		{
			"KEYSITE",
			NULL,
			&briefing_add_keysite,
		},
		/*
		{
			"OBJECTIVE_TYPE",
			NULL,
			&briefing_add_keysite_type,
		},
		*/
		{
			"MEDAL",
			NULL,
			&briefing_add_medal,
		},
		{
			"POSITION",
			NULL,
			&briefing_add_position,
		},
		{
			"RANK",
			NULL,
			&briefing_add_rank,
		},
		{
			"SECTOR",
			NULL,
			&briefing_add_sector,
		},
		{
			"TARGET_TYPE",
			NULL,
			&briefing_add_target_type,
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_briefing_parser (void)
{

	int
		result;

	char
		temp_buffer [512],
		temp_filename [128];

	session_list_data_type
		*current_session;

	FILE
		*file_ptr;

	file_tags
		tag;

	extra_briefing_database = NULL;

	//
	// read in briefing text
	//

	deinitialise_briefing_parser ();

	ASSERT (get_valid_current_game_session ());

	current_session = get_current_game_session ();

	result = get_global_current_language ();

	sprintf (temp_filename, "%s%s", BRIEF_PATH, brief_filenames [result]);

	file_ptr = safe_fopen (temp_filename, "r");

	task_briefing_database = (task_briefing_type *) malloc_heap_mem (sizeof (task_briefing_type) * NUM_ENTITY_SUB_TYPE_TASKS);
	memset (task_briefing_database, 0, sizeof (task_briefing_type) * NUM_ENTITY_SUB_TYPE_TASKS);

	while (TRUE)
	{

		tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

		switch (tag)
		{

			case FILE_TAG_START:
			{

				break;
			}

			case FILE_TAG_TYPE:
			{

				entity_sub_types
					task_type;

				task_type = get_next_file_enum (file_ptr, entity_sub_type_task_names, NUM_ENTITY_SUB_TYPE_TASKS);

				task_briefing_database [task_type].task_type = task_type;
					
				task_briefing_database [task_type].briefing_text1_count = 0;
				task_briefing_database [task_type].briefing_text2_count = 0;
				task_briefing_database [task_type].briefing_text3_count = 0;
				task_briefing_database [task_type].debriefing_text_success_count = 0;
				task_briefing_database [task_type].debriefing_text_partial_count = 0;
				task_briefing_database [task_type].debriefing_text_failure_count = 0;

				#if DEBUG_MODULE

				debug_log ("BRIEFING: reading in Briefing text for mission %s", entity_sub_type_task_names [task_type]);

				#endif

				//
				// Briefing text
				//

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) != FILE_TAG_END)
				{

					ASSERT (task_briefing_database [task_type].briefing_text1_count < MAX_NUMBER_OF_MISSION_TEXTS);
					ASSERT (task_briefing_database [task_type].briefing_text2_count < MAX_NUMBER_OF_MISSION_TEXTS);
					ASSERT (task_briefing_database [task_type].briefing_text3_count < MAX_NUMBER_OF_MISSION_TEXTS);

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					switch (result)
					{

						case FILE_TAG_TEXT1:
						{
			
							memset (&temp_buffer, 0, sizeof (temp_buffer));
							get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));
							task_briefing_database [task_type].briefing_text1 [task_briefing_database [task_type].briefing_text1_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
							sprintf (task_briefing_database [task_type].briefing_text1 [task_briefing_database [task_type].briefing_text1_count], "%s", &temp_buffer);

							#if DEBUG_MODULE

							debug_log ("BRIEFING: 		text1 (count %d) :- %s", task_briefing_database [task_type].briefing_text1_count, task_briefing_database [task_type].briefing_text1 [task_briefing_database [task_type].briefing_text1_count]);

							#endif

							task_briefing_database [task_type].briefing_text1_count ++;
			
							break;
						}

						case FILE_TAG_TEXT2:
						{
			
							memset (&temp_buffer, 0, sizeof (temp_buffer));
							get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));
							task_briefing_database [task_type].briefing_text2 [task_briefing_database [task_type].briefing_text2_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
							sprintf (task_briefing_database [task_type].briefing_text2 [task_briefing_database [task_type].briefing_text2_count], "%s", &temp_buffer);

							#if DEBUG_MODULE

							debug_log ("BRIEFING: 		text2 (count %d) :- %s", task_briefing_database [task_type].briefing_text2_count, task_briefing_database [task_type].briefing_text2 [task_briefing_database [task_type].briefing_text2_count]);

							#endif

							task_briefing_database [task_type].briefing_text2_count ++;
			
							break;
						}

						case FILE_TAG_TEXT3:
						{
			
							memset (&temp_buffer, 0, sizeof (temp_buffer));
							get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));
							task_briefing_database [task_type].briefing_text3 [task_briefing_database [task_type].briefing_text3_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
							sprintf (task_briefing_database [task_type].briefing_text3 [task_briefing_database [task_type].briefing_text3_count], "%s", &temp_buffer);

							#if DEBUG_MODULE

							debug_log ("BRIEFING: 		text3 (count %d) :- %s", task_briefing_database [task_type].briefing_text3_count, task_briefing_database [task_type].briefing_text3 [task_briefing_database [task_type].briefing_text3_count]);

							#endif

							task_briefing_database [task_type].briefing_text3_count ++;
			
							break;
						}
						default:
						{

							debug_fatal ("BRIEFING: unknown tag %d", result);
						}
					}

				}

				// read in file_tag_end
				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				//
				// Debriefing text
				//

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) != FILE_TAG_END)
				{

					ASSERT (task_briefing_database [task_type].debriefing_text_success_count < MAX_NUMBER_OF_MISSION_TEXTS);
					ASSERT (task_briefing_database [task_type].debriefing_text_partial_count < MAX_NUMBER_OF_MISSION_TEXTS);
					ASSERT (task_briefing_database [task_type].debriefing_text_failure_count < MAX_NUMBER_OF_MISSION_TEXTS);

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					switch (result)
					{

						case FILE_TAG_SUCCESS:
						{
			
							memset (&temp_buffer, 0, sizeof (temp_buffer));
							get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));
							task_briefing_database [task_type].debriefing_text_success [task_briefing_database [task_type].debriefing_text_success_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
							sprintf (task_briefing_database [task_type].debriefing_text_success [task_briefing_database [task_type].debriefing_text_success_count], "%s", &temp_buffer);

							#if DEBUG_MODULE

							debug_log ("BRIEFING: 		text_success (count %d) :- %s", task_briefing_database [task_type].debriefing_text_success_count, task_briefing_database [task_type].debriefing_text_success [task_briefing_database [task_type].debriefing_text_success_count]);

							#endif

							task_briefing_database [task_type].debriefing_text_success_count ++;
			
							break;
						}

						case FILE_TAG_PARTIAL:
						{
			
							memset (&temp_buffer, 0, sizeof (temp_buffer));
							get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));
							task_briefing_database [task_type].debriefing_text_partial [task_briefing_database [task_type].debriefing_text_partial_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
							sprintf (task_briefing_database [task_type].debriefing_text_partial [task_briefing_database [task_type].debriefing_text_partial_count], "%s", &temp_buffer);

							#if DEBUG_MODULE

							debug_log ("BRIEFING: 		text_partial (count %d) :- %s", task_briefing_database [task_type].debriefing_text_partial_count, task_briefing_database [task_type].debriefing_text_partial [task_briefing_database [task_type].debriefing_text_partial_count]);

							#endif

							task_briefing_database [task_type].debriefing_text_partial_count ++;
			
							break;
						}

						case FILE_TAG_FAILURE:
						{
			
							memset (&temp_buffer, 0, sizeof (temp_buffer));
							get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));
							task_briefing_database [task_type].debriefing_text_failure [task_briefing_database [task_type].debriefing_text_failure_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
							sprintf (task_briefing_database [task_type].debriefing_text_failure [task_briefing_database [task_type].debriefing_text_failure_count], "%s", &temp_buffer);

							#if DEBUG_MODULE

							debug_log ("BRIEFING: 		text_failure (count %d) :- %s", task_briefing_database [task_type].debriefing_text_failure_count, task_briefing_database [task_type].debriefing_text_failure [task_briefing_database [task_type].debriefing_text_failure_count]);

							#endif

							task_briefing_database [task_type].debriefing_text_failure_count ++;
			
							break;
						}
						default:
						{

							debug_fatal ("BRIEFING: unknown tag %d", result);
						}
					}

				}

				// read in file_tag_end
				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				break;
			}

			case FILE_TAG_MEDAL:
			{

				medal_types
					medal_type;

				int
					current_medal_list;

				extra_briefing_type
					*new_medal_briefing;

				// create new medal type

				new_medal_briefing = (extra_briefing_type *) malloc_heap_mem (sizeof (extra_briefing_type));

				memset (new_medal_briefing, 0, sizeof (extra_briefing_type));

				// get all medals these texts apply to

				current_medal_list = 0;

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_TYPE)
				{

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					ASSERT (result == FILE_TAG_TYPE);
	
					medal_type = get_next_file_enum (file_ptr, medal_type_names, NUM_MEDAL_TYPES);
	
					current_medal_list |= (1 << medal_type);
				}

				new_medal_briefing->type = EXTRA_BRIEFING_MEDAL;

				new_medal_briefing->sub_type = current_medal_list;

				// read in N medal texts

				new_medal_briefing->text_count = 0;

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) != FILE_TAG_END)
				{

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					ASSERT (result == FILE_TAG_TEXT1);
			
					memset (&temp_buffer, 0, sizeof (temp_buffer));
					get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));

					new_medal_briefing->briefing_text [new_medal_briefing->text_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
					sprintf (new_medal_briefing->briefing_text [new_medal_briefing->text_count], "%s", &temp_buffer);

					new_medal_briefing->text_count ++;
				}

				// read in file_tag_end
				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				new_medal_briefing->next = extra_briefing_database;

				extra_briefing_database = new_medal_briefing;

				break;
			}

			case FILE_TAG_PROMOTION:
			{

				extra_briefing_type
					*new_promotion_briefing;

				// create new promotion type

				new_promotion_briefing = (extra_briefing_type *) malloc_heap_mem (sizeof (extra_briefing_type));

				memset (new_promotion_briefing, 0, sizeof (extra_briefing_type));

				new_promotion_briefing->type = EXTRA_BRIEFING_PROMOTION;

				new_promotion_briefing->sub_type = 0;

				// read in N promotion texts

				new_promotion_briefing->text_count = 0;

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) != FILE_TAG_END)
				{

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					ASSERT (result == FILE_TAG_TEXT1);
			
					memset (&temp_buffer, 0, sizeof (temp_buffer));
					get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));

					new_promotion_briefing->briefing_text [new_promotion_briefing->text_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
					sprintf (new_promotion_briefing->briefing_text [new_promotion_briefing->text_count], "%s", &temp_buffer);

					new_promotion_briefing->text_count ++;
				}

				// read in file_tag_end
				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				new_promotion_briefing->next = extra_briefing_database;

				extra_briefing_database = new_promotion_briefing;

				break;
			}

			case FILE_TAG_OBJECTIVES:
			{

				extra_briefing_type
					*new_objective_briefing;

				// create new objective type

				new_objective_briefing = (extra_briefing_type *) malloc_heap_mem (sizeof (extra_briefing_type));

				memset (new_objective_briefing, 0, sizeof (extra_briefing_type));

				// get all objective these texts apply to

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_TYPE);
	
				new_objective_briefing->type = EXTRA_BRIEFING_OBJECTIVES;

				new_objective_briefing->sub_type = get_next_file_enum (file_ptr, entity_sub_type_keysite_names, NUM_ENTITY_SUB_TYPE_KEYSITES);

				// read in N objective texts

				new_objective_briefing->text_count = 0;

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) != FILE_TAG_END)
				{

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					ASSERT (result == FILE_TAG_TEXT1);
			
					memset (&temp_buffer, 0, sizeof (temp_buffer));
					get_next_file_paragraph (file_ptr, temp_buffer, sizeof (temp_buffer));

					new_objective_briefing->briefing_text [new_objective_briefing->text_count] = (char *) malloc_heap_mem (sizeof (char) * (strlen (temp_buffer) + 1));
					sprintf (new_objective_briefing->briefing_text [new_objective_briefing->text_count], "%s", &temp_buffer);

					new_objective_briefing->text_count ++;
				}

				// read in file_tag_end
				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				new_objective_briefing->next = extra_briefing_database;

				extra_briefing_database = new_objective_briefing;

				break;
			}

			//*pilot_rank_names [] =
			case FILE_TAG_END:
			{

				fclose (file_ptr);

				return;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_briefing_parser (void)
{

	int
		loop,
		loop2;

	extra_briefing_type
		*this_medal;

	//
	// Briefing / Debriefing
	//

	if (task_briefing_database)
	{
	
		for (loop = 0; loop < NUM_ENTITY_SUB_TYPE_TASKS; loop ++)
		{

			for (loop2 = 0; loop2 < MAX_NUMBER_OF_MISSION_TEXTS; loop2 ++)
			{

				// briefing

				if (task_briefing_database [loop].briefing_text1 [loop2])
				{
		
					free_mem (task_briefing_database [loop].briefing_text1 [loop2]);
				}
		
				if (task_briefing_database [loop].briefing_text2 [loop2])
				{
		
					free_mem (task_briefing_database [loop].briefing_text2 [loop2]);
				}
		
				if (task_briefing_database [loop].briefing_text3 [loop2])
				{
		
					free_mem (task_briefing_database [loop].briefing_text3 [loop2]);
				}

				// debriefing
		
				if (task_briefing_database [loop].debriefing_text_success [loop2])
				{
		
					free_mem (task_briefing_database [loop].debriefing_text_success [loop2]);
				}
		
				if (task_briefing_database [loop].debriefing_text_partial [loop2])
				{
		
					free_mem (task_briefing_database [loop].debriefing_text_partial [loop2]);
				}
		
				if (task_briefing_database [loop].debriefing_text_failure [loop2])
				{
		
					free_mem (task_briefing_database [loop].debriefing_text_failure [loop2]);
				}
			}
		}

		free_mem (task_briefing_database);
	}

	//
	// Medals
	//

	while (extra_briefing_database)
	{

		this_medal = extra_briefing_database;

		extra_briefing_database = extra_briefing_database->next;

		// free medal

		for (loop = 0; loop < MAX_NUMBER_OF_MISSION_TEXTS; loop ++)
		{

			// text

			if (this_medal->briefing_text [loop])
			{
	
				free_mem (this_medal->briefing_text [loop]);
			}
		}

		free_mem (this_medal);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void build_substitution_info (entity *task, medal_types medal, pilot_rank_types rank, char *text_buffer, char *destination_text)
{

	char
		*text_ptr,
		*temp_text;

	int
		flag,
		loop;

	temp_text = text_buffer;
	text_ptr = destination_text;

	if (text_buffer == NULL)
	{

		*text_ptr = '\0';

		return;
	}

	//
	// initialise substitution string
	//

	for (loop = 0; loop < sizeof (briefing_substitutions) / sizeof (briefing_substitution_type); loop ++)
	{

		briefing_substitutions [loop].position_ptr = strstr (text_buffer, briefing_substitutions [loop].string);
	}

	//
	//
	//

	while (*temp_text != '\0')
	{

		int
			loop;

		//
		// check for substitution string
		//

		flag = FALSE;

		for (loop = 0; loop < sizeof (briefing_substitutions) / sizeof (briefing_substitution_type); loop ++)
		{
	
			if (briefing_substitutions [loop].position_ptr == temp_text)
			{

				briefing_substitutions [loop].function (task, medal, rank, &text_ptr);

				temp_text += strlen (briefing_substitutions [loop].string);

				flag = TRUE;

				break;
			}
		}

		if (!flag)
		{

			//
			// copy string across
			//

			*text_ptr = *temp_text;
	
			text_ptr ++;

			temp_text ++;
		}
	}

	*text_ptr = '\0';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void briefing_add_position (entity *en, medal_types medal, pilot_rank_types rank, char **text)
{

	char
		buffer [32];

	vec3d
		*pos;

	switch (get_local_entity_type (en))
	{

		case ENTITY_TYPE_TASK:
		{
		
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_STOP_POSITION);
		
	  		break;
		}

		default:
		{
		
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

			break;
		}
	}
		
	sprintf (buffer, "%d : %d", (int) pos->x, (int) pos->z);

	strcpy (*text, buffer);

	*text += strlen (buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void briefing_add_sector (entity *en, medal_types medal, pilot_rank_types rank, char **text)
{

	char
		buffer [32];

	vec3d
		*pos;

	int
		x,
		z;

	switch (get_local_entity_type (en))
	{

		case ENTITY_TYPE_TASK:
		{
		
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_STOP_POSITION);
		
	  		break;
		}

		default:
		{
		
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

			break;
		}
	}
		
	get_x_sector (x, pos->x);
	get_z_sector (z, pos->z);

	if (get_global_current_language () != LANGUAGE_POLISH)
	{
		sprintf (buffer, "%s [%03d:%03d]", get_trans ("Sector"), x, z);
	}
	else
	{
		sprintf (buffer, " [%03d:%03d]", x, z);
	}
	

	strcpy (*text, buffer);

	*text += strlen (buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void briefing_add_keysite (entity *en, medal_types medal, pilot_rank_types rank, char **text)
{

	entity
		*keysite;

	if (en)
	{

		switch (get_local_entity_type (en))
		{

			case ENTITY_TYPE_TASK:
			{
		
				keysite = get_local_entity_parent (en, LIST_TYPE_TASK_DEPENDENT);
		
				if (keysite)
				{
		
					if (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE)
					{
					
						strcpy (*text, get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));
						*text += strlen (get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));
					}
					else
					{
					
						debug_fatal ("BRIEFING: Trying to build briefing text for %s (%d) mission but object isn't a keysite %s (%d)",
										get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
										get_local_entity_string (keysite, STRING_TYPE_FULL_NAME), get_local_entity_index (keysite));
					}
				}

				break;
			}

			case ENTITY_TYPE_KEYSITE:
			{
		
				strcpy (*text, get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME));
				*text += strlen (get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME));

				break;

			}
			default:
			{
				
				debug_fatal ("BRIEFING: Trying to build briefing text for %s (%d) unknown type",
								get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void briefing_add_keysite_type (entity *keysite, medal_types medal, pilot_rank_types rank, char **text)
{

	if (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE)
	{
	
		strcpy (*text, get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));
		*text += strlen (get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));
	}
	else
	{
	
		debug_fatal ("BRIEFING: Trying to build objective briefing but object isn't a keysite %s (%d)",
						get_local_entity_string (keysite, STRING_TYPE_FULL_NAME), get_local_entity_index (keysite));
	}
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void briefing_add_group (entity *task, medal_types medal, pilot_rank_types rank, char **text)
{

	entity
		*group,
		*company;

	if (task)
	{

		group = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

		if (group)
		{

			if (get_local_entity_type (group) == ENTITY_TYPE_GROUP)
			{

				company = get_local_entity_parent (group, LIST_TYPE_DIVISION);

				ASSERT (company);

				strcpy (*text, get_local_entity_string (group, STRING_TYPE_DIVISION_NAME));
				*text += strlen (get_local_entity_string (group, STRING_TYPE_DIVISION_NAME));

				strcpy (*text, ", ");
				*text += strlen (", ");
			
				strcat (*text, get_local_entity_string (company, STRING_TYPE_DIVISION_NAME));
				*text += strlen (get_local_entity_string (company, STRING_TYPE_DIVISION_NAME));
			}
			else
			{
			
				debug_fatal ("BRIEFING: Trying to build briefing text for %s (%d) mission but object isn't a group %s (%d)",
								get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_index (task),
								get_local_entity_string (group, STRING_TYPE_FULL_NAME), get_local_entity_index (group));
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void briefing_add_target_type (entity *task, medal_types medal, pilot_rank_types rank, char **text)
{

	entity
		*target;

	if (task)
	{

		target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

		if (target)
		{

			switch (get_local_entity_type (target))
			{

				default:
				{
	
					strcpy (*text, get_local_entity_string (target, STRING_TYPE_FULL_NAME));
					*text += strlen (get_local_entity_string (target, STRING_TYPE_FULL_NAME));
	
					break;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void briefing_add_medal (entity *task, medal_types medal, pilot_rank_types rank, char **text)
{

	if (get_local_entity_int_value (task, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
	{

		strcpy (*text, get_trans (us_medal_type_names [medal]));

		*text += strlen (get_trans (us_medal_type_names [medal]));
	}
	else
	{

		strcpy (*text, get_trans (cis_medal_type_names [medal]));

		*text += strlen (get_trans (cis_medal_type_names [medal]));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void briefing_add_rank (entity *task, medal_types medal, pilot_rank_types rank, char **text)
{

	strcpy (*text, get_trans (rank_type_names [rank]));

	*text += strlen (get_trans (rank_type_names [rank]));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

task_briefing_type *get_task_briefing_data (entity_sub_types task_type)
{

	if (task_briefing_database [task_type].task_type == task_type)
	{

		return &task_briefing_database [task_type];
	}
	else
	{

		return NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extra_briefing_type *get_extra_briefing_data (extra_briefing_types type, int sub_type)
{

	extra_briefing_type
		*this_item;

	this_item = extra_briefing_database;

	while (this_item)
	{

		if (this_item->type == type)
		{

			switch (this_item->type)
			{

				case EXTRA_BRIEFING_MEDAL:
				{
	
					if (this_item->sub_type & (1 << sub_type))
					{
			
						return this_item;
					}

					break;
				}

				default:
				{

					if (this_item->sub_type == sub_type)
					{
		
						return this_item;
					}
				}
			}
		}

		this_item = this_item->next;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_briefing_text (entity *task, char *text1, char *text2, char *text3)
{

	int
		remainder,
		text1_choice,
		text2_choice,
		text3_choice;

	task_briefing_type
		*task_briefing;

	memset (text1, 0, sizeof (text1));
	memset (text2, 0, sizeof (text2));
	memset (text3, 0, sizeof (text3));

	task_briefing = get_task_briefing_data (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE));

	if (task_briefing)
	{

		// text 1 choice
	
		// check if any texts
		if (task_briefing->briefing_text1 [0])
		{
		
			text1_choice = get_local_entity_index (task) % task_briefing->briefing_text1_count;
			
			remainder = get_local_entity_index (task) / task_briefing->briefing_text1_count;
		
			build_substitution_info (task, NUM_MEDAL_TYPES, NUM_PILOT_RANKS, task_briefing->briefing_text1 [text1_choice], text1);
		}
	
		// text 2 choice
	
		// check if any texts
		if (task_briefing->briefing_text2 [0])
		{
		
			text2_choice = (remainder + get_local_entity_index (task)) % task_briefing->briefing_text2_count;
		
			build_substitution_info (task, NUM_MEDAL_TYPES, NUM_PILOT_RANKS, task_briefing->briefing_text2 [text2_choice], text2);
		}
	
		// text 3 choice
	
		// check if any texts
		if (task_briefing->briefing_text3 [0])
		{
		
			remainder += get_local_entity_index (task) / task_briefing->briefing_text3_count;
		
			text3_choice = (remainder + get_local_entity_index (task)) % task_briefing->briefing_text3_count;
		
			build_substitution_info (task, NUM_MEDAL_TYPES, NUM_PILOT_RANKS, task_briefing->briefing_text3 [text3_choice], text3);
		}
	
		#if DEBUG_MODULE
	
		debug_log ("BRIEFING: using %d, %d, %d for text choice", text1_choice, text2_choice, text3_choice);
	
		#endif

		return TRUE;
	}

	debug_log ("BRIEFING: WARNING: no briefing for mission %s", get_local_entity_string (task, STRING_TYPE_FULL_NAME));

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_debriefing_text (entity *task, char **debrief, char **ff_debrief)
{

	int
		text_choice;

	task_briefing_type
		*task_debriefing,
		*ff_task_debriefing;

	ASSERT (task); 

	*debrief = NULL;

	*ff_debrief = NULL;

	ff_task_debriefing = NULL;

	task_debriefing = get_task_briefing_data (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE));

	// friendly fire debriefing text held is TASK_NOTHING
	if (get_task_friendly_fire_incidents (task))
	{

		ff_task_debriefing = get_task_briefing_data (ENTITY_SUB_TYPE_TASK_NOTHING);
	}

	if (task_debriefing)
	{

		switch (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED))
		{

			case TASK_COMPLETED_SUCCESS:
			{
	
				text_choice = get_local_entity_index (task) % task_debriefing->debriefing_text_success_count;
				*debrief = task_debriefing->debriefing_text_success [text_choice];

				if (ff_task_debriefing)
				{

					text_choice = get_local_entity_index (task) % ff_task_debriefing->debriefing_text_success_count;
					*ff_debrief = ff_task_debriefing->debriefing_text_success [text_choice];
				}

				break;
			}

			case TASK_COMPLETED_PARTIAL:
			{
	
				text_choice = get_local_entity_index (task) % task_debriefing->debriefing_text_partial_count;
				*debrief = task_debriefing->debriefing_text_partial [text_choice];

				if (ff_task_debriefing)
				{

					text_choice = get_local_entity_index (task) % ff_task_debriefing->debriefing_text_partial_count;
					*ff_debrief = ff_task_debriefing->debriefing_text_partial [text_choice];
				}

				break;
			}

			case TASK_COMPLETED_FAILURE:
			{
	
				text_choice = get_local_entity_index (task) % task_debriefing->debriefing_text_failure_count;
				*debrief = task_debriefing->debriefing_text_failure [text_choice];

				if (ff_task_debriefing)
				{

					text_choice = get_local_entity_index (task) % ff_task_debriefing->debriefing_text_failure_count;
					*ff_debrief = ff_task_debriefing->debriefing_text_failure [text_choice];
				}

				break;
			}

			case TASK_INCOMPLETE:
			{

				debug_fatal ("BRIEFING: Doing debrief for incomplete task %s (%d)", get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_index (task));

				break;
			}
		}

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_medal_briefing_text (entity *task, int medal_type, char *medal_text)
{

	int
		text_choice;

	extra_briefing_type
		*this_medal;

	this_medal = get_extra_briefing_data (EXTRA_BRIEFING_MEDAL, medal_type);

	if (this_medal)
	{

		ASSERT (this_medal->text_count > 0);
	
		text_choice = get_local_entity_index (task) % this_medal->text_count;
	
		build_substitution_info (task, medal_type, NUM_PILOT_RANKS, this_medal->briefing_text [text_choice], medal_text);

		return TRUE;
	}
	else
	{

		debug_log ("BRIEFING: WARNING: no medal text for %s", medal_type_names [medal_type]);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_promotion_briefing_text (entity *task, int rank_type, char *rank_text)
{

	int
		text_choice;

	extra_briefing_type
		*this_rank;

	// sub_type == 0 because there aren't different texts per promotion
	this_rank = get_extra_briefing_data (EXTRA_BRIEFING_PROMOTION, 0);

	if (this_rank)
	{

		ASSERT (this_rank->text_count > 0);
	
		text_choice = get_local_entity_index (task) % this_rank->text_count;
	
		build_substitution_info (task, NUM_MEDAL_TYPES, rank_type, this_rank->briefing_text [text_choice], rank_text);

		return TRUE;
	}
	else
	{

		debug_log ("BRIEFING: WARNING: no rank text for %s", pilot_rank_names [rank_type]);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_objective_briefing_text (entity *keysite, int objective_type, char *objective_text)
{

	int
		text_choice;

	extra_briefing_type
		*this_objective;

	this_objective = get_extra_briefing_data (EXTRA_BRIEFING_OBJECTIVES, objective_type);

	if (this_objective)
	{

		ASSERT (this_objective->text_count > 0);
	
		text_choice = get_local_entity_index (keysite) % this_objective->text_count;
	
		build_substitution_info (keysite, NUM_MEDAL_TYPES, NUM_PILOT_RANKS, this_objective->briefing_text [text_choice], objective_text);

		return TRUE;
	}
	else
	{

		debug_log ("BRIEFING: WARNING: no objective text for %s", entity_sub_type_keysite_names [objective_type]);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
