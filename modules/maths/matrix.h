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

// Reminder : Rotations (TG - 3/12/99)
//
// To transform from World Space to Object Space use multiply_transpose_matrix3x3_matrix3x3 
// To transform from Object Space to World Space use multiply_matrix3x3_matrix3x3
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef float matrix3x3[3][3];

typedef float matrix4x4[4][4];

typedef double double_matrix3x3[3][3];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define get_heading_from_attitude_matrix(ATTITUDE) (atan2 ((ATTITUDE)[2][0], (ATTITUDE)[2][2]))

#define get_pitch_from_attitude_matrix(ATTITUDE) (asin ((ATTITUDE)[2][1]))

#define get_roll_from_attitude_matrix(ATTITUDE) (atan2 (-(ATTITUDE)[0][1], (ATTITUDE)[1][1]))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// float library
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void get_3d_transformation_matrix ( matrix3x3 m, float heading, float pitch, float roll );

extern void get_3d_transformation_matrix_fast ( matrix3x3 m, float heading, float pitch, float roll );

extern void get_3d_transformation_heading_pitch_matrix ( matrix3x3 m, float heading, float pitch );

extern void get_3d_transformation_heading_matrix ( matrix3x3 m, float heading );

extern void get_arbitrary_rotation_matrix ( matrix3x3 m, const vec3d *v, float angle );

extern void get_4d_transformation_matrix ( matrix4x4 m, float heading, float pitch, float roll, const vec3d *position );

extern void get_4d_projection_matrix ( matrix4x4 m, float near_plane, float far_plane, float fov_width, float fov_height );

extern void get_reflection_matrix ( matrix3x3 m, const vec3d *v );

extern void multiply_matrix3x3_vec3d ( vec3d *result, const matrix3x3 m, const vec3d *v );

extern void multiply_transpose_matrix3x3_vec3d ( vec3d *result, const matrix3x3 m, const vec3d *v );

extern void multiply_matrix3x3_matrix3x3 ( matrix3x3 result, const matrix3x3 a, const matrix3x3 b );

extern void multiply_transpose_matrix3x3_matrix3x3 ( matrix3x3 result, const matrix3x3 a, const matrix3x3 b );

extern void multiply_matrix3x3_transpose_matrix3x3 ( matrix3x3 result, const matrix3x3 a, const matrix3x3 b );

extern void multiply_matrix4x4_matrix4x4 ( matrix4x4 result, const matrix4x4 a, const matrix4x4 b );

extern void multiply_matrix4x4_vec4d ( vec4d *result, const matrix4x4 m, const vec4d *v );

extern void multiply_matrix3x3_matrix3x3_2d (matrix3x3 result, const matrix3x3 a, const matrix3x3 b);

extern void get_identity_matrix3x3 (matrix3x3 m);

extern void get_inverse_matrix (matrix3x3 result, const matrix3x3 matrix);

extern void get_matrix3x3_from_unit_vec3d (matrix3x3 result, const vec3d *v);

extern void get_matrix3x3_from_unit_vec3d_and_roll (matrix3x3 result, const vec3d *v, float roll);

extern void get_3d_transformation_matrix_from_face_normal_and_heading (matrix3x3 result, const vec3d *normal, float heading);

extern int check_identity_matrix3x3 (const matrix3x3 m);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// double library
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define get_heading_from_attitude_double_matrix(ATTITUDE) (atan2 ((ATTITUDE)[2][0], (ATTITUDE)[2][2]))

#define get_pitch_from_attitude_double_matrix(ATTITUDE) (asin ((ATTITUDE)[2][1]))

#define get_roll_from_attitude_double_matrix(ATTITUDE) (atan2 (-(ATTITUDE)[0][1], (ATTITUDE)[1][1]))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void multiply_double_matrix3x3_double_vec3d ( double_vec3d *result, const double_matrix3x3 m, const double_vec3d *v );

extern void multiply_transpose_double_matrix3x3_double_vec3d ( double_vec3d *result, const double_matrix3x3 m, const double_vec3d *v );

extern void multiply_transpose_matrix3x3_double_vec3d ( double_vec3d *result, const matrix3x3 m, const double_vec3d *v );

extern void multiply_double_matrix3x3_double_matrix3x3 ( double_matrix3x3 result, const double_matrix3x3 a, const double_matrix3x3 b );

extern void multiply_transpose_double_matrix3x3_double_matrix3x3 ( double_matrix3x3 result, const double_matrix3x3 a, const double_matrix3x3 b );

extern void multiply_double_matrix3x3_transpose_double_matrix3x3 ( double_matrix3x3 result, const double_matrix3x3 a, const double_matrix3x3 b );

extern void get_arbitrary_rotation_double_matrix ( double_matrix3x3 m, const double_vec3d *v, float angle );

extern void get_identity_double_matrix3x3 (double_matrix3x3 m);

extern void get_double_matrix3x3_from_unit_double_vec3d (double_matrix3x3 result, const double_vec3d *v);

extern void get_3d_transformation_double_matrix ( double_matrix3x3 m, double heading, double pitch, double roll );

extern void get_double_matrix3x3_from_unit_double_vec3d_and_roll (double_matrix3x3 result, const double_vec3d *v, double roll);

extern void get_inverse_double_matrix (double_matrix3x3 result, const double_matrix3x3 matrix);

extern void get_3d_transformation_double_matrix_from_face_normal_and_heading (double_matrix3x3 result, const double_vec3d *normal, double heading);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMBINATION LIBRARY
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void get_matrix3x3_from_unit_double_vec3d_and_roll (matrix3x3 result, const double_vec3d *v, double roll);

extern void multiply_transpose_double_matrix3x3_vec3d ( vec3d *result, const double_matrix3x3 m, const vec3d *v );

extern void multiply_double_matrix3x3_vec3d ( vec3d *result, const double_matrix3x3 m, const vec3d *v );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
