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

struct OBJECT_3D_INFORMATION
{

	char
		*name;

	float
		maximum_distance;
};

typedef struct OBJECT_3D_INFORMATION object_3d_information;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TEXTURE_ANIMATION_INFORMATION
{

	int
		number_of_frames,
		current_frame,
		*texture_indices;
};

typedef struct TEXTURE_ANIMATION_INFORMATION texture_animation_information;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern object_3d_information *object_3d_information_database;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_3d_objects_info ( const char *directory );

extern void deinitialise_3d_objects_info ( void );

extern int get_object_3d_index_from_name ( const char *name );

#ifndef OGRE_EE
extern int get_object_3d_sub_index_from_name ( const char *name );

extern int get_object_3d_camoflage_index_from_name ( const char *name );

extern int get_object_3d_camera_index_from_name ( const char *name );
#endif

extern int get_object_3d_texture_animation_index_from_name ( const char *name );

extern int get_object_3d_displacement_animation_index_from_name ( const char *name );

#ifndef OGRE_EE
extern object_3d_instance *construct_3d_object_by_name ( const char *name );
#endif

extern void set_object_3d_texture_camoflage_by_name ( const char *name );

extern int add_new_animation ( const char *animation_name );

// Casm 18DEC15 Skin
extern void skin_init ( struct OBJECT_3D_SCENE_DATABASE_ENTRY* scene );
extern void skin_random ( object_3d_instance* scene );
extern void skin_next ( object_3d_instance* scene );

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern object_3d_information
	*object_3d_information_database;

extern char
	**object_3d_enumeration_names,
	**object_3d_sub_object_names,
	**object_3d_camoflage_set_names,
	**object_3d_camera_names,
	**texture_animation_names,
	**displacement_animation_names;

extern texture_animation_information
	*texture_animations,
	*displacement_animations;

extern int
	object_3d_number_of_scene_names,
	object_3d_number_of_sub_object_names,
	object_3d_number_of_camoflage_set_names,
	object_3d_number_of_camera_names,
	number_of_texture_animations,
	number_of_displacement_animations;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#else
extern char
	**object_3d_enumeration_names,
	**texture_animation_names;
extern texture_animation_information
	*texture_animations;
extern int
	number_of_texture_animations;
#endif
