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

#include "terrain.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAXIMUM_BUFFERED_TREES 4096

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BUFFERED_TREE
{

	vec3d
		position,
		scale;

	real_colour
		colour;

	float
		depth;

	struct BUFFERED_TREE
		*pred,
		*succ;
};

typedef struct BUFFERED_TREE buffered_tree;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

terrain_tree_data
	*terrain_tree_database;

terrain_tree_info
	**terrain_tree_sectors;

buffered_tree
	buffered_tree_array[MAXIMUM_BUFFERED_TREES];

object_3d_instance
	*terrain_3d_tree_object,
	*terrain_3d_side_tree_object;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	current_tree_colour_red,
	current_tree_colour_green,
	current_tree_colour_blue;

unsigned char
	current_tree_colour_alpha;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_terrain_tree_buffering_system ( void );

void add_buffered_tree ( int index );

void draw_buffered_sorted_terrain_trees ( void );

void draw_3d_terrain_tree ( object_3d_instance *obj );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_terrain_trees ( void )
{

	//
	// Construct a tree object
	//

//	terrain_3d_tree_object = construct_3d_object ( OBJECT_3D_CANOPY_HEMISPHERE );

//	terrain_3d_side_tree_object = construct_3d_object ( OBJECT_3D_CANOPY_SPHERE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_terrain_3d_tree_database ( char *sector_filename, char *data_filename )
{

	FILE
		*fp;

	int
		x_sector,
		z_sector;

	terrain_tree_data
		*tree_data;

	//
	// Memory map the tree data file
	//

	terrain_tree_database = mopen ( data_filename );

	if ( !terrain_tree_database )
	{

		debug_fatal ( "Unable to memory-map %s", data_filename );
	}

	//
	// Open the sector file
	//

	fp = safe_fopen ( sector_filename, "rb" );

	//
	// Go through all the sectors, setting the number of trees and the relevant pointer
	//

	tree_data = terrain_tree_database;

	for ( z_sector = 0; z_sector < terrain_3d_sector_z_max; z_sector++ )
	{

		for ( x_sector = 0; x_sector < terrain_3d_sector_z_max; x_sector++ )
		{

			fread ( &terrain_tree_sectors[z_sector][x_sector].number_of_trees, sizeof ( int ), 1, fp );

			if ( terrain_tree_sectors[z_sector][x_sector].number_of_trees )
			{

				terrain_tree_sectors[z_sector][x_sector].data = tree_data;

				tree_data += terrain_tree_sectors[z_sector][x_sector].number_of_trees;
			}
			else
			{

				terrain_tree_sectors[z_sector][x_sector].data = NULL;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unload_terrain_3d_tree_database ( void )
{

	int
		x_sector,
		z_sector;

	if ( terrain_tree_sectors )
	{
	
		mclose ( terrain_tree_database );
	
		for ( z_sector = 0; z_sector < terrain_3d_sector_z_max; z_sector++ )
		{
	
			for ( x_sector = 0; x_sector < terrain_3d_sector_z_max; x_sector++ )
			{
	
				terrain_tree_sectors[z_sector][x_sector].number_of_trees = 0;
	
				terrain_tree_sectors[z_sector][x_sector].data = NULL;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_tree_sector ( scene_slot_drawing_list *slot )
{

	terrain_tree_info
		*current_tree_sector;

	terrain_tree_data
		*tree_data;

	int
		count;

	float
		current_sector_x_offset,
		current_sector_z_offset;
	
	current_tree_sector = &terrain_tree_sectors[slot->sector.z][slot->sector.x];

	tree_data = current_tree_sector->data;

	current_sector_x_offset = slot->sector.x * TERRAIN_3D_SECTOR_SIDE_LENGTH;

	current_sector_z_offset = slot->sector.z * TERRAIN_3D_SECTOR_SIDE_LENGTH;

	if ( current_tree_sector->number_of_trees )
	{

		reset_terrain_tree_buffering_system ();

		for ( count = 0; count < current_tree_sector->number_of_trees; count++ )
		{
	
			float
				x,
				y,
				z,
				relative_z;

			x = tree_data->x;
			y = tree_data->y;
			z = tree_data->z;

			relative_z = (	( x - visual_3d_vp->x ) * visual_3d_vp->zv.x +
								( y - visual_3d_vp->y ) * visual_3d_vp->zv.y +
								( z - visual_3d_vp->z ) * visual_3d_vp->zv.z );

			if ( relative_z < 1024.0 )
			{

				int
					tree_index;

				tree_index = get_tree_buffer ();

				buffered_tree_array[tree_index].position.x = x;
				buffered_tree_array[tree_index].position.y = y;
				buffered_tree_array[tree_index].position.z = z;

				buffered_tree_array[tree_index].scale.x = tree_data->scale_x;
				buffered_tree_array[tree_index].scale.y = tree_data->scale_y / 2;
				buffered_tree_array[tree_index].scale.z = tree_data->scale_z;

				buffered_tree_array[tree_index].depth = relative_z;

				buffered_tree_array[tree_index].colour = tree_data->colour;

				add_buffered_tree ( tree_index );
			}

			tree_data++;
		}

		draw_buffered_sorted_terrain_trees ();

		set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_buffered_trees;

buffered_tree
	*buffered_sorted_tree_head,
	*buffered_sorted_tree_tail,
	*buffered_sorted_tree_insert;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_terrain_tree_buffering_system ( void )
{

	number_of_buffered_trees = 0;

	buffered_sorted_tree_head = NULL;

	buffered_sorted_tree_tail = NULL;

	buffered_sorted_tree_insert = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_tree_buffer ( void )
{

	ASSERT ( number_of_buffered_trees < MAXIMUM_BUFFERED_TREES );

	return ( number_of_buffered_trees++ );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_buffered_tree ( int index )
{

	float
		distance;

	distance = buffered_tree_array[index].depth;

	if ( buffered_sorted_tree_insert )
	{

		buffered_tree
			*previous_tree,
			*this_tree;

		this_tree = buffered_sorted_tree_insert;

		previous_tree = buffered_sorted_tree_insert;

		if ( distance < this_tree->depth )
		{

			//
			// Start searching BACKWARDS ( more distant trees drawn first )
			//
	
			while ( this_tree )
			{
	
				if ( distance >= this_tree->depth )
				{
	
					break;
				}
				else
				{
	
					previous_tree = this_tree;
	
					this_tree = this_tree->pred;
				}
			}
	
			if ( this_tree )
			{

				//
				// Add new tree AFTER this_tree
				//

				if ( !this_tree->succ )
				{

					//
					// We are at the tail end of the list
					//

					buffered_tree_array[index].pred = this_tree;

					buffered_tree_array[index].succ = NULL;

					this_tree->succ = &buffered_tree_array[index];

					buffered_sorted_tree_tail = &buffered_tree_array[index];

					buffered_sorted_tree_insert = &buffered_tree_array[index];
				}
				else
				{

					//
					// Insert into list normally.
					//

					buffered_tree_array[index].succ = this_tree->succ;

					buffered_tree_array[index].pred = this_tree;

					this_tree->succ->pred = &buffered_tree_array[index];

					this_tree->succ = &buffered_tree_array[index];

					buffered_sorted_tree_insert = &buffered_tree_array[index];
				}
			}
			else
			{
	
				//
				// Add this tree at the HEAD of the list
				//

				buffered_tree_array[index].succ = buffered_sorted_tree_head;

				buffered_tree_array[index].pred = NULL;

				buffered_sorted_tree_head->pred = &buffered_tree_array[index];

				buffered_sorted_tree_head = &buffered_tree_array[index];

				buffered_sorted_tree_insert = &buffered_tree_array[index];
			}
		}
		else
		{

			//
			// Start searching FORWARDS ( less distant trees drawn last )
			//
	
			while ( this_tree )
			{
	
				if ( distance <= this_tree->depth )
				{
	
					break;
				}
				else
				{
	
					previous_tree = this_tree;
	
					this_tree = this_tree->succ;
				}
			}
	
			if ( this_tree )
			{

				//
				// Add new tree BEFORE this_tree
				//

				if ( !this_tree->pred )
				{

					//
					// We are at the head end of the list
					//

					buffered_tree_array[index].pred = NULL;

					buffered_tree_array[index].succ = this_tree;

					this_tree->pred = &buffered_tree_array[index];

					buffered_sorted_tree_head = &buffered_tree_array[index];

					buffered_sorted_tree_insert = &buffered_tree_array[index];
				}
				else
				{

					//
					// Insert into list normally.
					//

					buffered_tree_array[index].pred = this_tree->pred;

					buffered_tree_array[index].succ = this_tree;

					this_tree->pred->succ = &buffered_tree_array[index];

					this_tree->pred = &buffered_tree_array[index];

					buffered_sorted_tree_insert = &buffered_tree_array[index];
				}
			}
			else
			{
	
				//
				// Add this polygon at the TAIL of the list
				//

				buffered_tree_array[index].pred = buffered_sorted_tree_tail;

				buffered_tree_array[index].succ = NULL;

				buffered_sorted_tree_tail->succ = &buffered_tree_array[index];

				buffered_sorted_tree_tail = &buffered_tree_array[index];

				buffered_sorted_tree_insert = &buffered_tree_array[index];
			}
		}
	}
	else
	{

		buffered_tree_array[index].succ = NULL;

		buffered_tree_array[index].pred = NULL;

		buffered_sorted_tree_head = &buffered_tree_array[index];

		buffered_sorted_tree_tail = &buffered_tree_array[index];

		buffered_sorted_tree_insert = &buffered_tree_array[index];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_buffered_sorted_terrain_trees ( void )
{

	buffered_tree
		*tree;

	tree = buffered_sorted_tree_tail;

	while ( tree )
	{

		//
		// Draw a tree object at ( x, y, z )
		//

		terrain_3d_tree_object->vp.x = tree->position.x;
		terrain_3d_tree_object->vp.y = tree->position.y;
		terrain_3d_tree_object->vp.z = tree->position.z;

		terrain_3d_tree_object->relative_scale.x = tree->scale.x;
		terrain_3d_tree_object->relative_scale.y = tree->scale.y;
		terrain_3d_tree_object->relative_scale.z = tree->scale.z;

		get_3d_transformation_matrix ( terrain_3d_tree_object->vp.attitude, 0, 0, 0 );

		set_object_3d_instance_relative_position ( terrain_3d_tree_object );

		if ( get_object_3d_instance_visibility ( terrain_3d_tree_object ) != OBJECT_3D_NOT_VISIBLE )
		{

			if ( terrain_3d_tree_object->rel_vp.z < 1024.0 )
			{

				float
					alpha;

				int
					ialpha;

				current_tree_colour_red = tree->colour.red;
				current_tree_colour_green = tree->colour.green;
				current_tree_colour_blue = tree->colour.blue;

				current_tree_colour_red /= 255.0;
				current_tree_colour_green /= 255.0;
				current_tree_colour_blue /= 255.0;

				//
				// Set the alpha value here
				//

				if ( terrain_3d_tree_object->rel_vp.z > 512.0 )
				{

					alpha = 1024.0 - terrain_3d_tree_object->rel_vp.z;
					alpha /= 512.0;

					convert_float_to_int ( ( alpha * 255 ), &ialpha );
					current_tree_colour_alpha = ialpha;
				}
				else
				{

					current_tree_colour_alpha = 255;
				}

				current_tree_colour_alpha = 255;

				draw_3d_terrain_tree ( terrain_3d_tree_object );
			}
		}

		tree = tree->pred;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_tree ( object_3d_instance *obj )
{

	int
		object_number;

	object_3d_info
		*this_object_3d_info;

	light_3d_source
		*this_light,
		*prev_light,
		*light_ptr,
		*light;

	vec3d
		*pos;
	
	vec3d
		object_camera_position,
		object_pos;

	//
	// Set up the object drawing global variables
	//

	object_3d_points_current_base = 0;

	object_3d_object_current_base = 0;

	object_3d_light_3d_current_base = 0;

	//
	// Calculate the object's position relative to the view.
	//

	pos = &obj->rel_vp.position;

	{

		float
			fog_intensity;

		int
			ifog_intensity;

		fog_intensity = get_fog_distance_value ( pos->z );

		convert_float_to_int ( fog_intensity, &ifog_intensity );

		set_d3d_fog_face_intensity ( ifog_intensity );
	}

	//
	// Set the main objects' scaling values
	//

	object_3d_scale.x = obj->relative_scale.x;
	object_3d_scale.y = obj->relative_scale.y;
	object_3d_scale.z = obj->relative_scale.z;

	//
	// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
	//

	rotation_3d[0][0] = ( obj->vp.xv.x * visual_3d_vp->xv.x + obj->vp.xv.y * visual_3d_vp->xv.y + obj->vp.xv.z * visual_3d_vp->xv.z );
	rotation_3d[0][1] = ( obj->vp.xv.x * visual_3d_vp->yv.x + obj->vp.xv.y * visual_3d_vp->yv.y + obj->vp.xv.z * visual_3d_vp->yv.z );
	rotation_3d[0][2] = ( obj->vp.xv.x * visual_3d_vp->zv.x + obj->vp.xv.y * visual_3d_vp->zv.y + obj->vp.xv.z * visual_3d_vp->zv.z );

	rotation_3d[1][0] = ( obj->vp.yv.x * visual_3d_vp->xv.x + obj->vp.yv.y * visual_3d_vp->xv.y + obj->vp.yv.z * visual_3d_vp->xv.z );
	rotation_3d[1][1] = ( obj->vp.yv.x * visual_3d_vp->yv.x + obj->vp.yv.y * visual_3d_vp->yv.y + obj->vp.yv.z * visual_3d_vp->yv.z );
	rotation_3d[1][2] = ( obj->vp.yv.x * visual_3d_vp->zv.x + obj->vp.yv.y * visual_3d_vp->zv.y + obj->vp.yv.z * visual_3d_vp->zv.z );

	rotation_3d[2][0] = ( obj->vp.zv.x * visual_3d_vp->xv.x + obj->vp.zv.y * visual_3d_vp->xv.y + obj->vp.zv.z * visual_3d_vp->xv.z );
	rotation_3d[2][1] = ( obj->vp.zv.x * visual_3d_vp->yv.x + obj->vp.zv.y * visual_3d_vp->yv.y + obj->vp.zv.z * visual_3d_vp->yv.z );
	rotation_3d[2][2] = ( obj->vp.zv.x * visual_3d_vp->zv.x + obj->vp.zv.y * visual_3d_vp->zv.y + obj->vp.zv.z * visual_3d_vp->zv.z );

	rotation_3d[0][0] *= object_3d_scale.x;
	rotation_3d[1][0] *= object_3d_scale.y;
	rotation_3d[2][0] *= object_3d_scale.z;

	rotation_3d[0][1] *= object_3d_scale.x;
	rotation_3d[1][1] *= object_3d_scale.y;
	rotation_3d[2][1] *= object_3d_scale.z;

	rotation_3d[0][2] *= object_3d_scale.x;
	rotation_3d[1][2] *= object_3d_scale.y;
	rotation_3d[2][2] *= object_3d_scale.z;

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	{

		float
			x,
			y,
			z;

		x = ( ( visual_3d_vp->x - obj->vp.x ) * obj->vp.xv.x );
		x += ( ( visual_3d_vp->y - obj->vp.y ) *  obj->vp.xv.y );
		x += ( ( visual_3d_vp->z - obj->vp.z ) *  obj->vp.xv.z );

		y = ( ( visual_3d_vp->x - obj->vp.x ) * obj->vp.yv.x );
		y += ( ( visual_3d_vp->y - obj->vp.y ) *  obj->vp.yv.y );
		y += ( ( visual_3d_vp->z - obj->vp.z ) *  obj->vp.yv.z );

		z = ( ( visual_3d_vp->x - obj->vp.x ) * obj->vp.zv.x );
		z += ( ( visual_3d_vp->y - obj->vp.y ) *  obj->vp.zv.y );
		z += ( ( visual_3d_vp->z - obj->vp.z ) *  obj->vp.zv.z );

		object_pos.x = x;
		object_pos.y = y;
		object_pos.z = z;
	}

	//
	// Get the object number
	//

	object_number = get_object_approximation_number ( obj->object_number, pos->z, &object_3d_approximation_level );

	//
	// Rotate the light source vector to be relative to the object.
	//

	light_ptr = current_3d_lights;

	prev_light = NULL;

	light = NULL;

	if ( light_ptr )
	{

		light = &light_3d_array[object_3d_light_3d_current_base];

		while ( light_ptr )
		{

			float
				lx,
				ly,
				lz;

			if ( light_ptr->type == LIGHT_3D_TYPE_POINT )
			{

				vec3d
					vector;

				float
					distance;

				//
				// Work out the distance from object to light source
				//

				vector.x = - light_ptr->light_position.x + obj->vp.x;
				vector.y = - light_ptr->light_position.y + obj->vp.y;
				vector.z = - light_ptr->light_position.z + obj->vp.z;

				lx = vector.x * vector.x;
				ly = vector.y * vector.y;
				lz = vector.z * vector.z;

				distance = ( lx + ly + lz );

				if ( distance < light_ptr->radius )
				{

					distance = 1 - ( distance / light_ptr->radius );

					this_light = &light_3d_array[object_3d_light_3d_current_base];
			
					object_3d_light_3d_current_base++;
		
					if ( prev_light )
					{
		
						prev_light->succ = this_light;
					}
		
					this_light->pred = prev_light;
					this_light->succ = NULL;
		
					this_light->type = light_ptr->type;

					this_light->colour.red = light_ptr->colour.red * distance;
					this_light->colour.green = light_ptr->colour.green * distance;
					this_light->colour.blue = light_ptr->colour.blue * distance;
//					this_light->colour.intensity = light_ptr->colour.intensity * distance;

					normalise_3d_vector ( &vector );

					lx = ( vector.x * obj->vp.attitude[0][0] );
					lx += ( vector.y * obj->vp.attitude[0][1] );
					lx += ( vector.z * obj->vp.attitude[0][2] );
		
					ly = ( vector.x * obj->vp.attitude[1][0] );
					ly += ( vector.y * obj->vp.attitude[1][1] );
					ly += ( vector.z * obj->vp.attitude[1][2] );
		
					lz = ( vector.x * obj->vp.attitude[2][0] );
					lz += ( vector.y * obj->vp.attitude[2][1] );
					lz += ( vector.z * obj->vp.attitude[2][2] );
		
					this_light->lx = lx;
					this_light->ly = ly;
					this_light->lz = lz;
		
					prev_light = this_light;
				}
			}
			else
			{
	
				this_light = &light_3d_array[object_3d_light_3d_current_base];
		
				object_3d_light_3d_current_base++;
	
				if ( prev_light )
				{
	
					prev_light->succ = this_light;
				}
	
				this_light->pred = prev_light;
				this_light->succ = NULL;
	
				this_light->type = light_ptr->type;

				this_light->colour.red = light_ptr->colour.red;
				this_light->colour.green = light_ptr->colour.green;
				this_light->colour.blue = light_ptr->colour.blue;
//				this_light->colour.intensity = light_ptr->colour.intensity;
	
				lx = ( light_ptr->lx * obj->vp.attitude[0][0] );
				lx +=  ( light_ptr->ly * obj->vp.attitude[0][1] );
				lx += ( light_ptr->lz * obj->vp.attitude[0][2] );
	
				ly = ( light_ptr->lx * obj->vp.attitude[1][0] );
				ly += ( light_ptr->ly * obj->vp.attitude[1][1] );
				ly += ( light_ptr->lz * obj->vp.attitude[1][2] );
	
	
				lz = ( light_ptr->lx * obj->vp.attitude[2][0] );
				lz += ( light_ptr->ly * obj->vp.attitude[2][1] );
				lz += ( light_ptr->lz * obj->vp.attitude[2][2] );
	
				this_light->lx = lx;
				this_light->ly = ly;
				this_light->lz = lz;
	
				prev_light = this_light;
			}
	
			light_ptr = light_ptr->succ;
		}
	}

	{

		vec3d
			rel_pos;

		//
		// Calculate the relative camera position in the object viewspace
		//

		rel_pos.x = visual_3d_vp->x - obj->vp.x;
		rel_pos.y = visual_3d_vp->y - obj->vp.y;
		rel_pos.z = visual_3d_vp->z - obj->vp.z;

		object_camera_position.x = ( rel_pos.x * obj->vp.attitude[0][0] + rel_pos.y * obj->vp.attitude[1][0] + rel_pos.z * obj->vp.attitude[2][0] );
		object_camera_position.y = ( rel_pos.x * obj->vp.attitude[0][1] + rel_pos.y * obj->vp.attitude[1][1] + rel_pos.z * obj->vp.attitude[2][1] );
		object_camera_position.z = ( rel_pos.x * obj->vp.attitude[0][2] + rel_pos.y * obj->vp.attitude[1][2] + rel_pos.z * obj->vp.attitude[2][2] );
	}

	//
	//	Set up this objects' object info structure
	//

	object_3d_object_base[object_3d_object_current_base].lights = light;

	object_3d_object_base[object_3d_object_current_base].camera_position = object_camera_position;

	object_3d_object_base[object_3d_object_current_base].points_base = object_3d_points_current_base;

	object_3d_object_base[object_3d_object_current_base].object_number = object_number;

	this_object_3d_info = &object_3d_object_base[object_3d_object_current_base];

	global_object_3d_info = this_object_3d_info;

	//
	// Transform the object's shape data
	//

	//
	// Setup the objects scaling information
	//

	{

		float
			xdistance,
			ydistance,
			zdistance;

		xdistance = ( objects_3d_data[object_number].bounding_box.xmax - objects_3d_data[object_number].bounding_box.xmin ) / 2;
		ydistance = ( objects_3d_data[object_number].bounding_box.ymax - objects_3d_data[object_number].bounding_box.ymin ) / 2;
		zdistance = ( objects_3d_data[object_number].bounding_box.zmax - objects_3d_data[object_number].bounding_box.zmin ) / 2;

		object_3d_x_middle = objects_3d_data[object_number].bounding_box.xmin + xdistance;
		object_3d_y_middle = objects_3d_data[object_number].bounding_box.ymin + ydistance;
		object_3d_z_middle = objects_3d_data[object_number].bounding_box.zmin + zdistance;

		object_3d_x_scale = xdistance / 32767.0;
		object_3d_y_scale = ydistance / 32767.0;
		object_3d_z_scale = zdistance / 32767.0;
	}
/*
	if ( objects_3d_data[object_number].number_of_points )
	{

		int
			object_outcode;

		object_outcode = get_object_3d_outcode ( object_number, pos );

		if ( object_outcode )
		{

			transform_3d_object ( &objects_3d_data[object_number], pos, light, object_3d_points_current_base);
		}
		else
		{

			transform_unclipped_3d_object ( &objects_3d_data[object_number], pos, light, object_3d_points_current_base);
		}


		polygon_zdistance_bias = POLYGON_ZDISTANCE_NORMAL_BIAS;

		set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CW );

		if ( object_outcode )
		{

			draw_3d_terrain_tree_clipped_faces ( object_number, this_object_3d_info );
		}
		else
		{

			draw_3d_terrain_tree_unclipped_faces ( object_number, this_object_3d_info );
		}

		set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

		if ( object_outcode )
		{

			draw_3d_terrain_tree_clipped_faces ( object_number, this_object_3d_info );
		}
		else
		{

			draw_3d_terrain_tree_unclipped_faces ( object_number, this_object_3d_info );
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_tree_clipped_faces ( int object_number, object_3d_info *this_object_3d_info )
{
/*
	object_3d_face
		*faces;

	int
		count;

	faces = objects_3d_data[object_number].faces;

	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
	current_object_3d_gouraud_list = objects_3d_data[object_number].object_point_normal_references;
	current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;
	current_object_3d_texture_list = objects_3d_data[object_number].object_faces_texture_point_list;
	current_object_3d_transformed_normals = &transformed_3d_normals[object_3d_points_current_base];

	if ( current_object_3d_surface->texture_wrapped )	{ current_object_3d_texture_address = D3DTADDRESS_WRAP; }
	else																{ current_object_3d_texture_address = D3DTADDRESS_CLAMP; }

	if ( current_object_3d_surface->texture_filtered )	{ current_object_3d_texture_filter = D3DFILTER_LINEAR; }
	else																{ current_object_3d_texture_filter = D3DFILTER_NEAREST; }

	if ( current_object_3d_surface->texture_mipmapped ){ current_object_3d_texture_mipmap = D3DFILTER_MIPLINEAR; }
	else																{ current_object_3d_texture_mipmap = D3DFILTER_NEAREST; }

	for ( count = objects_3d_data[object_number].number_of_faces; count > 0; count-- )
	{

		ASSERT ( faces->number_of_points >= 3 );

		if ( faces->flags & FACE_HAS_NEW_SURFACE )
		{

			current_object_3d_surface++;

			if ( current_object_3d_surface->texture_wrapped )	{ current_object_3d_texture_address = D3DTADDRESS_WRAP; }
			else																{ current_object_3d_texture_address = D3DTADDRESS_CLAMP; }
	
			if ( current_object_3d_surface->texture_filtered )	{ current_object_3d_texture_filter = D3DFILTER_LINEAR; }
			else																{ current_object_3d_texture_filter = D3DFILTER_NEAREST; }
	
			if ( current_object_3d_surface->texture_mipmapped ){ current_object_3d_texture_mipmap = D3DFILTER_MIPLINEAR; }
			else																{ current_object_3d_texture_mipmap = D3DFILTER_NEAREST; }
		}

		if ( outcode_3d_object_polygon ( faces->number_of_points, current_object_3d_point_list, this_object_3d_info->points_base, &current_object_3d_outcode ) )
		{

			if ( current_object_3d_outcode == 0 )
			{

				if ( faces->flags & FACE_TEXTURED )
				{

					if ( faces->flags & FACE_GOURAUD_SHADED )
					{

						render_unclipped_3d_terrain_tree_gouraud_textured_diffuse_lit_polygon ( faces, this_object_3d_info );
					}
					else
					{

						render_unclipped_3d_terrain_tree_textured_diffuse_lit_polygon ( faces, this_object_3d_info );
					}
				}
				else
				{

					debug_fatal ( "Trying to draw a non-textured face in a canopy hemisphere" );
				}
			}
			else
			{

				if ( faces->flags & FACE_TEXTURED )
				{

					if ( faces->flags & FACE_GOURAUD_SHADED )
					{

						render_clipped_3d_terrain_tree_gouraud_textured_diffuse_lit_polygon ( faces, this_object_3d_info );
					}
					else
					{

						render_clipped_3d_terrain_tree_textured_diffuse_lit_polygon ( faces, this_object_3d_info );
					}
				}
				else
				{

					debug_fatal ( "Trying to draw a non-textured face in a canopy hemisphere" );
				}
			}
		}

		current_object_3d_point_list += faces->number_of_points;

		current_object_3d_texture_list += faces->number_of_points;

		if ( faces->flags & FACE_GOURAUD_SHADED )
		{

			current_object_3d_gouraud_list += faces->number_of_points;
		}
		else
		{

			current_object_3d_face_normal_list++;
		}

		faces++;
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_terrain_tree_unclipped_faces ( int object_number, object_3d_info *this_object_3d_info )
{
/*
	object_3d_face
		*faces;

	int
		count;

	faces = objects_3d_data[object_number].faces;

	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
	current_object_3d_gouraud_list = objects_3d_data[object_number].object_point_normal_references;
	current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;
	current_object_3d_texture_list = objects_3d_data[object_number].object_faces_texture_point_list;
	current_object_3d_transformed_normals = &transformed_3d_normals[object_3d_points_current_base];

	if ( current_object_3d_surface->texture_wrapped )	{ current_object_3d_texture_address = D3DTADDRESS_WRAP; }
	else																{ current_object_3d_texture_address = D3DTADDRESS_CLAMP; }

	if ( current_object_3d_surface->texture_filtered )	{ current_object_3d_texture_filter = D3DFILTER_LINEAR; }
	else																{ current_object_3d_texture_filter = D3DFILTER_NEAREST; }

	if ( current_object_3d_surface->texture_mipmapped ){ current_object_3d_texture_mipmap = D3DFILTER_MIPLINEAR; }
	else																{ current_object_3d_texture_mipmap = D3DFILTER_NEAREST; }

	for ( count = objects_3d_data[object_number].number_of_faces; count > 0; count-- )
	{

		ASSERT ( faces->number_of_points >= 3 );

		if ( faces->flags & FACE_HAS_NEW_SURFACE )
		{

			current_object_3d_surface++;

			if ( current_object_3d_surface->texture_wrapped )	{ current_object_3d_texture_address = D3DTADDRESS_WRAP; }
			else																{ current_object_3d_texture_address = D3DTADDRESS_CLAMP; }
	
			if ( current_object_3d_surface->texture_filtered )	{ current_object_3d_texture_filter = D3DFILTER_LINEAR; }
			else																{ current_object_3d_texture_filter = D3DFILTER_NEAREST; }
	
			if ( current_object_3d_surface->texture_mipmapped ){ current_object_3d_texture_mipmap = D3DFILTER_MIPLINEAR; }
			else																{ current_object_3d_texture_mipmap = D3DFILTER_NEAREST; }
		}

		if ( faces->flags & FACE_TEXTURED )
		{

			if ( faces->flags & FACE_GOURAUD_SHADED )
			{

				render_unclipped_3d_terrain_tree_gouraud_textured_diffuse_lit_polygon ( faces, this_object_3d_info );
			}
			else
			{

				render_unclipped_3d_terrain_tree_textured_diffuse_lit_polygon ( faces, this_object_3d_info );
			}
		}
		else
		{

			debug_fatal ( "Trying to draw a non-textured face in a canopy hemisphere" );
		}

		current_object_3d_point_list += faces->number_of_points;

		current_object_3d_texture_list += faces->number_of_points;

		if ( faces->flags & FACE_GOURAUD_SHADED )
		{

			current_object_3d_gouraud_list += faces->number_of_points;
		}
		else
		{

			current_object_3d_face_normal_list++;
		}

		faces++;
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_clipped_3d_terrain_tree_textured_diffuse_lit_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	texture_map
		*texture;

	texture = &system_textures[current_object_3d_surface->texture_index];

	{

		real_colour
			colour;

		float
			red,
			green,
			blue;

		int
			ired,
			igreen,
			iblue;

		//
		// Look up the colour of the face normal
		//

		red = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].r;
		green = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].g;
		blue = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].b;

		red *= current_tree_colour_red;
		green *= current_tree_colour_green;
		blue *= current_tree_colour_blue;

		convert_float_to_int ( red, &ired );
		convert_float_to_int ( green, &igreen );
		convert_float_to_int ( blue, &iblue );

		colour.red = ired;
		colour.green = igreen;
		colour.blue = iblue;
		colour.alpha = 255;

		poly = NULL;
		/*construct_3d_vertex_textured_polygon ( this_face->number_of_points,
																		current_object_3d_point_list,
																		current_object_3d_texture_list,
																		object_base->points_base );
																		*/
		
		clip_3d_coord = 0;

		if ( current_object_3d_outcode & CLIP_HITHER )
		{
	
			poly = hither_clip_3d_polygon ( poly, &current_object_3d_outcode );

			if ( !poly )
			{

				return;
			}
		}

		if ( current_object_3d_outcode )
		{

			apply_perspective_to_polygon_texture ( poly );
				
			poly = clip_3d_polygon ( poly, current_object_3d_outcode );

			if ( !poly )
			{

				return;
			}

			remove_perspective_from_polygon_texture ( poly );
		}

//		set_d3d_int_state ( D3DRENDERSTATE_TEXTUREMAG, current_object_3d_texture_filter );
//		set_d3d_int_state ( D3DRENDERSTATE_TEXTUREMIN, current_object_3d_texture_mipmap );
//		set_d3d_int_state ( D3DRENDERSTATE_TEXTUREADDRESS, current_object_3d_texture_address );

//		draw_d3d_flat_shaded_textured_polygon ( poly, texture, colour );
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_clipped_3d_terrain_tree_gouraud_textured_diffuse_lit_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	int
		triangle_count,
		outcode;

	vertex
		*poly;

	texture_map
		*texture;

	texture = &system_textures[current_object_3d_surface->texture_index];

	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{

		poly = NULL;
		/*construct_3d_vertex_gouraud_coloured_textured_triangle_fan ( triangle_count,
																									current_object_3d_point_list,
																									current_object_3d_gouraud_list,
																									current_object_3d_texture_list,
																									object_base->points_base,
																									&outcode,
																									current_tree_colour_red,
																									current_tree_colour_green,
																									current_tree_colour_blue,
																									current_tree_colour_alpha );
																									*/
		if ( poly )
		{
		
			if ( outcode )
			{
		
				clip_3d_coord = 0;

				if ( outcode & CLIP_HITHER )
				{
			
					poly = hither_clip_3d_polygon ( poly, &outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			
				if ( outcode )
				{
		
					apply_perspective_to_polygon_texture ( poly );
						
					poly = clip_3d_polygon ( poly, outcode );
		
					if ( !poly )
					{
		
						continue;
					}
		
					remove_perspective_from_polygon_texture ( poly );
				}
			}
		

//			set_d3d_int_state ( D3DRENDERSTATE_TEXTUREMAG, current_object_3d_texture_filter );
//			set_d3d_int_state ( D3DRENDERSTATE_TEXTUREMIN, current_object_3d_texture_mipmap );
//			set_d3d_int_state ( D3DRENDERSTATE_TEXTUREADDRESS, current_object_3d_texture_address );

//			draw_d3d_gouraud_shaded_textured_polygon ( poly, texture );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_unclipped_3d_terrain_tree_textured_diffuse_lit_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	texture_map
		*texture;

	real_colour
		colour;

	int
		ired,
		igreen,
		iblue,
		count;

	float
		red,
		green,
		blue;

	object_transformed_2d_point
		*vert,
		*transformed_points;

	LPD3DTLVERTEX
		destination_vertices;

	object_3d_short_textured_point
		*texture_list;

	texture = &system_textures[current_object_3d_surface->texture_index];

	//
	// Look up the colour of the face normal
	//

	red = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].r;
	green = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].g;
	blue = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].b;

	red *= current_tree_colour_red;
	green *= current_tree_colour_green;
	blue *= current_tree_colour_blue;

	convert_float_to_int ( red, &ired );
	convert_float_to_int ( green, &igreen );
	convert_float_to_int ( blue, &iblue );

	colour.red = ired;
	colour.green = igreen;
	colour.blue = iblue;
	colour.alpha = current_tree_colour_alpha;

//	set_d3d_int_state ( D3DRENDERSTATE_TEXTUREMAG, current_object_3d_texture_filter );
//	set_d3d_int_state ( D3DRENDERSTATE_TEXTUREMIN, current_object_3d_texture_mipmap );
//	set_d3d_int_state ( D3DRENDERSTATE_TEXTUREADDRESS, current_object_3d_texture_address );

	//
	// Should draw a flat shaded polygon
	//

	set_d3d_flat_shaded_textured_renderstate ( texture );

	transformed_points = transformed_3d_2d_points + object_base->points_base;

	destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

	texture_list = NULL;	//current_object_3d_texture_list;

	for ( count = 0; count < this_face->number_of_points; count++ )
	{

		vert = NULL;	//transformed_points + current_object_3d_point_list[count].point;
	
		*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
		destination_vertices[count].sz = vert->q;
		destination_vertices[count].rhw = vert->q;
		destination_vertices[count].tu = ( ( float ) texture_list->u ) / OBJECT_3D_TEXTURE_UV_SCALE;
		destination_vertices[count].tv = ( ( float ) texture_list->v ) / OBJECT_3D_TEXTURE_UV_SCALE;
		destination_vertices[count].color = colour.colour;
		destination_vertices[count].specular = d3d_fog_intensity;

		texture_list++;
	}

	draw_fan_primitive ( this_face->number_of_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_unclipped_3d_terrain_tree_gouraud_textured_diffuse_lit_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	texture_map
		*texture;

	int
		count;

	object_transformed_2d_point
		*vert,
		*transformed_points;

	LPD3DTLVERTEX
		destination_vertices;

	object_3d_short_textured_point
		*texture_list;

	point_3d_plain_reference
		*gouraud_list;

	texture = &system_textures[current_object_3d_surface->texture_index];

	transformed_points = transformed_3d_2d_points + object_base->points_base;

	texture_list = NULL;	//current_object_3d_texture_list;

	gouraud_list = NULL;	//current_object_3d_gouraud_list;

	//
	// Should draw a gouraud shaded polygon
	//

	set_d3d_gouraud_shaded_textured_renderstate ( texture );

//	set_d3d_int_state ( D3DRENDERSTATE_TEXTUREMAG, current_object_3d_texture_filter );
//	set_d3d_int_state ( D3DRENDERSTATE_TEXTUREMIN, current_object_3d_texture_mipmap );
//	set_d3d_int_state ( D3DRENDERSTATE_TEXTUREADDRESS, current_object_3d_texture_address );

	destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

	for ( count = 0; count < this_face->number_of_points; count++ )
	{

		int
			ir,
			ig,
			ib;
	
		float
			r,
			g,
			b;

		real_colour
			colour;

		vert = NULL;	//transformed_points + current_object_3d_point_list[count].point;
	
		*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
		destination_vertices[count].sz = vert->q;
		destination_vertices[count].rhw = vert->q;
		destination_vertices[count].tu = ( ( float ) texture_list->u ) / OBJECT_3D_TEXTURE_UV_SCALE;
		destination_vertices[count].tv = ( ( float ) texture_list->v ) / OBJECT_3D_TEXTURE_UV_SCALE;
		r = current_object_3d_transformed_normals[gouraud_list->point].r;
		g = current_object_3d_transformed_normals[gouraud_list->point].g;
		b = current_object_3d_transformed_normals[gouraud_list->point].b;
		convert_float_to_int ( ( r * current_tree_colour_red ), &ir );
		convert_float_to_int ( ( g * current_tree_colour_green ), &ig );
		convert_float_to_int ( ( b * current_tree_colour_blue ), &ib );
		colour.red = ir;
		colour.green = ig;
		colour.blue = ib;
		colour.alpha = current_tree_colour_alpha;
		destination_vertices[count].color = colour.colour;
		destination_vertices[count].specular = d3d_fog_intensity;

		gouraud_list++;
		texture_list++;
	}

	draw_fan_primitive ( this_face->number_of_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

