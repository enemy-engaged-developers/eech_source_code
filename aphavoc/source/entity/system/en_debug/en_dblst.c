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

static void debug_log_entity_list (entity *parent, list_types type, int indent_level)
{
	char
		*prefix,
		s1[400],
		s2[400];

	int
		length,
		child;

	entity
		*en;

	ASSERT (parent);

	length = indent_level * 3;

	prefix = malloc_heap_mem (length + 1);

	memset (prefix, ' ', length);

	prefix [length] = '\0';

	child = 1;

	debug_log ("%s========================================", prefix);
	debug_log ("%sPARENT/CHILD LIST (%s)", prefix, get_list_type_name (type));
	debug_log ("%s----------------------------------------", prefix);

	en = get_local_entity_first_child (parent, type);

	debug_log
	(
		"%sParent   : %-25.25s:                [%4d] -> [%4d] first child",
		prefix,
		get_local_entity_type_name (parent),
		get_local_entity_safe_index (parent),
		get_local_entity_safe_index (en)
	);

	while (en)
	{
		sprintf
		(
			s1,
			"%sChild %3d: %-25.25s: pred [%4d] <- [%4d] -> [%4d] succ: parent [%4d]",
			prefix,
			child,
			get_local_entity_type_name (en),
			get_local_entity_safe_index (get_local_entity_child_pred (en, type)),
			get_local_entity_safe_index (en),
			get_local_entity_safe_index (get_local_entity_child_succ (en, type)),
			get_local_entity_safe_index (get_local_entity_parent (en, type))
		);

		switch (get_local_entity_type (en))
		{
			////////////////////////////////////////
			case ENTITY_TYPE_WAYPOINT:
			////////////////////////////////////////
			{
				sprintf (s2, ": tag [%c]", get_local_entity_char_value (en, CHAR_TYPE_TAG));

				strcat (s1, s2);

				break;
			}
		}

		debug_log (s1);

		en = get_local_entity_child_succ (en, type);

		child++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void debug_log_entity_group (entity *grp, int indent_level)
{
	ASSERT (grp);

	ASSERT (get_local_entity_type (grp) == ENTITY_TYPE_GROUP);

	debug_log_entity_list (grp, LIST_TYPE_MEMBER, indent_level);

	debug_log_entity_list (grp, LIST_TYPE_WAYPOINT, indent_level);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void debug_log_entity_force (entity *frc)
{
	entity
		*grp,
		*keysite;

	int
		indent;

	ASSERT (frc);

	ASSERT (get_local_entity_type (frc) == ENTITY_TYPE_FORCE);

	keysite = get_local_entity_first_child (frc, LIST_TYPE_KEYSITE_FORCE);

	while (keysite)
	{
		debug_log_entity_list (keysite, LIST_TYPE_KEYSITE_GROUP, 0);

		indent = 1;

		grp = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);

		while (grp)
		{
			debug_log_entity_group (grp, indent++);

			grp = get_local_entity_child_succ (grp, LIST_TYPE_KEYSITE_GROUP);
		}

		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_log_entity_session (entity *ssn, char *title)
{
	entity
		*frc;

	ASSERT (ssn);

	ASSERT (get_local_entity_type (ssn) == ENTITY_TYPE_SESSION);

	debug_log ("********************************************************************************");
	debug_log ("********************************************************************************");
	debug_log ("***");
	debug_log ("*** %s", title);
	debug_log ("***");
	debug_log ("********************************************************************************");
	debug_log ("********************************************************************************");

	//
	// force, groups, etc.
	//

	debug_log_entity_list (ssn, LIST_TYPE_FORCE, 0);

	frc = get_local_entity_first_child (ssn, LIST_TYPE_FORCE);

	while (frc)
	{
		debug_log_entity_force (frc);

		frc = get_local_entity_child_succ (frc, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
