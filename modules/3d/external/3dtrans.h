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

#define	MAX_POINTS		16384

#define	INTEGER_METRES_FACTOR				(0x47400000)

#define	INTEGER_FLOAT_FACTOR					(0x4b40005a)

#define	INTEGER_FLOAT_8_FACTOR				(0x4cc00000)

#define	INTEGER_TEXTURE_FACTOR				(0x4cc00000)

#define	INTEGER_BINARY_INTENSITY_FACTOR	(0x40400000)

#define	INTEGER_WHOLE_INTENSITY_FACTOR	(0x47c00000)

#define	FLOAT_METRES_FACTOR					(32768+16384)

#define	FLOAT_FLOAT_FACTOR					(8388608+4194394)

#define	FLOAT_FLOAT_8_FACTOR					(100663296.0)

#define	FLOAT_TEXTURE_FACTOR					(100663296.0)

#define	FLOAT_BINARY_INTENSITY_FACTOR		(3)

#define	FLOAT_WHOLE_INTENSITY_FACTOR		(65536+32768)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern matrix3x3
	rotation_3d,
	scaled_rotation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern vertex
	transformed_3d_points[];

extern object_3d_transformed_point_normal
	transformed_3d_normals[];

extern float
	transformed_3d_normal_factors[];

extern unsigned char
	transformed_3d_normal_visibilities[];

extern unsigned char
	transformed_3d_point_outcodes[],
	transformed_3d_points_needed[];

extern object_transformed_3d_point
	transformed_3d_3d_points[];

extern object_transformed_2d_point
	transformed_3d_2d_points[];

extern float
	float_factor,
	binary_intensity_float_factor,
	whole_intensity_float_factor;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_3d_transformation_arrays ( void );

extern void initialise_3d_transformation_stats ( void );

extern void reset_3d_transformation_stats ( void );

extern void illuminate_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base );

extern void illuminate_object_point_normals ( object_3d_heading_pitch_normal *normals, int number_of_normals, light_3d_source *lights, int points_base );

extern void calculate_object_normal_factors ( object_3d_point_normal *normals, int number_of_normals, vec3d *camera, struct OBJECT_3D_BOUNDS *bounds, int points_base );

extern void transform_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base );

extern void transform_flat_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base );

extern void transform_unclipped_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base );

extern void transform_unclipped_flat_3d_object ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction, int points_base );

extern void initialise_transform_3d_object_points ( object_3d *object, vec3d *pos, light_3d_source *lights, vec3d *camera_direction );

extern void transform_3d_object_points ( int number_of_points );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
