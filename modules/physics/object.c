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

#include "physics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	draw_bounding_box;

object
	*object_list_head = NULL;

static double
	world_energy = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_object (object *obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_object_system (void)
{

	debug_watch ("World Energy 				= %f", MT_DOUBLE, &world_energy);

	draw_bounding_box = FALSE;

	deinitialise_object_system ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_object_system (void)
{

	object
		*destroy_object = nullptr;

	while (object_list_head)
	{

		destroy_object = object_list_head;

		object_list_head = object_list_head->next;

		if (destroy_object->name)
		{

			free_mem (destroy_object->name);
		}

		if (destroy_object->rigid_body)
		{

			free_mem (destroy_object->rigid_body);
		}

		destruct_3d_object (destroy_object->inst3d);

		free_mem (destroy_object);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object *create_object (char *name, int object_number, double_vec3d *position)
{

	object
		*new_object = nullptr;

	new_object = (object *) malloc_heap_mem (sizeof (object));

	memset (new_object, 0, sizeof (object));

	// name

	new_object->name = (char *) malloc_heap_mem (sizeof (char) * (strlen (name) + 2));

	sprintf (new_object->name, "%s", name);

	// object number

	new_object->scaling.x = 1.0;
	new_object->scaling.y = 1.0;
	new_object->scaling.z = 1.0;

	new_object->object_number = object_number;

	// position

	new_object->position = *position;

	// attitude

	get_identity_double_matrix3x3 (new_object->attitude);

	// instance 3d

	new_object->inst3d = construct_3d_object (object_number);

	// link into list

	new_object->next = object_list_head;

	object_list_head = new_object;

	camera_object = new_object;

	return new_object;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_objects (void)
{

	object
		*current_object = nullptr;

	current_object = object_list_head;

	while (current_object)
	{

		if (current_object->rigid_body)
		{
	
			memcpy (current_object->attitude, current_object->rigid_body->attitude, sizeof (double_matrix3x3));
	
			memcpy (&current_object->position, &current_object->rigid_body->position_cm [0], sizeof (double_vec3d));
		}

		current_object = current_object->next;
	}

	world_energy = get_total_rigid_body_energies () + get_total_connection_energies ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_objects (void)
{

	object
		*current_object = nullptr;

	current_object = object_list_head;

	while (current_object)
	{

		draw_object (current_object);

		current_object = current_object->next;
	}

	draw_arrows ();

	draw_lines ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_object (object *current_object)
{

	current_object->inst3d->vp.position.x = current_object->position.x;
	current_object->inst3d->vp.position.y = current_object->position.y;
	current_object->inst3d->vp.position.z = current_object->position.z;

	//debug_log ("OBJECT: position [%f, %f, %f]", current_object->position.x, current_object->position.y, current_object->position.z);

	if (current_object->rigid_body)
	{
	
		current_object->inst3d->relative_scale.x = current_object->rigid_body->scaling.x;
		current_object->inst3d->relative_scale.y = current_object->rigid_body->scaling.y;
		current_object->inst3d->relative_scale.z = current_object->rigid_body->scaling.z;
	}

	//memcpy (current_object->inst3d->vp.attitude, current_object->attitude, sizeof (double_matrix3x3));

	current_object->inst3d->vp.attitude [0][0] = current_object->attitude [0][0];
	current_object->inst3d->vp.attitude [0][1] = current_object->attitude [0][1];
	current_object->inst3d->vp.attitude [0][2] = current_object->attitude [0][2];

	current_object->inst3d->vp.attitude [1][0] = current_object->attitude [1][0];
	current_object->inst3d->vp.attitude [1][1] = current_object->attitude [1][1];
	current_object->inst3d->vp.attitude [1][2] = current_object->attitude [1][2];

	current_object->inst3d->vp.attitude [2][0] = current_object->attitude [2][0];
	current_object->inst3d->vp.attitude [2][1] = current_object->attitude [2][1];
	current_object->inst3d->vp.attitude [2][2] = current_object->attitude [2][2];

	insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, current_object->inst3d);

	if (current_object->rigid_body)
	{

		//draw_rigid_body_bounding_box (current_object->rigid_body);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
