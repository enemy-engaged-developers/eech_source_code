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

char
	*user_defined_events_strings [] =
	{
	
		"COLLECTIVE_UP",
		"COLLECTIVE_DOWN",
		"CYCLIC_LEFT",
		"CYCLIC_RIGHT",
		"CYCLIC_UP",
		"CYCLIC_DOWN",
		"PEDAL_LEFT",
		"PEDAL_RIGHT",
		"FIRE_WEAPON",
		"MAX_USER_DEFINED_EVENTS"
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

user_defined_key_type
	*user_defined_keys;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_user_defined_file (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_user_defined_events (void)
{

	user_defined_events
		ev;

	user_defined_key_type
		*new_user_defined_key;

	char
		enum_event [100],
		key [10],
		modifier [10];

	FILE
		*file_ptr;

	file_ptr = fopen ("userdef.key", "r");

	if (!file_ptr)
	{

		return;
	}

	while (fscanf (file_ptr, "%s %s %s", &enum_event, &key, &modifier) != EOF)
	{

		new_user_defined_key = (user_defined_key_type *) malloc_heap_mem (sizeof (user_defined_key_type));

		ev = COLLECTIVE_UP;

		while (ev != NUM_USER_DEFINED_EVENTS)
		{

			if (stricmp (user_defined_events_strings [ev], enum_event) == 0)
			{
		
				new_user_defined_key->ev = ev;
		
				new_user_defined_key->dik_code = (int) key [0];

				new_user_defined_key->modifier_dik_code = (int) modifier [0];

				new_user_defined_key->next = user_defined_keys;

				user_defined_keys = new_user_defined_key;
		
				debug_log ("USER DEFINED %s=%s %s", enum_event, key, modifier);

				break;
			}

			ev ++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_user_defined_flight_events (void)
{

	user_defined_key_type
		*current_key;

	current_key = user_defined_keys;

	while (current_key)
	{

		switch (current_key->ev)
		{

			////////////////////////////////////////////////////////////////

			case COLLECTIVE_UP:
			{

				set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, collective_forward);

				break;
			}

			case COLLECTIVE_DOWN:
			{

				set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, collective_backward);

				break;
			}

			////////////////////////////////////////////////////////////////

			case CYCLIC_LEFT:
			{

				set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, cyclic_left);

				break;
			}

			case CYCLIC_RIGHT:
			{
				
				set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, cyclic_right);

				break;
			}

			case CYCLIC_UP:
			{

				set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, cyclic_forward);

				break;
			}

			case CYCLIC_DOWN:
			{

				set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, cyclic_backward);

				break;
			}

			////////////////////////////////////////////////////////////////

			case PEDAL_LEFT:
			{

				set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, pedal_left);

				break;
			}

			case PEDAL_RIGHT:
			{

				set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, pedal_right);

				break;
			}

			////////////////////////////////////////////////////////////////

			case FIRE_WEAPON:
			{

				//set_event (current_key->dik_code, current_key->modifier_dik_code, KEY_STATE_EITHER, fire_cannon_shell_event);

				break;
			}

			////////////////////////////////////////////////////////////////

			default:
			{

				debug_log ("USER DEFINED KEY : ERROR : Unknown key definition");
			}
		}

		current_key = current_key->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_user_defined_file (void)
{

	FILE
		*file_ptr;

	file_ptr = fopen ("userdef.key", "w");

	if (file_ptr)
	{

		fprintf (file_ptr, "COLLECTIVE_UP %c %c\n", DIK_Q, MODIFIER_NONE);
		fprintf (file_ptr, "COLLECTIVE_DOWN %c %c\n", DIK_A, MODIFIER_NONE);

		fprintf (file_ptr, "CYCLIC_LEFT %c %c\n", DIK_LEFT, MODIFIER_NONE);
		fprintf (file_ptr, "CYCLIC_RIGHT %c %c\n", DIK_RIGHT, MODIFIER_NONE);
		fprintf (file_ptr, "CYCLIC_FORWARD %c %c\n", DIK_UP, MODIFIER_NONE);
		fprintf (file_ptr, "CYCLIC_BACKWARD %c %c\n", DIK_DOWN, MODIFIER_NONE);
		
		fprintf (file_ptr, "PEDAL_LEFT %c %c\n", DIK_Z, MODIFIER_NONE);
		fprintf (file_ptr, "PEDAL_RIGHT %c %c\n", DIK_X, MODIFIER_NONE);
		
		fprintf (file_ptr, "FIRE_WEAPON %c %c\n", DIK_SPACE, MODIFIER_NONE);

		fclose (file_ptr);
	}
	else
	{

		debug_fatal ("USER DEFINED KEY : ERROR : Can't create file");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

