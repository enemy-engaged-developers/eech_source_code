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

extern void initialise_scene_quick_sub_object_search ( int scene_index );

extern void initialise_scene_visible_sub_objects ( int scene_index );

extern void initialise_scene_bounding_sub_objects ( int scene_index );

#ifndef OGRE_EE
extern void reset_sub_object_search_statistics ( void );

extern void report_sub_object_search_statistics ( void );
#endif

extern enum SUB_OBJECT_SEARCH_RESULT_TYPES find_object_3d_sub_object ( struct OBJECT_3D_SUB_OBJECT_SEARCH_DATA *search );

extern enum SUB_OBJECT_SEARCH_RESULT_TYPES find_object_3d_sub_object_from_sub_object ( struct OBJECT_3D_SUB_OBJECT_SEARCH_DATA *parent_search, struct OBJECT_3D_SUB_OBJECT_SEARCH_DATA *search );

// Returns the pointer to a named sub instance of an object, or gives a fatal warning if it doesn't exist
#ifndef OGRE_EE
extern object_3d_sub_instance* find_sub_object(object_3d_instance* parent_object, unsigned sub_obj_id);
#else
extern struct OgreGameObjectSceneElement* find_sub_object(object_3d_instance* parent_object, unsigned sub_obj_id);
#endif


#ifndef OGRE_EE
extern int find_object_3d_sub_objects (object_3d_instance *search_object, const object_3d_sub_object_search_batch *search, int number_of_sub_objects);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
