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

struct DEBUG_3D_OBJECT
{
	viewpoint
		vp;

	object_3d_index_numbers
		object_3d_shape;

	float
		lifetime;

	vec3d
		relative_scale;

	struct DEBUG_3D_OBJECT
		*succ,
		*pred;
};

typedef struct DEBUG_3D_OBJECT debug_3d_object;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DEBUG_3D_LINE
{
	vec3d
		point1,
		point2;

	rgb_colour
		colour;

	float
		lifetime;

	struct DEBUG_3D_LINE
		*succ,
		*pred;
};

typedef struct DEBUG_3D_LINE debug_3d_line;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern debug_3d_object
	*debug_3d_object_list;

#define get_debug_3d_object_list() (debug_3d_object_list)

extern debug_3d_line
	*debug_3d_line_list;

#define get_debug_3d_line_list() (debug_3d_line_list)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_debug_3d_objects (void);

extern void deinitialise_debug_3d_objects (void);

extern debug_3d_object *create_debug_3d_object (viewpoint *vp, object_3d_index_numbers object_3d_shape, float lifetime, float relative_scale);

extern debug_3d_object *create_rotated_debug_3d_object (vec3d *position, float heading, float pitch, float roll, object_3d_index_numbers object_3d_shape, float lifetime, float relative_scale);

extern debug_3d_object *create_vectored_debug_3d_object (vec3d *position, vec3d *vector, object_3d_index_numbers object_3d_shape, float lifetime, float relative_scale);

extern void destroy_debug_3d_object (debug_3d_object *object);

extern void destroy_all_debug_3d_objects (void);

extern void draw_debug_3d_objects (viewpoint *vp, float visual_range);

extern void initialise_debug_3d_lines (void);

extern void deinitialise_debug_3d_lines (void);

extern debug_3d_line *create_debug_3d_line (vec3d *point1, vec3d *point2, rgb_colour colour, float lifetime);

extern void destroy_debug_3d_line (debug_3d_line *line);

extern void destroy_all_debug_3d_lines (void);

extern void draw_debug_3d_lines (viewpoint *vp, float visual_range);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
