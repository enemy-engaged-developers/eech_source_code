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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define REPORT_SUB_OBJECT_SEARCHES 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	sub_object_search_minimum_depth,
	sub_object_index_count[OBJECT_3D_SUB_OBJECT_LAST];

static object_3d_scene_sub_object_table_entry
	*current_sub_object_table = NULL;

static int
	number_of_sub_object_table_entries;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if REPORT_SUB_OBJECT_SEARCHES

static int
	sub_object_search_count,
	sub_object_internal_search_count;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int recurse_set_scene_sub_object_visibility ( object_3d_database_entry *sub_object );

static void recurse_initialise_sub_scene_bounding_box ( object_3d_database_entry *sub_object );

static void rotate_sub_scene_boundaries ( object_3d_bounds *results, object_3d_bounds *source );

static void count_named_sub_objects ( object_3d_database_entry *sub_scene );

static void populate_table_with_named_sub_objects ( object_3d_database_entry *object );

static void add_sub_object_index_to_table ( object_3d_sub_object_index_numbers index, object_3d_database_entry *object );

static int sub_scene_has_parent_scene ( object_3d_database_entry *parent, object_3d_database_entry *scene );

static object_3d_sub_instance *get_sub_object_from_sub_scene ( int scene_index, object_3d_database_entry *sub_scene, object_3d_instance *object );


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_scene_quick_sub_object_search ( int scene_index )
{

	object_3d_sub_object_index_numbers
		index;

	int
		count,
		total_sub_object_indices,
		number_of_unique_indices;

	//
	// Set the sub object index array to 0
	//

	for ( index = OBJECT_3D_INVALID_SUB_OBJECT_INDEX; index < OBJECT_3D_SUB_OBJECT_LAST; index++ )
	{

		sub_object_index_count[index] = 0;
	}

	//
	// Go through all the objects in the scene counting the sub object indices
	//

	for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_object_indices; count++ )
	{

		sub_object_index_count[ objects_3d_scene_database[scene_index].scene_sub_object_indices_array[count].sub_object_index ]++;
	}

	//
	// Recurse down through any sub objects
	//

	for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_objects; count++ )
	{

		count_named_sub_objects ( &objects_3d_scene_database[scene_index].sub_objects[count] );
	}

	//
	// Count up the total number of named sub objects
	//

	total_sub_object_indices = 0;

	number_of_unique_indices = 0;

	for ( index = OBJECT_3D_INVALID_SUB_OBJECT_INDEX; index < OBJECT_3D_SUB_OBJECT_LAST; index++ )
	{

		total_sub_object_indices += sub_object_index_count[index];

		if ( sub_object_index_count[index] )
		{

			number_of_unique_indices++;
		}
	}

	//
	// We should already have the total number, so check here
	//

	// If this asserts make sure you have recompiled this file with the latest 3dmodels.h file
	ASSERT ( total_sub_object_indices == objects_3d_scene_database[scene_index].total_number_of_sub_object_indices );

	if ( number_of_unique_indices )
	{

		object_3d_database_entry
			**sub_object_table_entries,
			**sub_object_entry_ptr;

		int
			table_index;

		number_of_sub_object_table_entries = number_of_unique_indices;

		//
		// Allocate memory for the table
		//

		current_sub_object_table = safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY ) * number_of_unique_indices );

		ASSERT ( current_sub_object_table );

		//
		// Record the data in the scene
		//

		objects_3d_scene_database[scene_index].sub_object_indices_table = current_sub_object_table;

		objects_3d_scene_database[scene_index].number_of_sub_object_table_entries = number_of_unique_indices;

		//
		// Allocate memory for the entries in the table
		//

		sub_object_table_entries = safe_malloc ( sizeof ( struct OBJECT_3D_DATABASE_ENTRY * ) * total_sub_object_indices );

		//
		// Go through initialising the table
		//

		sub_object_entry_ptr = sub_object_table_entries;

		table_index = 0;

		for ( index = OBJECT_3D_INVALID_SUB_OBJECT_INDEX; index < OBJECT_3D_SUB_OBJECT_LAST; index++ )
		{

			if ( sub_object_index_count[index] != 0 )
			{

				current_sub_object_table[table_index].sub_object_index = index;

				current_sub_object_table[table_index].number_of_sub_objects = 0;

				current_sub_object_table[table_index].sub_objects = sub_object_entry_ptr;

				sub_object_entry_ptr += sub_object_index_count[index];

				table_index++;
			}
		}

		//
		// Now go through populating the table with the first level named sub objects
		//

		for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_object_indices; count++ )
		{

			int
				offset;

			object_3d_database_entry
				*sub_object;

			index = objects_3d_scene_database[scene_index].scene_sub_object_indices_array[count].sub_object_index;

			offset = objects_3d_scene_database[scene_index].scene_sub_object_indices_array[count].object_index;

			sub_object = &objects_3d_scene_database[scene_index].sub_objects[offset];

			add_sub_object_index_to_table ( index, sub_object );
		}

		//
		// Now recurse the sub objects doing the same thing
		//

		for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_objects; count++ )
		{

			populate_table_with_named_sub_objects ( &objects_3d_scene_database[scene_index].sub_objects[count] );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_scene_visible_sub_objects ( int scene_index )
{

	int
		count;

	for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_objects; count++ )
	{

		recurse_set_scene_sub_object_visibility ( &objects_3d_scene_database[scene_index].sub_objects[count] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int recurse_set_scene_sub_object_visibility ( object_3d_database_entry *sub_object )
{

	int
		count,
		visibility;

	visibility = 0;

	for ( count = 0; count < sub_object->number_of_sub_objects; count++ )
	{

		visibility += recurse_set_scene_sub_object_visibility ( &sub_object->sub_objects[count] );
	}

	if ( ( visibility ) || ( sub_object->index != 0 ) )
	{

		sub_object->default_visibility = TRUE;
	}
	else
	{

		sub_object->default_visibility = FALSE;
	}

	return ( sub_object->default_visibility );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static vec3d
	scene_position;

static object_3d_bounds
	scene_bounds,
	scene_bounds2,
	rotated_bounds,
	rotated_bounds2;


static matrix3x3
	scene_rotation;

static int
	contributes_to_collision;

void initialise_scene_bounding_sub_objects ( int scene_index )
{

	int
		index,
		count;

	memset ( &scene_bounds, 0, sizeof ( object_3d_bounds ) );
	memset ( &scene_bounds2, 0, sizeof ( object_3d_bounds ) );

	index = objects_3d_scene_database[scene_index].index;

	scene_position.x = 0;
	scene_position.y = 0;
	scene_position.z = 0;

	get_3d_transformation_matrix ( scene_rotation, 0, 0, 0 );

	if ( index != 0 )
	{

		rotate_sub_scene_boundaries ( &rotated_bounds, &objects_3d_data[index].bounding_box );
		rotate_sub_scene_boundaries ( &rotated_bounds2, &objects_3d_data[index].bounding_box2 );

		scene_bounds.xmin = min ( scene_bounds.xmin, rotated_bounds.xmin );
		scene_bounds.ymin = min ( scene_bounds.ymin, rotated_bounds.ymin );
		scene_bounds.zmin = min ( scene_bounds.zmin, rotated_bounds.zmin );

		scene_bounds.xmax = max ( scene_bounds.xmax, rotated_bounds.xmax );
		scene_bounds.ymax = max ( scene_bounds.ymax, rotated_bounds.ymax );
		scene_bounds.zmax = max ( scene_bounds.zmax, rotated_bounds.zmax );

		scene_bounds2.xmin = min ( scene_bounds2.xmin, rotated_bounds2.xmin );
		scene_bounds2.ymin = min ( scene_bounds2.ymin, rotated_bounds2.ymin );
		scene_bounds2.zmin = min ( scene_bounds2.zmin, rotated_bounds2.zmin );

		scene_bounds2.xmax = max ( scene_bounds2.xmax, rotated_bounds2.xmax );
		scene_bounds2.ymax = max ( scene_bounds2.ymax, rotated_bounds2.ymax );
		scene_bounds2.zmax = max ( scene_bounds2.zmax, rotated_bounds2.zmax );
	}

	contributes_to_collision = TRUE;

	for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_objects; count++ )
	{

		recurse_initialise_sub_scene_bounding_box ( &objects_3d_scene_database[scene_index].sub_objects[count] );
	}

	objects_3d_scene_database[scene_index].bounding_box = scene_bounds;

	objects_3d_scene_database[scene_index].bounding_box2 = scene_bounds2;

	//
	// Calculate the radius based on the bounding_box values
	//

	{

		double
			dxmin,
			dxmax,
			dymin,
			dymax,
			dzmin,
			dzmax,
			radius;

		dxmax = ( (double) scene_bounds.xmax * (double) scene_bounds.xmax );
		dxmin = ( (double) scene_bounds.xmin * (double) scene_bounds.xmin );

		dymax = ( (double) scene_bounds.ymax * (double) scene_bounds.ymax );
		dymin = ( (double) scene_bounds.ymin * (double) scene_bounds.ymin );

		dzmax = ( (double) scene_bounds.zmax * (double) scene_bounds.zmax );
		dzmin = ( (double) scene_bounds.zmin * (double) scene_bounds.zmin );

		radius = 0;

		radius = max ( radius, ( dxmax + dymax + dzmax ) );
		radius = max ( radius, ( dxmax + dymax + dzmin ) );
		radius = max ( radius, ( dxmax + dymin + dzmax ) );
		radius = max ( radius, ( dxmax + dymin + dzmin ) );
		radius = max ( radius, ( dxmin + dymax + dzmax ) );
		radius = max ( radius, ( dxmin + dymax + dzmin ) );
		radius = max ( radius, ( dxmin + dymin + dzmax ) );
		radius = max ( radius, ( dxmin + dymin + dzmin ) );

		radius = sqrt ( radius );

		objects_3d_scene_database[scene_index].radius = radius;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recurse_initialise_sub_scene_bounding_box ( object_3d_database_entry *sub_object )
{

	vec3d
		old_scene_position,
		relative_position;

	matrix3x3
		matrix,
		new_rotation,
		old_scene_rotation;

	int
		old_contributes_to_collision,
		count;

	//
	// Save state variables
	//

	old_scene_position = scene_position;

	old_contributes_to_collision = contributes_to_collision;

	memcpy ( old_scene_rotation, scene_rotation, sizeof ( matrix3x3 ) );

	//
	// Set the collision flag
	//

	if ( !sub_object->collision_contribution )
	{

		contributes_to_collision = FALSE;
	}

	//
	// Figure out new position
	//

	relative_position.x = (	( sub_object->keyframes[0].x * scene_rotation[0][0] ) +
									( sub_object->keyframes[0].y * scene_rotation[1][0] ) +
									( sub_object->keyframes[0].z * scene_rotation[2][0] ) );
	relative_position.y = (	( sub_object->keyframes[0].x * scene_rotation[0][1] ) +
									( sub_object->keyframes[0].y * scene_rotation[1][1] ) +
									( sub_object->keyframes[0].z * scene_rotation[2][1] ) );
	relative_position.z = (	( sub_object->keyframes[0].x * scene_rotation[0][2] ) +
									( sub_object->keyframes[0].y * scene_rotation[1][2] ) +
									( sub_object->keyframes[0].z * scene_rotation[2][2] ) );

	scene_position.x += relative_position.x;
	scene_position.y += relative_position.y;
	scene_position.z += relative_position.z;

	get_3d_transformation_matrix ( matrix, sub_object->keyframes[0].heading, -sub_object->keyframes[0].pitch, -sub_object->keyframes[0].roll );

	new_rotation[0][0] = ( ( matrix[0][0] * scene_rotation[0][0] ) + ( matrix[0][1] * scene_rotation[1][0] ) + ( matrix[0][2] * scene_rotation[2][0] ) );
	new_rotation[0][1] = ( ( matrix[0][0] * scene_rotation[0][1] ) + ( matrix[0][1] * scene_rotation[1][1] ) + ( matrix[0][2] * scene_rotation[2][1] ) );
	new_rotation[0][2] = ( ( matrix[0][0] * scene_rotation[0][2] ) + ( matrix[0][1] * scene_rotation[1][2] ) + ( matrix[0][2] * scene_rotation[2][2] ) );

	new_rotation[1][0] = ( ( matrix[1][0] * scene_rotation[0][0] ) + ( matrix[1][1] * scene_rotation[1][0] ) + ( matrix[1][2] * scene_rotation[2][0] ) );
	new_rotation[1][1] = ( ( matrix[1][0] * scene_rotation[0][1] ) + ( matrix[1][1] * scene_rotation[1][1] ) + ( matrix[1][2] * scene_rotation[2][1] ) );
	new_rotation[1][2] = ( ( matrix[1][0] * scene_rotation[0][2] ) + ( matrix[1][1] * scene_rotation[1][2] ) + ( matrix[1][2] * scene_rotation[2][2] ) );

	new_rotation[2][0] = ( ( matrix[2][0] * scene_rotation[0][0] ) + ( matrix[2][1] * scene_rotation[1][0] ) + ( matrix[2][2] * scene_rotation[2][0] ) );
	new_rotation[2][1] = ( ( matrix[2][0] * scene_rotation[0][1] ) + ( matrix[2][1] * scene_rotation[1][1] ) + ( matrix[2][2] * scene_rotation[2][1] ) );
	new_rotation[2][2] = ( ( matrix[2][0] * scene_rotation[0][2] ) + ( matrix[2][1] * scene_rotation[1][2] ) + ( matrix[2][2] * scene_rotation[2][2] ) );

	memcpy ( scene_rotation, new_rotation, sizeof ( matrix3x3 ) );

	scene_rotation[0][0] *= sub_object->keyframes[0].scale_x;
	scene_rotation[1][0] *= sub_object->keyframes[0].scale_y;
	scene_rotation[2][0] *= sub_object->keyframes[0].scale_z;

	scene_rotation[0][1] *= sub_object->keyframes[0].scale_x;
	scene_rotation[1][1] *= sub_object->keyframes[0].scale_y;
	scene_rotation[2][1] *= sub_object->keyframes[0].scale_z;

	scene_rotation[0][2] *= sub_object->keyframes[0].scale_x;
	scene_rotation[1][2] *= sub_object->keyframes[0].scale_y;
	scene_rotation[2][2] *= sub_object->keyframes[0].scale_z;

	//
	// Compute the bounding boxes
	//

	rotate_sub_scene_boundaries ( &rotated_bounds, &objects_3d_data[ sub_object->index ].bounding_box );
	rotate_sub_scene_boundaries ( &rotated_bounds2, &objects_3d_data[ sub_object->index ].bounding_box2 );

	rotated_bounds.xmin += scene_position.x;
	rotated_bounds.ymin += scene_position.y;
	rotated_bounds.zmin += scene_position.z;

	rotated_bounds.xmax += scene_position.x;
	rotated_bounds.ymax += scene_position.y;
	rotated_bounds.zmax += scene_position.z;

	scene_bounds.xmin = min ( scene_bounds.xmin, rotated_bounds.xmin );
	scene_bounds.ymin = min ( scene_bounds.ymin, rotated_bounds.ymin );
	scene_bounds.zmin = min ( scene_bounds.zmin, rotated_bounds.zmin );

	scene_bounds.xmax = max ( scene_bounds.xmax, rotated_bounds.xmax );
	scene_bounds.ymax = max ( scene_bounds.ymax, rotated_bounds.ymax );
	scene_bounds.zmax = max ( scene_bounds.zmax, rotated_bounds.zmax );

	if (	( ( rotated_bounds2.xmax - rotated_bounds2.xmin ) != 0 ) ||
			( ( rotated_bounds2.ymax - rotated_bounds2.ymin ) != 0 ) ||
			( ( rotated_bounds2.zmax - rotated_bounds2.zmin ) != 0 ) )
	{

		rotated_bounds2.xmin += scene_position.x;
		rotated_bounds2.ymin += scene_position.y;
		rotated_bounds2.zmin += scene_position.z;

		rotated_bounds2.xmax += scene_position.x;
		rotated_bounds2.ymax += scene_position.y;
		rotated_bounds2.zmax += scene_position.z;

		if ( contributes_to_collision )
		{

			scene_bounds2.xmin = min ( scene_bounds2.xmin, rotated_bounds2.xmin );
			scene_bounds2.ymin = min ( scene_bounds2.ymin, rotated_bounds2.ymin );
			scene_bounds2.zmin = min ( scene_bounds2.zmin, rotated_bounds2.zmin );

			scene_bounds2.xmax = max ( scene_bounds2.xmax, rotated_bounds2.xmax );
			scene_bounds2.ymax = max ( scene_bounds2.ymax, rotated_bounds2.ymax );
			scene_bounds2.zmax = max ( scene_bounds2.zmax, rotated_bounds2.zmax );
		}
	}

	//
	// Calculate sub objects
	//

	for ( count = 0; count < sub_object->number_of_sub_objects; count++ )
	{

		recurse_initialise_sub_scene_bounding_box ( &sub_object->sub_objects[count] );
	}

	//
	// Restore the original position & rotation
	//

	scene_position = old_scene_position;

	memcpy ( scene_rotation, old_scene_rotation, sizeof ( matrix3x3 ) );

	contributes_to_collision = old_contributes_to_collision;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rotate_sub_scene_boundaries ( object_3d_bounds *results, object_3d_bounds *source )
{

	vec3d
		cube_points[8];

	int
		count;

	if (	( source->xmin == 0.0 ) && ( source->xmax == 0.0 ) &&
			( source->ymin == 0.0 ) && ( source->ymax == 0.0 ) &&
			( source->zmin == 0.0 ) && ( source->zmax == 0.0 ) )
	{

		results->xmin = 0.0;
		results->xmax = 0.0;
		results->ymin = 0.0;
		results->ymax = 0.0;
		results->zmin = 0.0;
		results->zmax = 0.0;
	}
	else
	{

		cube_points[0].x = source->xmin; cube_points[0].y = source->ymin; cube_points[0].z = source->zmin;
		cube_points[1].x = source->xmin; cube_points[1].y = source->ymin; cube_points[1].z = source->zmax;
		cube_points[2].x = source->xmin; cube_points[2].y = source->ymax; cube_points[2].z = source->zmin;
		cube_points[3].x = source->xmin; cube_points[3].y = source->ymax; cube_points[3].z = source->zmax;
		cube_points[4].x = source->xmax; cube_points[4].y = source->ymin; cube_points[4].z = source->zmin;
		cube_points[5].x = source->xmax; cube_points[5].y = source->ymin; cube_points[5].z = source->zmax;
		cube_points[6].x = source->xmax; cube_points[6].y = source->ymax; cube_points[6].z = source->zmin;
		cube_points[7].x = source->xmax; cube_points[7].y = source->ymax; cube_points[7].z = source->zmax;

		for ( count = 0; count < 8; count++ )
		{

			float
				x,
				y,
				z;

			x = cube_points[count].x * scene_rotation[0][0] + cube_points[count].y * scene_rotation[1][0] + cube_points[count].z * scene_rotation[2][0];
			y = cube_points[count].x * scene_rotation[0][1] + cube_points[count].y * scene_rotation[1][1] + cube_points[count].z * scene_rotation[2][1];
			z = cube_points[count].x * scene_rotation[0][2] + cube_points[count].y * scene_rotation[1][2] + cube_points[count].z * scene_rotation[2][2];

			cube_points[count].x = x;
			cube_points[count].y = y;
			cube_points[count].z = z;
		}

		results->xmin = cube_points[0].x;
		results->xmax = cube_points[0].x;
		results->ymin = cube_points[0].y;
		results->ymax = cube_points[0].y;
		results->zmin = cube_points[0].z;
		results->zmax = cube_points[0].z;

		for ( count = 1; count < 8; count++ )
		{

			results->xmin = min ( results->xmin, cube_points[count].x );
			results->ymin = min ( results->ymin, cube_points[count].y );
			results->zmin = min ( results->zmin, cube_points[count].z );

			results->xmax = max ( results->xmax, cube_points[count].x );
			results->ymax = max ( results->ymax, cube_points[count].y );
			results->zmax = max ( results->zmax, cube_points[count].z );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void count_named_sub_objects ( object_3d_database_entry *sub_scene )
{

	int
		count;

	for ( count = 0; count < sub_scene->number_of_sub_object_indices; count++ )
	{

		sub_object_index_count[ sub_scene->sub_object_indices[count].sub_object_index ]++;
	}

	for ( count = 0; count < sub_scene->number_of_sub_objects; count++ )
	{

		count_named_sub_objects ( &sub_scene->sub_objects[count] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void populate_table_with_named_sub_objects ( object_3d_database_entry *object )
{

	int
		count;

	for ( count = 0; count < object->number_of_sub_object_indices; count++ )
	{

		object_3d_sub_object_index_numbers
			index;

		int
			offset;

		object_3d_database_entry
			*sub_object;

		index = object->sub_object_indices[count].sub_object_index;

		offset = object->sub_object_indices[count].object_index;

		sub_object = &object->sub_objects[offset];

		add_sub_object_index_to_table ( index, sub_object );
	}

	for ( count = 0; count < object->number_of_sub_objects; count++ )
	{

		populate_table_with_named_sub_objects ( &object->sub_objects[count] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_sub_object_index_to_table ( object_3d_sub_object_index_numbers index, object_3d_database_entry *object )
{

	int
		count;

	for ( count = 0; count < number_of_sub_object_table_entries; count++ )
	{

		if ( current_sub_object_table[count].sub_object_index == index )
		{

			int
				offset;

			offset = current_sub_object_table[count].number_of_sub_objects;

			current_sub_object_table[count].sub_objects[offset] = object;

			current_sub_object_table[count].number_of_sub_objects++;

			return;
		}
	}

	debug_fatal ( "Unable to find sub object index in table" );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_sub_object_search_statistics ( void )
{

#if REPORT_SUB_OBJECT_SEARCHES

	sub_object_search_count = 0;

	sub_object_internal_search_count = 0;

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_sub_object_search_statistics ( void )
{

#if REPORT_SUB_OBJECT_SEARCHES

	debug_log ( "Performed %d sub object searches, internal: %d", sub_object_search_count, sub_object_internal_search_count );

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum SUB_OBJECT_SEARCH_RESULT_TYPES find_object_3d_sub_object ( struct OBJECT_3D_SUB_OBJECT_SEARCH_DATA *search )
{

	object_3d_sub_instance
		*result;

	object_3d_database_entry
		*scene_result;

	int
		table_index,
		scene_index;

	object_3d_sub_object_index_numbers
		search_index;

	object_3d_scene_sub_object_table_entry   // table of the named sub objects (from scene)
		*table;

#if REPORT_SUB_OBJECT_SEARCHES

	sub_object_search_count++;

#endif

	sub_object_search_minimum_depth = search->search_depth;

	scene_index = search->search_object->object_number;

	search_index = search->sub_object_index;

	table = objects_3d_scene_database[scene_index].sub_object_indices_table;

	result = NULL;

	scene_result = NULL;

	for ( table_index = 0; ( ( table_index < objects_3d_scene_database[scene_index].number_of_sub_object_table_entries ) && ( !scene_result ) ); table_index++ )
	{

		if ( table[table_index].sub_object_index == search_index )
		{

			//
			// Check to ensure we haven't gone past our search depth
			//

			if ( sub_object_search_minimum_depth < table[table_index].number_of_sub_objects )
			{

				scene_result = table[table_index].sub_objects[sub_object_search_minimum_depth];

				break;
			}
			else
			{

				break;
			}
		}
	}

	if ( scene_result )
	{

		//
		// Match the scene to the object
		//

		result = get_sub_object_from_sub_scene ( scene_index, scene_result, search->search_object );

		search->result_sub_object = result;

		search->object_scene = scene_result;

		search->relative_heading_initial = scene_result->keyframes[0].heading;
		search->relative_heading_minimum = scene_result->relative_heading_minimum;
		search->relative_heading_maximum = scene_result->relative_heading_maximum;

		search->relative_pitch_initial = scene_result->keyframes[0].pitch;
		search->relative_pitch_minimum = scene_result->relative_pitch_minimum;
		search->relative_pitch_maximum = scene_result->relative_pitch_maximum;

		search->relative_roll_initial = scene_result->keyframes[0].roll;
		search->relative_roll_minimum = scene_result->relative_roll_minimum;
		search->relative_roll_maximum = scene_result->relative_roll_maximum;

		return ( SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND );
	}
	else
	{

		search->object_scene = NULL;

		return ( SUB_OBJECT_SEARCH_RESULT_OBJECT_NOT_FOUND );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum SUB_OBJECT_SEARCH_RESULT_TYPES find_object_3d_sub_object_from_sub_object ( struct OBJECT_3D_SUB_OBJECT_SEARCH_DATA *parent_search, struct OBJECT_3D_SUB_OBJECT_SEARCH_DATA *search )
{

	object_3d_instance
		*scene_object;

	object_3d_sub_instance
		*tmp_object,
		*result;

	object_3d_database_entry
		*scene_parent,
		*scene_result;

	int
		search_depth,
		table_index,
		scene_index;

	object_3d_sub_object_index_numbers
		search_index;

	object_3d_scene_sub_object_table_entry
		*table;

#if REPORT_SUB_OBJECT_SEARCHES

	sub_object_search_count++;

#endif

	search_depth = search->search_depth;

	tmp_object = parent_search->result_sub_object;

	while ( tmp_object->parent )
	{

		tmp_object = tmp_object->parent;
	}

	scene_object = ( object_3d_instance * ) tmp_object;

	scene_index = scene_object->object_number;

	search_index = search->sub_object_index;

	scene_parent = parent_search->object_scene;

	table = objects_3d_scene_database[scene_index].sub_object_indices_table;

	result = NULL;

	scene_result = NULL;

	for ( table_index = 0; ( ( table_index < objects_3d_scene_database[scene_index].number_of_sub_object_table_entries ) && ( !scene_result ) ); table_index++ )
	{

		if ( table[table_index].sub_object_index == search_index )
		{

			int
				search_object_depth;

			search_object_depth = 0;

			while ( search_depth >= 0 )
			{

				if ( search_object_depth >= table[table_index].number_of_sub_objects )
				{

					break;
				}
				else
				{

					if ( sub_scene_has_parent_scene ( scene_parent, table[table_index].sub_objects[search_object_depth] ) )
					{

						scene_result = table[table_index].sub_objects[search_object_depth];

						if ( search_depth == 0 )
						{

							break;
						}
						else
						{

							search_depth--;
						}
					}
				}

				search_object_depth++;
			}

			if ( search_depth != 0 )
			{

				scene_result = NULL;
			}
		}
	}

	if ( scene_result )
	{

		//
		// Match the scene to the object
		//

		result = get_sub_object_from_sub_scene ( scene_index, scene_result, scene_object );

		search->result_sub_object = result;

		search->object_scene = scene_result;

		search->relative_heading_initial = scene_result->keyframes[0].heading;
		search->relative_heading_minimum = scene_result->relative_heading_minimum;
		search->relative_heading_maximum = scene_result->relative_heading_maximum;

		search->relative_pitch_initial = scene_result->keyframes[0].pitch;
		search->relative_pitch_minimum = scene_result->relative_pitch_minimum;
		search->relative_pitch_maximum = scene_result->relative_pitch_maximum;

		search->relative_roll_initial = scene_result->keyframes[0].roll;
		search->relative_roll_minimum = scene_result->relative_roll_minimum;
		search->relative_roll_maximum = scene_result->relative_roll_maximum;

		return ( SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND );
	}
	else
	{

		search->object_scene = NULL;

		return ( SUB_OBJECT_SEARCH_RESULT_OBJECT_NOT_FOUND );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sub_scene_has_parent_scene ( object_3d_database_entry *parent, object_3d_database_entry *scene )
{

	while ( scene )
	{

		if ( scene->parent == parent )
		{

			return ( TRUE );
		}
		else
		{

			scene = scene->parent;
		}
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_sub_instance *get_sub_object_from_sub_scene ( int scene_index, object_3d_database_entry *sub_scene, object_3d_instance *object )
{

	object_3d_database_entry
		*this_scene,
		*sub_scenes[256];

	object_3d_sub_instance
		*this_sub_object;

	int
		offset,
		count,
		number_of_sub_scenes;

	number_of_sub_scenes = 0;

	this_scene = sub_scene;

	// build path up to parent
	while ( this_scene )
	{

		sub_scenes[number_of_sub_scenes] = this_scene;

		this_scene = this_scene->parent;

		number_of_sub_scenes++;

		ASSERT(number_of_sub_scenes < (sizeof(sub_scenes) / sizeof(sub_scenes[0])));
	}

	//
	// Get the offset of parent from the main scene / object
	//

	offset = sub_scenes[ ( number_of_sub_scenes - 1 ) ] - objects_3d_scene_database[scene_index].sub_objects;

	this_sub_object = &object->sub_objects[offset];  // get the parent object

	this_scene = sub_scenes[ ( number_of_sub_scenes -1 ) ];  // parent scene

	// traverse down the object tree with the same path as the scenes, and we should get the corresponding object
	for ( count = ( number_of_sub_scenes - 2 ); count >= 0; count-- )
	{

		offset = sub_scenes[count] - this_scene->sub_objects;

		this_sub_object = &this_sub_object->sub_objects[offset];

		this_scene = sub_scenes[count];
	}

	return ( this_sub_object );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_sub_instance* find_sub_object(object_3d_instance* parent_object, unsigned sub_obj_id)
{
	object_3d_sub_object_search_data
		search;

	const char* name = (sub_obj_id < OBJECT_3D_SUB_OBJECT_LAST) ? object_3d_subobject_names[sub_obj_id] : NULL;

	search.search_depth = 0;
	search.search_object = parent_object;
	search.sub_object_index = sub_obj_id;

	if (find_object_3d_sub_object(&search) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		if (name)
			debug_fatal ("Failed to locate sub object: %s", name);
		else
			debug_fatal ("Failed to locate sub object: %d (illegal id)", sub_obj_id);

	return search.result_sub_object;
}
